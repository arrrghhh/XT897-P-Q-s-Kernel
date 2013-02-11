#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x33bdc7f0, "module_layout" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0x613e563a, "input_event" },
	{ 0x9d669763, "memcpy" },
	{ 0x39c96550, "input_free_device" },
	{ 0xd7f0e68c, "input_mt_destroy_slots" },
	{ 0x79007eb4, "input_register_device" },
	{ 0x26282003, "input_mt_init_slots" },
	{ 0xfc8676fb, "input_set_abs_params" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0xfccb7bc1, "input_allocate_device" },
	{ 0x9635099c, "platform_device_unregister" },
	{ 0x873a31c6, "sysfs_remove_group" },
	{ 0xedd330b9, "input_unregister_device" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xdeac40e9, "sysfs_create_group" },
	{ 0x27e1a049, "printk" },
	{ 0x57e83953, "platform_device_register_resndata" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

