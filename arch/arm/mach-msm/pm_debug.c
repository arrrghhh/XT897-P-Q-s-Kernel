/* Copyright (c) 2012, Motorola Mobility Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kernel.h>
#include <linux/suspend.h>
#include <linux/earlysuspend.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#ifdef CONFIG_PM8921_BMS
#include <linux/mfd/pm8xxx/pm8921-bms.h>
#endif

#define PMDBG_IRQ_LIST_SIZE 3
#define PMDBG_UEVENT_ENV_BUFF 64
static unsigned int pmdbg_gpio_irq[PMDBG_IRQ_LIST_SIZE];
static unsigned int pmdbg_gic_irq[PMDBG_IRQ_LIST_SIZE];
static unsigned int pmdbg_pm8xxx_irq[PMDBG_IRQ_LIST_SIZE];

static int pmdbg_gpio_irq_index;
static int pmdbg_gic_irq_index;
static int pmdbg_pm8xxx_irq_index;

static struct notifier_block pmdbg_suspend_notifier;

static void pmdbg_resume(struct early_suspend *h)
{
	int uah = 0;
#ifdef CONFIG_PM8921_BMS
	if (pm8921_bms_get_cc_uah(&uah) < 0)
		uah = 0;
#endif
	pr_info("pm_debug: wakeup uah=%d\n", uah);
}

static void pmdbg_suspend(struct early_suspend *h)
{
	int uah = 0;
#ifdef CONFIG_PM8921_BMS
	if (pm8921_bms_get_cc_uah(&uah) < 0)
		uah = 0;
#endif
	pr_info("pm_debug: sleep uah=%d\n", uah);
}
static struct early_suspend pmdbg_early_suspend_desc = {
#ifdef CONFIG_HAS_EARLYSUSPEND
	.level = EARLY_SUSPEND_LEVEL_DISABLE_FB,
	.suspend = pmdbg_suspend,
	.resume = pmdbg_resume,
#endif
};

static int
pmdbg_suspend_notifier_call(struct notifier_block *bl, unsigned long state,
			void *unused)
{
	int uah = 0;
#ifdef CONFIG_PM8921_BMS
	if (pm8921_bms_get_cc_uah(&uah) < 0)
		uah = 0;
#endif
	switch (state) {
	case PM_SUSPEND_PREPARE:
		pr_info("pm_debug: suspend uah=%d\n", uah);
		break;
	case PM_POST_SUSPEND:
		pr_info("pm_debug: resume uah=%d\n", uah);
		break;
	}
	return NOTIFY_DONE;
}

void wakeup_source_gpio_cleanup(void)
{
	pmdbg_gpio_irq_index = 0;
}

int wakeup_source_gpio_add_irq(unsigned int irq)
{
	if (pmdbg_gpio_irq_index < PMDBG_IRQ_LIST_SIZE) {
		pmdbg_gpio_irq[pmdbg_gpio_irq_index] = irq;
		pmdbg_gpio_irq_index++;
		return 0;
	} else {
		return -ENOBUFS;
	}
}

void wakeup_source_gic_cleanup(void)
{
	pmdbg_gic_irq_index = 0;
}

int wakeup_source_gic_add_irq(unsigned int irq)
{
	if (pmdbg_gic_irq_index < PMDBG_IRQ_LIST_SIZE) {
		pmdbg_gic_irq[pmdbg_gic_irq_index] = irq;
		pmdbg_gic_irq_index++;
		return 0;
	} else {
		return -ENOBUFS;
	}
}

void wakeup_source_pm8xxx_cleanup(void)
{
	pmdbg_pm8xxx_irq_index = 0;
}

int wakeup_source_pm8xxx_add_irq(unsigned int irq)
{
	if (pmdbg_pm8xxx_irq_index < PMDBG_IRQ_LIST_SIZE) {
		pmdbg_pm8xxx_irq[pmdbg_pm8xxx_irq_index] = irq;
		pmdbg_pm8xxx_irq_index++;
		return 0;
	} else {
		return -ENOBUFS;
	}
}

static int __devinit pmdbg_driver_probe(struct platform_device *pdev)
{
	pr_debug("pmdbg_driver_probe\n");
	return 0;
}

static int __devexit pmdbg_driver_remove(struct platform_device *pdev)
{
	pr_debug("pmdbg_driver_remove\n");
	return 0;
}

void wakeup_source_uevent_env(char *buf, char *tag, unsigned int irqs[],
				int index)
{
	int i, len;

	if (index > 0) {
		if (index > PMDBG_IRQ_LIST_SIZE)
			index = PMDBG_IRQ_LIST_SIZE;
		len = 0;
		for (i = 0; i < index; i++) {
			if (i == 0)
				len += snprintf(buf,
					PMDBG_UEVENT_ENV_BUFF - len,
					"%s=%d", tag, irqs[i]);
			else
				len += snprintf(buf + len,
					PMDBG_UEVENT_ENV_BUFF - len,
					",%d", irqs[i]);
			if (len == PMDBG_UEVENT_ENV_BUFF)
				break;
		}
	}
}

static int pmdbg_driver_resume(struct device *dev)
{
	char *envp[4];
	char buf[3][PMDBG_UEVENT_ENV_BUFF];
	int env_index = 0;

	pr_debug("pmdbg_driver_resume: send uevent\n");
	if (pmdbg_gic_irq > 0) {
		wakeup_source_uevent_env(buf[env_index], "GIC",
					pmdbg_gic_irq,
					pmdbg_gic_irq_index);
		pmdbg_gic_irq_index = 0;
		envp[env_index] = buf[env_index];
		env_index++;
	}

	if (pmdbg_gpio_irq > 0) {
		wakeup_source_uevent_env(buf[env_index], "GPIO",
					pmdbg_gpio_irq,
					pmdbg_gpio_irq_index);
		pmdbg_gpio_irq_index = 0;
		envp[env_index] = buf[env_index];
		env_index++;
	}

	if (pmdbg_pm8xxx_irq_index > 0) {
		wakeup_source_uevent_env(buf[env_index], "PM8xxx",
					pmdbg_pm8xxx_irq,
					pmdbg_pm8xxx_irq_index);
		pmdbg_pm8xxx_irq_index = 0;
		envp[env_index] = buf[env_index];
		env_index++;
	}

	envp[env_index] = NULL;
	kobject_uevent_env(&dev->kobj, KOBJ_ONLINE, envp);
	return 0;
}

static struct platform_device pmdbg_device = {
	.name		= "pm_dbg",
	.id		= -1,
};

static const struct dev_pm_ops pmdbg_pm_ops = {
	.resume		= pmdbg_driver_resume,
};

static struct platform_driver pmdbg_driver = {
	.probe		= pmdbg_driver_probe,
	.remove		= __devexit_p(pmdbg_driver_remove),
	.driver		= {
			.name	= "pm_dbg",
			.owner	= THIS_MODULE,
			.pm	= &pmdbg_pm_ops,
	},
};

static int __init pmdbg_init(void)
{
	int err;
	pmdbg_suspend_notifier.notifier_call = pmdbg_suspend_notifier_call;
	register_pm_notifier(&pmdbg_suspend_notifier);
	register_early_suspend(&pmdbg_early_suspend_desc);
	err = platform_device_register(&pmdbg_device);
	pr_debug("pmdbg_device register %d\n", err);
	err = platform_driver_register(&pmdbg_driver);
	pr_debug("pmdbg_driver register %d\n", err);

	wakeup_source_gpio_cleanup();
	wakeup_source_gic_cleanup();

	return 0;
}

static void  __exit pmdbg_exit(void)
{
	unregister_early_suspend(&pmdbg_early_suspend_desc);
	unregister_pm_notifier(&pmdbg_suspend_notifier);
	platform_driver_unregister(&pmdbg_driver);
	platform_device_unregister(&pmdbg_device);
}

core_initcall(pmdbg_init);
module_exit(pmdbg_exit);

MODULE_ALIAS("platform:pm_dbg");
MODULE_DESCRIPTION("PM Debug driver");
MODULE_AUTHOR("Motorola");
MODULE_LICENSE("GPL v2");
