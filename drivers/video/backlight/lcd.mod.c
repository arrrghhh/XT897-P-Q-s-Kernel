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
	{ 0xa1b21da9, "kmalloc_caches" },
	{ 0x5934392b, "fb_register_client" },
	{ 0x555a9f39, "dev_set_drvdata" },
	{ 0x20000329, "simple_strtoul" },
	{ 0x16b02824, "mutex_unlock" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x7620cd4f, "device_register" },
	{ 0x11089ac7, "_ctype" },
	{ 0x575551a1, "__mutex_init" },
	{ 0x27e1a049, "printk" },
	{ 0xe5981256, "mutex_lock" },
	{ 0xc365cac0, "kmem_cache_alloc" },
	{ 0x37a0cba, "kfree" },
	{ 0xacda86f3, "class_destroy" },
	{ 0xcc36f32e, "fb_unregister_client" },
	{ 0xda7765e9, "device_unregister" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x4656c9c9, "dev_set_name" },
	{ 0xae920176, "__class_create" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

