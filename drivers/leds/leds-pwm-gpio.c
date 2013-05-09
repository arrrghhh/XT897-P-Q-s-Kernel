/*
 * LEDs driver for GPIOs with blinking done via Qualcomm LPGs
 *
 * Copyright (C) 2011 Motorola Mobility, Inc
 * Alina Yakovleva <qvdh43@motorola.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/leds.h>
#include <linux/pwm.h>
#include <linux/leds-pwm-gpio.h>
#include <linux/slab.h>
#include <linux/workqueue.h>

#include <asm/gpio.h>

struct pwm_gpio_led_data {
	struct led_classdev cdev;
	struct pwm_device *pwm;
	unsigned gpio;
	unsigned pwm_id;
	struct work_struct work;
	unsigned long delay_on;
	unsigned long delay_off;
	u8 new_level;
	u8 can_sleep;
	u8 active_low;
	u8 blinking;
};

static int pwm_gpio_blink_set(struct led_classdev *led_cdev,
	unsigned long *delay_on, unsigned long *delay_off)
{
	struct pwm_gpio_led_data *led_dat =
		container_of(led_cdev, struct pwm_gpio_led_data, cdev);
	int ret = 0;

	if (delay_on && delay_off) {
		ret = pwm_config(led_dat->pwm, *delay_on, *delay_on + *delay_off);
		if (ret) {
			pr_err("%s: pwm_config error %d\n", __func__, ret);
			return ret;
		}
		ret = pwm_enable(led_dat->pwm);
		if (ret) {
			pr_err("%s: pwm_enable error %d\n", __func__, ret);
			return ret;
		}
		led_dat->blinking = 1;
		led_dat->delay_on = *delay_on;
		led_dat->delay_off = *delay_off;
	} else {
		led_dat->blinking = 0;
		led_dat->delay_on = 0;
		led_dat->delay_off = 0;
		pwm_disable(led_dat->pwm);
	}

	return 0;
}

static void pwm_gpio_led_work(struct work_struct *work)
{
	struct pwm_gpio_led_data *led_dat =
		container_of(work, struct pwm_gpio_led_data, work);

	if (led_dat->blinking)
		pwm_gpio_blink_set(&led_dat->cdev, NULL, NULL);
	gpio_set_value_cansleep(led_dat->gpio, led_dat->new_level);
}

static void pwm_gpio_led_set(struct led_classdev *led_cdev,
	enum led_brightness value)
{
	struct pwm_gpio_led_data *led_dat =
		container_of(led_cdev, struct pwm_gpio_led_data, cdev);
	int level;

	pr_info("%s: %s, %d\n", __func__, led_dat->cdev.name, value);
	if (value == LED_OFF)
		level = 0;
	else
		level = 1;

	if (led_dat->active_low)
		level = !level;

	/* Setting GPIOs with I2C/etc requires a task context, and we don't
	 * seem to have a reliable way to know if we're already in one; so
	 * let's just assume the worst.
	 */
	led_dat->new_level = level;
	if (led_dat->can_sleep) {
		schedule_work(&led_dat->work);
	} else {
		if (led_dat->blinking)
			pwm_gpio_blink_set(led_cdev, NULL, NULL);
		gpio_set_value(led_dat->gpio, level);
	}
}

static ssize_t pwm_gpio_blink_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct pwm_gpio_led_data *led_dat = dev_get_drvdata(dev);

	sprintf(buf, "brightness=%d, on=%ld ms, off=%ld ms, gpio(%d)=%d\n",
		led_dat->cdev.brightness,
		led_dat->delay_on/1000, led_dat->delay_off/1000,
		led_dat->gpio, gpio_get_value_cansleep(led_dat->gpio));
	return strlen(buf)+1;
}

static ssize_t pwm_gpio_blink_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct pwm_gpio_led_data *led_dat = dev_get_drvdata(dev);
	unsigned long led_on = 0;
	unsigned long led_off = 0;
	char *ptr;
	//static unsigned calls = 0;

	led_on = simple_strtoul(buf, &ptr, 10);
	if (!led_on) {
		pr_info("%s: led_on = 0\n", __func__);
		return pwm_gpio_blink_set(&led_dat->cdev, NULL, NULL);
	}
	if (ptr) {
		while(*ptr == ' ' || *ptr == '\t')
			ptr++;
	}
	led_off = simple_strtoul(ptr, NULL, 10);
	pr_info("%s: led_on = %d, led_off = %d\n", __func__,
		(unsigned)led_on, (unsigned)led_off);
	/* Convert to microseconds */
	led_on *= 1000;
	led_off *= 1000;
	return pwm_gpio_blink_set(&led_dat->cdev, &led_on, &led_off);
}

static DEVICE_ATTR(blink, 0664, pwm_gpio_blink_show, pwm_gpio_blink_store);

static int __devinit create_pwm_gpio_led(const struct led_pwm_gpio *led,
	struct pwm_gpio_led_data *led_dat, struct device *parent)
{
	int ret, state;

	led_dat->gpio = -1;
	led_dat->pwm_id = -1;

	/* skip leds that aren't available */
	if (!gpio_is_valid(led->gpio)) {
		pr_err("%s: skipping unavailable LED gpio %d (%s)\n",
			__func__, led->gpio, led->name);
		return 0;
	}

	ret = gpio_request(led->gpio, led->name);
	if (ret < 0) {
		pr_err("%s: gpio_request(%d, %s) failed\n",
			__func__, led->gpio, led->name);
		return ret;
	}

	led_dat->cdev.name = led->name;
	led_dat->cdev.default_trigger = led->default_trigger;
	led_dat->gpio = led->gpio;
	led_dat->pwm_id = led->pwm_id;
	led_dat->active_low = led->active_low;
	led_dat->blinking = 0;
	led_dat->can_sleep = gpio_cansleep(led->gpio);
	led_dat->cdev.brightness_set = pwm_gpio_led_set;
	if (led->default_state == LEDS_GPIO_DEFSTATE_KEEP)
		state = !!gpio_get_value(led_dat->gpio) ^ led_dat->active_low;
	else
		state = (led->default_state == LEDS_GPIO_DEFSTATE_ON);
	led_dat->cdev.brightness = state ? LED_FULL : LED_OFF;
	if (!led->retain_state_suspended)
		led_dat->cdev.flags |= LED_CORE_SUSPENDRESUME;

	ret = gpio_direction_output(led_dat->gpio, led_dat->active_low ^ state);
	if (ret < 0) {
		pr_err("%s: gpio_direction_output(%d, %d) failed\n",
			__func__, led_dat->gpio, led_dat->active_low ^ state);
		goto err;
	}
		
	INIT_WORK(&led_dat->work, pwm_gpio_led_work);

	ret = led_classdev_register(parent, &led_dat->cdev);
	if (ret < 0) {
		pr_err("%s: unable to register LED class for %s\n",
			__func__, led_dat->cdev.name);
		goto err;
	}
	pr_info("%s: LED class %s, gpio %d, can sleep = %d\n",
		__func__, led->name, led->gpio, led_dat->can_sleep);
	/* See if this LED is blinking with PWM */
	if (led_dat->pwm_id < 0)
		return 0;
	ret = device_create_file(led_dat->cdev.dev, &dev_attr_blink);
	if (ret) {
		pr_err("%s: unable to create blink device file for %s\n",
			__func__, led_dat->cdev.name);
		goto err_blink;
	}
	pr_info("%s: created blink device file for %s\n",
		__func__, led_dat->cdev.name);
	led_dat->pwm = pwm_request(led_dat->pwm_id, led_dat->cdev.name);
	if (!led_dat->pwm) {
		pr_err("%s: pwm_request error for %s, pwm_id %d\n",
			__func__, led_dat->cdev.name, led_dat->pwm_id);
		goto err_pwm_request;
	}
	pr_info("%s: requested pwm for %s, pwm_id=%d\n",
		__func__, led_dat->cdev.name, led_dat->pwm_id);

	return 0;

err_pwm_request:
	device_remove_file(led_dat->cdev.dev, &dev_attr_blink);
err_blink:
	led_classdev_unregister(&led_dat->cdev);
err:
	gpio_free(led_dat->gpio);
	return ret;
}

static void delete_pwm_gpio_led(struct pwm_gpio_led_data *led)
{
	if (!gpio_is_valid(led->gpio))
		return;
	device_remove_file(led->cdev.dev, &dev_attr_blink);
	led_classdev_unregister(&led->cdev);
	cancel_work_sync(&led->work);
	gpio_free(led->gpio);
	pwm_free(led->pwm);
}

static int __devinit pwm_gpio_led_probe(struct platform_device *pdev)
{
	struct led_pwm_gpio_platform_data *pdata = pdev->dev.platform_data;
	struct pwm_gpio_led_data *leds_data;
	int i, ret = 0;

	if (!pdata) {
		pr_err("%s: no platform data supplied\n", __func__);
		return -EAGAIN;
	}

	leds_data = kzalloc(sizeof(struct pwm_gpio_led_data) * pdata->num_leds,
				GFP_KERNEL);
	if (!leds_data) {
		pr_err("%s: kzalloc error allocating leds_data\n", __func__);
		return -ENOMEM;
	}

	pr_info("%s: num_leds is %d\n", __func__, pdata->num_leds);
	for (i = 0; i < pdata->num_leds; i++) {
		ret = create_pwm_gpio_led(&pdata->leds[i], &leds_data[i], &pdev->dev);
		if (ret < 0)
			goto err;
	}

	platform_set_drvdata(pdev, leds_data);

	return 0;

err:
	for (i = i - 1; i >= 0; i--)
		delete_pwm_gpio_led(&leds_data[i]);

	kfree(leds_data);

	return ret;
}

static int __devexit pwm_gpio_led_remove(struct platform_device *pdev)
{
	int i;
	struct led_pwm_gpio_platform_data *pdata = pdev->dev.platform_data;
	struct pwm_gpio_led_data *leds_data;

	leds_data = platform_get_drvdata(pdev);

	for (i = 0; i < pdata->num_leds; i++)
		delete_pwm_gpio_led(&leds_data[i]);

	kfree(leds_data);

	return 0;
}

static struct platform_driver pwm_gpio_led_driver = {
	.probe		= pwm_gpio_led_probe,
	.remove		= __devexit_p(pwm_gpio_led_remove),
	.driver		= {
		.name	= "pwm_gpio_leds",
		.owner	= THIS_MODULE,
	},
};

static int __init pwm_gpio_led_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&pwm_gpio_led_driver);
	if (ret)
		pr_err("%s: unable to register platform driver\n", __func__);
	return ret;
}

static void __exit pwm_gpio_led_exit(void)
{
	platform_driver_unregister(&pwm_gpio_led_driver);
}

module_init(pwm_gpio_led_init);
module_exit(pwm_gpio_led_exit);

MODULE_AUTHOR("Alina Yakovleva <qvdh43@motorola.com>");
MODULE_DESCRIPTION("GPIO/PWM LED driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:pwm-gpio-leds");
