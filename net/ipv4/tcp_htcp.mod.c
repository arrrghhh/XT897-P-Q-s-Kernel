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
	{ 0x3ec8886f, "param_ops_int" },
	{ 0xaf9816b1, "tcp_register_congestion_control" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x792751f7, "tcp_slow_start" },
	{ 0xef38ddca, "tcp_is_cwnd_limited" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0xb54533f7, "usecs_to_jiffies" },
	{ 0xe0d5639f, "tcp_unregister_congestion_control" },
	{ 0x7d11c268, "jiffies" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xe707d823, "__aeabi_uidiv" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

