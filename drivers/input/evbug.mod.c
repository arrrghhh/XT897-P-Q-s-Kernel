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
	{ 0xee243e4b, "input_register_handler" },
	{ 0xa1b21da9, "kmalloc_caches" },
	{ 0x6c0ac53d, "input_open_device" },
	{ 0x396bc29d, "input_register_handle" },
	{ 0xc365cac0, "kmem_cache_alloc" },
	{ 0x37a0cba, "kfree" },
	{ 0x7b41b714, "input_unregister_handle" },
	{ 0xc9c9518e, "input_close_device" },
	{ 0x27e1a049, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xf79d1183, "input_unregister_handler" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("input:b*v*p*e*-e*k*r*a*m*l*s*f*w*");
