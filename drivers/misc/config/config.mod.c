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
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xff178f6, "__aeabi_idivmod" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x14ddee08, "single_open" },
	{ 0xe5faab09, "single_release" },
	{ 0x7acbd3bd, "seq_printf" },
	{ 0x255de402, "remove_proc_entry" },
	{ 0x12b89148, "filp_close" },
	{ 0x6011766a, "seq_read" },
	{ 0xaecb95b4, "kernel_read" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x7b343885, "proc_mkdir" },
	{ 0x27e1a049, "printk" },
	{ 0xc365cac0, "kmem_cache_alloc" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x4e5e554, "create_proc_entry" },
	{ 0xa974a3ec, "seq_lseek" },
	{ 0x37a0cba, "kfree" },
	{ 0x9d669763, "memcpy" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x708fa95e, "filp_open" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

