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
	{ 0x772b5423, "platform_driver_register" },
	{ 0x73c25fb3, "rfkill_register" },
	{ 0xb5ffdea7, "rfkill_init_sw_state" },
	{ 0x5fc8a995, "rfkill_alloc" },
	{ 0x1556b68, "dev_err" },
	{ 0x555a9f39, "dev_set_drvdata" },
	{ 0x4bf69a5e, "rfkill_destroy" },
	{ 0xd4fb5e25, "rfkill_unregister" },
	{ 0x95968a3, "dev_get_drvdata" },
	{ 0xf1f2333d, "platform_driver_unregister" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "5135EFD2BE07BA9DA21C97E");
