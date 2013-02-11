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
	{ 0xc3fe87c8, "param_ops_uint" },
	{ 0x3ec8886f, "param_ops_int" },
	{ 0x97767d73, "no_llseek" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x84c42967, "spi_new_device" },
	{ 0x63e4c850, "spi_busnum_to_master" },
	{ 0x9d669763, "memcpy" },
	{ 0xf6365777, "spi_register_driver" },
	{ 0xae920176, "__class_create" },
	{ 0x2d96f213, "__register_chrdev" },
	{ 0x46e13d6b, "put_device" },
	{ 0xe71e7209, "spi_setup" },
	{ 0x6d4d2fe8, "get_device" },
	{ 0xad998077, "complete" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x2f4ea1ac, "wait_for_completion" },
	{ 0xce33c40a, "spi_async" },
	{ 0x5f754e5a, "memset" },
	{ 0x8e9e431a, "nonseekable_open" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xacda86f3, "class_destroy" },
	{ 0xfe481733, "driver_unregister" },
	{ 0xda7765e9, "device_unregister" },
	{ 0xa1b21da9, "kmalloc_caches" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0x498e2851, "device_create" },
	{ 0xd3dbfbc4, "_find_first_zero_bit_le" },
	{ 0x575551a1, "__mutex_init" },
	{ 0xc365cac0, "kmem_cache_alloc" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x16b02824, "mutex_unlock" },
	{ 0x37a0cba, "kfree" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0xfb54c9ba, "device_destroy" },
	{ 0xe5981256, "mutex_lock" },
	{ 0xaea99e9d, "_raw_spin_unlock_irq" },
	{ 0x555a9f39, "dev_set_drvdata" },
	{ 0xe551272c, "_raw_spin_lock_irq" },
	{ 0x95968a3, "dev_get_drvdata" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

