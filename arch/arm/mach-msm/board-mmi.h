/*
 * arch/arm/mach-msm/board-mmi.h
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

#ifndef __ARCH_ARM_MACH_MSM_BOARD_MMI_H
#define __ARCH_ARM_MACH_MSM_BOARD_MMI_H

#include <linux/mfd/pm8xxx/pm8921.h>
#include <linux/power/mmi-battery.h>
#include <linux/ct406.h>
#include <linux/i2c.h>
#include <linux/of.h>

#define _HWREV(x)	(x)
#define HWREV_DEF	_HWREV(0xFF00)
#define HWREV_S1	_HWREV(0x1100)
#define HWREV_S2	_HWREV(0x1200)
#define HWREV_S3	_HWREV(0x1300)
#define HWREV_M1	_HWREV(0x2100)
#define HWREV_M2	_HWREV(0x2200)
#define HWREV_M3	_HWREV(0x2300)
#define HWREV_P0	_HWREV(0x8000)
#define HWREV_P1	_HWREV(0x8100)
#define HWREV_P1B2	_HWREV(0x81B2)
#define HWREV_P1C	_HWREV(0x81C0)
#define HWREV_P2	_HWREV(0x8200)
#define HWREV_P3	_HWREV(0x8300)
#define HWREV_P4	_HWREV(0x8400)
#define HWREV_P5	_HWREV(0x8500)
#define HWREV_P6	_HWREV(0x8600)

#ifdef CONFIG_TOUCHSCREEN_MELFAS100_TS
extern struct touch_platform_data touch_pdata;
extern int __init melfas_ts_platform_init(void);
#endif

#ifdef CONFIG_BACKLIGHT_LM3532
extern struct lm3532_backlight_platform_data mp_lm3532_pdata;
#endif

extern int mot_setup_touch_cyttsp3(struct i2c_board_info *info,
		struct device_node *node);

extern int mot_setup_touch_atmxt(struct i2c_board_info *info,
		struct device_node *node);

extern int __init msm8960_tmp105_init(struct i2c_board_info *info,
		struct device_node *child);

extern struct pm8xxx_keypad_platform_data mmi_keypad_data;
extern struct pm8xxx_keypad_platform_data mmi_qwerty_keypad_data;

extern struct pm8xxx_keypad_platform_data mot_keypad_data;
extern struct msm_i2c_platform_data msm8960_i2c_qup_gsbi12_pdata;

enum {
	MMI_BATTERY_DEFAULT = 0,
	MMI_BATTERY_EB20_P1,
	MMI_BATTERY_EB20_PRE,
	MMI_BATTERY_EB41_B,
	MMI_BATTERY_EV30_CID_5858,
	MMI_BATTERY_EV30_CID_4246,
	MMI_BATTERY_EG30_SDI,
	MMI_BATTERY_EB20_SDI,
	MMI_BATTERY_EB40_LG,
	MMI_BATTERY_EG30_LG,
	MMI_BATTERY_NUM,
};

struct mmi_battery_list {
	unsigned int                        num_cells;
	struct mmi_battery_cell             *cell_list[MMI_BATTERY_NUM];
	struct pm8921_bms_battery_data      *bms_list[MMI_BATTERY_NUM];
	struct pm8921_charger_battery_data  *chrg_list[MMI_BATTERY_NUM];
};

extern struct mmi_battery_list mmi_batts;

int __init ct406_init(struct i2c_board_info *info, struct device_node *child);
void msm8960_get_dsps_fw_name(char *name);
void __init mmi_vibrator_init(void);
int __init mapphone_touch_panel_init(struct i2c_board_info *i2c_info,
		struct device_node *node);
void enable_msm_l2_erp_irq(void);
void disable_msm_l2_erp_irq(void);

#define  MMI_KEYPAD_RESET	0x1
#define  MMI_KEYPAD_SLIDER	0x2

int __init mmi_keypad_init(int mode);
#endif
