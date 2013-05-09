/*
 * arch/arm/mach-msm/board-8960-melfas-touch.c
 *
 * Copyright (C) 2011-2012 Motorola Mobility, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/resource.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/i2c.h>
#include <asm/mach-types.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <mach/gpio.h>
#include <mach/gpiomux.h>
#include <linux/earlysuspend.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/gfp.h>
#include <linux/types.h>
#include <linux/slab.h>

#include <linux/input/touch_platform.h>
#include <linux/melfas100_ts.h>
#include "board-mmi.h"

#define MELFAS_SLOW_TOUCH 2000
#define MELFAS_LATENCY_SAMPLES 64
#define MELFAS_LATENCY_SHIFT 6
#define MELFAS_ALL_LATENCY_SIZE 1024
#define MELFAS_SLOW_SIZE 256

static u32 melfas_latency_times[MELFAS_LATENCY_SAMPLES];
static struct timespec melfas_int_time;
static u32 melfas_int_count;
static u32 melfas_all_int_count;
static u32 melfas_slow_int_count;
static u32 melfas_high_latency;
static u32 melfas_avg_latency;
static u64 *melfas_slow_timestamp;
static u32 *melfas_all_latency;
static u8 melfas_latency_debug;

static void touch_calculate_latency(void);
static void touch_set_int_time(void);
static void touch_set_latency_debug_level(u8 debug_level);
static void touch_recalc_avg_latency(void);
static u32 touch_get_avg_latency(void);
static u32 touch_get_high_latency(void);
static u32 touch_get_slow_int_count(void);
static u32 touch_get_int_count(void);
static u32 touch_get_timestamp_ptr(u64 **timestamp);
static u32 touch_get_latency_ptr(u32 **latency);
static u8 touch_get_latency_debug_level(void);

static struct touch_firmware	ts_firmware;
static uint8_t	fw_version[] = { 0x45 };
/* should be used to compare to public firmware version */
static uint8_t	priv_v[] = { 0x07 };
static uint8_t	pub_v[] = { 0x15 };
static uint8_t fw_file_name[] = "melfas_45_7_15.fw";

static struct gpiomux_setting i2c_gpio_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi3_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi3_suspended_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_KEEPER,
};

static struct gpiomux_setting melfas_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting melfas_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct msm_gpiomux_config gsbi3_gpio_configs[] = {
	{
		.gpio = MELFAS_TOUCH_SDA_GPIO,
		.settings = {
			[GPIOMUX_ACTIVE]    = &i2c_gpio_config,
			[GPIOMUX_SUSPENDED] = &i2c_gpio_config,
		},
	},
	{
		.gpio = MELFAS_TOUCH_SCL_GPIO,
		.settings = {
			[GPIOMUX_ACTIVE]    = &i2c_gpio_config,
			[GPIOMUX_SUSPENDED] = &i2c_gpio_config,
		},
	},
	{
		.gpio = MELFAS_TOUCH_INT_GPIO,
		.settings = {
			[GPIOMUX_ACTIVE]    = &melfas_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &melfas_int_sus_cfg,
		},
	}

};

static struct msm_gpiomux_config gsbi3_i2c_configs[] = {
	{
		.gpio = MELFAS_TOUCH_SDA_GPIO,	/* GSBI3 I2C QUP SDA */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi3_suspended_cfg,
			[GPIOMUX_ACTIVE] = &gsbi3_active_cfg,
		},
	},
	{
		.gpio = MELFAS_TOUCH_SCL_GPIO,	/* GSBI3 I2C QUP SCL */
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi3_suspended_cfg,
			[GPIOMUX_ACTIVE] = &gsbi3_active_cfg,
		},
	},
	{
		.gpio = MELFAS_TOUCH_INT_GPIO,
		.settings = {
			[GPIOMUX_ACTIVE]    = &melfas_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &melfas_int_sus_cfg,
		},
	}
};

static int melfas_mux_fw_flash(bool to_gpios)
{
	/* TOUCH_EN is always an output */
	if (to_gpios) {
		gpio_direction_output(MELFAS_TOUCH_INT_GPIO, 0);

		msm_gpiomux_install(gsbi3_gpio_configs,
				ARRAY_SIZE(gsbi3_gpio_configs));

		gpio_direction_output(MELFAS_TOUCH_SCL_GPIO, 0);
		gpio_direction_output(MELFAS_TOUCH_SDA_GPIO, 0);
	} else {
		gpio_direction_output(MELFAS_TOUCH_INT_GPIO, 1);
		gpio_direction_input(MELFAS_TOUCH_INT_GPIO);

		/* Initalize SCL and SDA for i2c mode */
		msm_gpiomux_install(gsbi3_i2c_configs,
				ARRAY_SIZE(gsbi3_i2c_configs));

		gpio_direction_output(MELFAS_TOUCH_SCL_GPIO, 1);
		gpio_direction_input(MELFAS_TOUCH_SCL_GPIO);
		gpio_direction_output(MELFAS_TOUCH_SDA_GPIO, 1);
		gpio_direction_input(MELFAS_TOUCH_SDA_GPIO);
	}
	return 0;
}

struct touch_platform_data touch_pdata = {
	.flags = TS_FLIP_X | TS_FLIP_Y,

	.gpio_interrupt	= MELFAS_TOUCH_INT_GPIO,
	.gpio_reset	= MELFAS_TOUCH_RESET_GPIO,
	.gpio_scl	= MELFAS_TOUCH_SCL_GPIO,
	.gpio_sda	= MELFAS_TOUCH_SDA_GPIO,

	.max_x = 719,
	.max_y = 1279,

	.invert_x = 1,
	.invert_y = 1,

	.mux_fw_flash   = melfas_mux_fw_flash,
	.int_latency    = touch_calculate_latency,
	.int_time       = touch_set_int_time,
	.get_avg_lat    = touch_get_avg_latency,
	.get_high_lat   = touch_get_high_latency,
	.get_slow_cnt   = touch_get_slow_int_count,
	.get_int_cnt    = touch_get_int_count,
	.set_dbg_lvl    = touch_set_latency_debug_level,
	.get_dbg_lvl    = touch_get_latency_debug_level,
	.get_time_ptr   = touch_get_timestamp_ptr,
	.get_lat_ptr    = touch_get_latency_ptr,
};


int __init melfas_ts_platform_init(void)
{
	pr_info(" MELFAS TS: platform init\n");

	/* Initalize SCL and SDA for i2c mode */
	msm_gpiomux_install(gsbi3_i2c_configs, ARRAY_SIZE(gsbi3_i2c_configs));

	/* melfas reset gpio */
	gpio_request(MELFAS_TOUCH_RESET_GPIO, "touch_reset");
	gpio_direction_output(MELFAS_TOUCH_RESET_GPIO, 1);

	/* melfas interrupt gpio */
	gpio_request(MELFAS_TOUCH_INT_GPIO, "touch_irq");
	gpio_direction_input(MELFAS_TOUCH_INT_GPIO);

	gpio_request(MELFAS_TOUCH_SCL_GPIO, "touch_scl");
	gpio_request(MELFAS_TOUCH_SDA_GPIO, "touch_sda");

	/* Setup platform structure with the firmware information */
	ts_firmware.ver = &(fw_version[0]);
	ts_firmware.vsize = sizeof(fw_version);
	ts_firmware.private_fw_v = &(priv_v[0]);
	ts_firmware.private_fw_v_size = sizeof(priv_v);
	ts_firmware.public_fw_v = &(pub_v[0]);
	ts_firmware.public_fw_v_size = sizeof(pub_v);

	touch_pdata.fw = &ts_firmware;
	strcpy(touch_pdata.fw_name, fw_file_name);

	return 0;
}

static void touch_recalc_avg_latency()
{
	u64 total_time;
	u8 i;

	for (i = 0; i < MELFAS_LATENCY_SAMPLES; i++)
		total_time += melfas_latency_times[i];
	melfas_avg_latency = total_time >> MELFAS_LATENCY_SHIFT;

	return;
}

static void touch_calculate_latency()
{
	struct timespec end_time;
	struct timespec delta_timespec;
	s64 delta_time;

	ktime_get_ts(&end_time);
	if (melfas_int_count == 0)
		melfas_slow_int_count = 0;
	delta_timespec = timespec_sub(end_time, melfas_int_time);
	delta_time = timespec_to_ns(&delta_timespec);
	do_div(delta_time, NSEC_PER_USEC);
	melfas_latency_times[melfas_int_count & \
				(MELFAS_LATENCY_SAMPLES - 1)] = delta_time;
	if ((melfas_latency_debug >= 2) && (melfas_all_latency == NULL)) {
		melfas_all_latency = kmalloc(MELFAS_ALL_LATENCY_SIZE * \
						sizeof(u32), GFP_ATOMIC);
		memset(melfas_all_latency, 0, MELFAS_ALL_LATENCY_SIZE * \
						sizeof(u32));
	}
	if (melfas_all_latency > 0)
		melfas_all_latency[melfas_all_int_count++ & \
			(MELFAS_ALL_LATENCY_SIZE - 1)] = delta_time;
	if (delta_time > MELFAS_SLOW_TOUCH) {
		if ((melfas_latency_debug >= 2) &&
			(melfas_slow_timestamp == NULL)) {
			melfas_slow_timestamp = kmalloc(MELFAS_SLOW_SIZE * \
						sizeof(u64), GFP_ATOMIC);
			memset(melfas_slow_timestamp, 0, MELFAS_SLOW_SIZE * \
						sizeof(u64));
		}
		if (melfas_slow_timestamp > 0)
			melfas_slow_timestamp[melfas_slow_int_count++ & \
				(MELFAS_SLOW_SIZE - 1)] = \
					timespec_to_ns(&end_time);
	}
	if (delta_time > melfas_high_latency)
		melfas_high_latency = delta_time;
	if (!(melfas_int_count & (MELFAS_LATENCY_SAMPLES - 1)))
		touch_recalc_avg_latency();
	melfas_int_count++;

	return;
}

static void touch_set_int_time()
{
	ktime_get_ts(&melfas_int_time);

	return;
}

static u32 touch_get_avg_latency()
{
	return melfas_avg_latency;
}

static u32 touch_get_high_latency()
{
	return melfas_high_latency;
}

static u32 touch_get_slow_int_count()
{
	return melfas_slow_int_count;
}

static u32 touch_get_int_count()
{
	return melfas_int_count;
}

static void touch_set_latency_debug_level(u8 debug_level)
{
	melfas_latency_debug = debug_level;

	return;
}

static u8 touch_get_latency_debug_level()
{
	return melfas_latency_debug;
}

static u32 touch_get_timestamp_ptr(u64 **timestamp)
{
	*timestamp = melfas_slow_timestamp;

	return MELFAS_SLOW_SIZE * sizeof(u64);
}

static u32 touch_get_latency_ptr(u32 **latency)
{
	*latency = melfas_all_latency;

	return MELFAS_ALL_LATENCY_SIZE * sizeof(u32);
}
