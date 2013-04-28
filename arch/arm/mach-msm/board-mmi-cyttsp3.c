/*
 * Copyright 2012 Motorola Mobility, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/kobject.h>
#include <linux/kernel.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/input/touch_platform.h>
#include <linux/msm_ssbi.h>
#include <asm/prom.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <mach/gpiomux.h>
#include <linux/input/cyttsp3_core.h>
#include "board-mmi.h"

static struct gpiomux_setting cyts3_resout_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting cyts3_resout_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting cyts3_sleep_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting cyts3_sleep_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting cyts3_int_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting cyts3_int_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config msm8960_cyts3_configs[] = {
	{
		.gpio = CYTT_GPIO_INTR,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cyts3_int_act_cfg,
			[GPIOMUX_SUSPENDED] = &cyts3_int_sus_cfg,
		},
	},
	{
		.gpio = CYTT_GPIO_ENABLE,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cyts3_sleep_act_cfg,
			[GPIOMUX_SUSPENDED] = &cyts3_sleep_sus_cfg,
		},
	},
	{
		.gpio = CYTT_GPIO_RST,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cyts3_resout_act_cfg,
			[GPIOMUX_SUSPENDED] = &cyts3_resout_sus_cfg,
		},
	},
};

int mot_setup_touch_cyttsp3(struct i2c_board_info *info,
		struct device_node *node)
{
	int retval = 0;
	struct touch_platform_data *tpdata;

	tpdata = kzalloc(sizeof(struct touch_platform_data), GFP_KERNEL);
	if (!tpdata) {
		pr_err("%s: Unable to create platform data.\n", __func__);
		retval = -ENOMEM;
		goto out;
	}

	info->platform_data = tpdata;

	tpdata->gpio_enable    = CYTT_GPIO_ENABLE;
	tpdata->gpio_reset     = CYTT_GPIO_RST;
	tpdata->gpio_interrupt = CYTT_GPIO_INTR;

	msm_gpiomux_install(msm8960_cyts3_configs,
			ARRAY_SIZE(msm8960_cyts3_configs));

	if (mapphone_touch_panel_init(info, node) != 0) {
		pr_err("%s:FATAL! No touch devtree params found\n", __func__);
		kfree(tpdata);
		info->platform_data = NULL;
		retval = -ENOMEM;
	}

out:
	return retval;
}
