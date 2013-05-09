/*
 *  ALSA headset detection to H2W device  converter 
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/switch.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/slab.h>




struct alsa_to_h2w_data {
	struct switch_dev sdev;
};

static char *name_hadsets_with_mic = "Headset with a mic";
static char *name_hadsets_no_mic = "Headphone";
static char *name_hadsets_pull_out = "No Device";
static char *state_hadsets_with_mic = "1";
static char *state_hadsets_no_mic = "2";
static char *state_hadsets_pull_out = "0";

static struct alsa_to_h2w_data *headset_switch_data;

void alsa_to_h2w_headset_report(int state)
{
	if (headset_switch_data)
		switch_set_state(&headset_switch_data->sdev, state);
}
EXPORT_SYMBOL_GPL(alsa_to_h2w_headset_report);

static ssize_t headset_print_name(struct switch_dev *sdev, char *buf)
{
	const char *name;

	if (!buf)
		return -EINVAL;

	switch (switch_get_state(sdev)) {
	case 0:
		name = name_hadsets_pull_out;
		break;
	case 1:
		name = name_hadsets_with_mic;
		break;
	case 2:
		name = name_hadsets_no_mic;
		break;
	default:
		name = NULL;
		break;
	}

	if (name)
		return sprintf(buf, "%s\n", name);
	else
		return -EINVAL;
}

static ssize_t headset_print_state(struct switch_dev *sdev, char *buf)
{
	const char *state;

	if (!buf)
		return -EINVAL;

	switch (switch_get_state(sdev)) {
	case 0:
		state = state_hadsets_pull_out;
		break;
	case 1:
		state = state_hadsets_with_mic;
		break;
	case 2:
		state = state_hadsets_no_mic;
		break;
	default:
		state = NULL;
		break;
	}

	if (state)
		return sprintf(buf, "%s\n", state);
	else
		return -EINVAL;
}

static int alsa_to_h2w_probe(struct platform_device *pdev)
{
	struct alsa_to_h2w_data *switch_data;
	int ret = 0;

	switch_data = kzalloc(sizeof(struct alsa_to_h2w_data), GFP_KERNEL);
	if (!switch_data)
		return -ENOMEM;
	headset_switch_data = switch_data;

	switch_data->sdev.name = "h2w";
	switch_data->sdev.print_name = headset_print_name;
	switch_data->sdev.print_state = headset_print_state;

	ret = switch_dev_register(&switch_data->sdev);
	if (ret < 0)
		goto err_switch_dev_register;

	platform_set_drvdata(pdev, switch_data);
	return 0;

err_switch_dev_register:
	kfree(switch_data);
	return ret;
}

static int __devexit alsa_to_h2w_remove(struct platform_device *pdev)
{
	struct alsa_to_h2w_data *switch_data = platform_get_drvdata(pdev);

	switch_dev_unregister(&switch_data->sdev);
	kfree(switch_data);
	headset_switch_data = NULL;

	return 0;
}

static struct platform_driver alsa_to_h2w_driver = {
	.probe		= alsa_to_h2w_probe,
	.remove		= __devexit_p(alsa_to_h2w_remove),
	.driver		= {
		.name	= "alsa-to-h2w",
		.owner	= THIS_MODULE,
	},
};

static int __init alsa_to_h2w_init(void)
{
	return platform_driver_register(&alsa_to_h2w_driver);
}

static void __exit alsa_to_h2w_exit(void)
{
	platform_driver_unregister(&alsa_to_h2w_driver);
}

module_init(alsa_to_h2w_init);
module_exit(alsa_to_h2w_exit);

MODULE_AUTHOR("Vladimir Karpovich (Vladimir.Karpovich@motorola.com)");
MODULE_DESCRIPTION("Headset ALSA to H2w driver");
MODULE_LICENSE("GPL");
