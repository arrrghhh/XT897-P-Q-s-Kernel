/*
 * linux/arch/arm/mach-msm/board-8960-sensors.c
 *
 * Copyright (C) 2009-2012 Motorola Mobility, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifdef CONFIG_INPUT_CT406
#include <linux/ct406.h>
#endif
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#ifdef CONFIG_BACKLIGHT_LM3532
#include <linux/i2c/lm3532.h>
#endif
#include <linux/platform_device.h>
#include <mach/gpio.h>
#include <mach/gpiomux.h>

#include "board-mmi.h"

#ifdef CONFIG_INPUT_CT406
/*
 * CT406
 */

static struct gpiomux_setting ct406_reset_suspend_config = {
                        .func = GPIOMUX_FUNC_GPIO,
                        .drv = GPIOMUX_DRV_2MA,
                        .pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting ct406_reset_active_config = {
                        .func = GPIOMUX_FUNC_GPIO,
                        .drv = GPIOMUX_DRV_2MA,
                        .pull = GPIOMUX_PULL_NONE,
                        .dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config ct406_irq_gpio_config = {
        .settings = {
                [GPIOMUX_SUSPENDED] = &ct406_reset_suspend_config,
                [GPIOMUX_ACTIVE] = &ct406_reset_active_config,
        },
};

struct ct406_platform_data mp_ct406_pdata = {
	.regulator_name = "",
	.prox_samples_for_noise_floor = 0x05,
	.ct405_prox_saturation_threshold = 0x0208,
	.ct405_prox_covered_offset = 0x008c,
	.ct405_prox_uncovered_offset = 0x0046,
	.ct405_prox_recalibrate_offset = 0x0046,
	.ct405_prox_pulse_count = 0x02,
	.ct405_prox_offset = 0x00,
	.ct406_prox_saturation_threshold = 0x0208,
	.ct406_prox_covered_offset = 0x008c,
	.ct406_prox_uncovered_offset = 0x0046,
	.ct406_prox_recalibrate_offset = 0x0046,
	.ct406_prox_pulse_count = 0x02,
	.ct406_prox_offset = 0x00,
	.als_lens_transmissivity = 20,
};

int __init ct406_init(struct i2c_board_info *info, struct device_node *child)

{
	int ret = 0;
	int len = 0;
	const void *prop;
	unsigned gpio = 0;

	info->platform_data = &mp_ct406_pdata;

	prop = of_get_property(child, "irq,gpio", &len);
	if (!prop || (len != sizeof(u8)))
		return -EINVAL;
	gpio = *(u8 *)prop;

	info->irq = MSM_GPIO_TO_INT(gpio);

	ct406_irq_gpio_config.gpio = gpio;
	msm_gpiomux_install(&ct406_irq_gpio_config, 1);
	ret = gpio_request(gpio, "ct406 proximity int");
	if (ret) {
		pr_err("ct406 gpio_request failed: %d\n", ret);
		goto fail;
	}

	ret = gpio_export(gpio, 0);
	if (ret) {
		pr_err("ct406 gpio_export failed: %d\n", ret);
	}

	mp_ct406_pdata.irq = info->irq;

	prop = of_get_property(child, "prox_samples_for_noise_floor", &len);
	if (prop && (len == sizeof(u8)))
		mp_ct406_pdata.prox_samples_for_noise_floor = *(u8 *)prop;
	prop = of_get_property(child, "ct405_prox_saturation_threshold", &len);
	if (prop && (len == sizeof(u16)))
		mp_ct406_pdata.ct405_prox_saturation_threshold = *(u16 *)prop;
	prop = of_get_property(child, "ct405_prox_covered_offset", &len);
	if (prop && (len == sizeof(u16)))
		mp_ct406_pdata.ct405_prox_covered_offset = *(u16 *)prop;
	prop = of_get_property(child, "ct405_prox_uncovered_offset", &len);
	if (prop && (len == sizeof(u16)))
		mp_ct406_pdata.ct405_prox_uncovered_offset = *(u16 *)prop;
	prop = of_get_property(child, "ct405_prox_recalibrate_offset", &len);
	if (prop && (len == sizeof(u16)))
		mp_ct406_pdata.ct405_prox_recalibrate_offset = *(u16 *)prop;
	prop = of_get_property(child, "ct405_prox_offset", &len);
	if (prop && (len == sizeof(u8)))
		mp_ct406_pdata.ct405_prox_offset = *(u8 *)prop;
	prop = of_get_property(child, "ct406_prox_saturation_threshold", &len);
	if (prop && (len == sizeof(u16)))
		mp_ct406_pdata.ct406_prox_saturation_threshold = *(u16 *)prop;
	prop = of_get_property(child, "ct406_prox_covered_offset", &len);
	if (prop && (len == sizeof(u16)))
		mp_ct406_pdata.ct406_prox_covered_offset = *(u16 *)prop;
	prop = of_get_property(child, "ct406_prox_uncovered_offset", &len);
	if (prop && (len == sizeof(u16)))
		mp_ct406_pdata.ct406_prox_uncovered_offset = *(u16 *)prop;
	prop = of_get_property(child, "ct406_prox_recalibrate_offset", &len);
	if (prop && (len == sizeof(u16)))
		mp_ct406_pdata.ct406_prox_recalibrate_offset = *(u16 *)prop;
	prop = of_get_property(child, "ct406_prox_pulse_count", &len);
	if (prop && (len == sizeof(u8)))
		mp_ct406_pdata.ct406_prox_pulse_count = *(u8 *)prop;
	prop = of_get_property(child, "ct406_prox_offset", &len);
	if (prop && (len == sizeof(u8)))
		mp_ct406_pdata.ct406_prox_offset = *(u8 *)prop;

	return 0;

fail:
	return ret;
}
#else
static int __init ct406_init(void)
{
	return 0;
}
#endif //CONFIG_CT406

#ifdef CONFIG_BACKLIGHT_LM3532
/*
 * LM3532
 */

#define LM3532_RESET_GPIO 12

static struct gpiomux_setting lm3532_reset_suspend_config = {
			.func = GPIOMUX_FUNC_GPIO,
			.drv = GPIOMUX_DRV_2MA,
			.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting lm3532_reset_active_config = {
			.func = GPIOMUX_FUNC_GPIO,
			.drv = GPIOMUX_DRV_2MA,
			.pull = GPIOMUX_PULL_NONE,
			.dir = GPIOMUX_OUT_LOW,
};

static struct msm_gpiomux_config lm3532_reset_gpio_config = {
	.gpio = LM3532_RESET_GPIO,
	.settings = {
		[GPIOMUX_SUSPENDED] = &lm3532_reset_suspend_config,
		[GPIOMUX_ACTIVE] = &lm3532_reset_active_config,
	},
};

static int lm3532_power_up(void)
{
	int ret;

	msm_gpiomux_install(&lm3532_reset_gpio_config, 1);

        ret = gpio_request(LM3532_RESET_GPIO, "lm3532_reset");
        if (ret) {
                pr_err("%s: Request LM3532 reset GPIO failed, ret=%d\n",
			__func__, ret);
                return -ENODEV;
        }

	return 0;
}

static int lm3532_power_down(void)
{
	gpio_free(LM3532_RESET_GPIO);

	return 0;
}

static int lm3532_reset_assert(void)
{
	gpio_set_value(LM3532_RESET_GPIO, 0);

	return 0;
}

static int lm3532_reset_release(void)
{
	gpio_set_value(LM3532_RESET_GPIO, 1);

	return 0;
}

struct lm3532_backlight_platform_data mp_lm3532_pdata = {
	.power_up = lm3532_power_up,
	.power_down = lm3532_power_down,
	.reset_assert = lm3532_reset_assert,
	.reset_release = lm3532_reset_release,

	.led1_controller = LM3532_CNTRL_A,
	.led2_controller = LM3532_CNTRL_A,
	.led3_controller = LM3532_CNTRL_C,

	.ctrl_a_name = "lcd-backlight",
	.ctrl_b_name = "lm3532_led1",
	.ctrl_c_name = "lm3532_led2",

	.susd_ramp = 0xC0,
	.runtime_ramp = 0xC0,

	.als1_res = 0xE0,
	.als2_res = 0xE0,
	.als_dwn_delay = 0x00,
	.als_cfgr = 0x2C,

	.en_ambl_sens = 0,

	.pwm_init_delay_ms = 5000,
	.pwm_resume_delay_ms = 0,
	.pwm_disable_threshold = 0,

	.ctrl_a_usage = LM3532_BACKLIGHT_DEVICE,
	.ctrl_a_pwm = 0xC2,
	.ctrl_a_fsc = 0xFF,
	.ctrl_a_l4_daylight = 0xFF,
	.ctrl_a_l3_bright = 0xCC,
	.ctrl_a_l2_office = 0x99,
	.ctrl_a_l1_indoor = 0x66,
	.ctrl_a_l0_dark = 0x33,

	.ctrl_b_usage = LM3532_UNUSED_DEVICE,
	.ctrl_b_pwm = 0x82,
	.ctrl_b_fsc = 0xFF,
	.ctrl_b_l4_daylight = 0xFF,
	.ctrl_b_l3_bright = 0xCC,
	.ctrl_b_l2_office = 0x99,
	.ctrl_b_l1_indoor = 0x66,
	.ctrl_b_l0_dark = 0x33,

	.ctrl_c_usage = LM3532_UNUSED_DEVICE,
	.ctrl_c_pwm = 0x82,
	.ctrl_c_fsc = 0xFF,
	.ctrl_c_l4_daylight = 0xFF,
	.ctrl_c_l3_bright = 0xCC,
	.ctrl_c_l2_office = 0x99,
	.ctrl_c_l1_indoor = 0x66,
	.ctrl_c_l0_dark = 0x33,

	.l4_high = 0xCC,
	.l4_low = 0xCC,
	.l3_high = 0x99,
	.l3_low = 0x99,
	.l2_high = 0x66,
	.l2_low = 0x66,
	.l1_high = 0x33,
	.l1_low = 0x33,

	.boot_brightness = 102,
};
#endif /* CONFIG_BACKLIGHT_LM3532 */

/*
 * DSPS Firmware
 */

void msm8960_get_dsps_fw_name(char *name)
{
	struct device_node *dsps_node;
	int len = 0;
	const void *prop;

	dsps_node = of_find_node_by_path("/Chosen@0");
	if (!dsps_node)
		return;
	prop = of_get_property(dsps_node, "qualcomm,dsps,fw", &len);
	if (len >= 16) {
		printk(KERN_ERR "%s: Invalid DSPS FW name\n", __func__);
		return;
	}
	if (prop) {
		strcpy(name, (char *)prop);
		printk(KERN_INFO "%s: DSPS FW version from devtree: %s\n",
			 __func__, (char *)prop);
	}
}

/*
 * TMP105/LM75 temperature sensor
 */

static struct gpiomux_setting tmp105_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting tmp105_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.pull = GPIOMUX_PULL_UP,
};

static struct msm_gpiomux_config tmp105_gpio_configs = {
	.settings = {
		[GPIOMUX_ACTIVE]    = &tmp105_int_act_cfg,
		[GPIOMUX_SUSPENDED] = &tmp105_int_sus_cfg,
	},
};

int  __init msm8960_tmp105_init(struct i2c_board_info *info,
				struct device_node *child)
{
	int ret = 0;
	int len = 0;
	const void *prop;
	unsigned gpio = 0;

	pr_debug("msm8960_tmp105_init\n");

	prop = of_get_property(child, "irq,gpio", &len);
	if (!prop || (len != sizeof(u8)))
		return -EINVAL;
	gpio = *(u8 *)prop;
	tmp105_gpio_configs.gpio = gpio;
	msm_gpiomux_install(&tmp105_gpio_configs, 1);

	ret = gpio_request(gpio, "tmp105_intr");
	if (ret) {
		pr_err("gpio_request tmp105_intr GPIO (%d) failed (%d)\n",
			gpio, ret);
		return ret;
	}
	gpio_direction_input(gpio);

	ret = gpio_export(gpio, 0);
	if (ret)
		pr_err("tmp105 gpio_export failed: %d\n", ret);
	return 0;
}
