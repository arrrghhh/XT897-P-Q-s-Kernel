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
	{ 0x4cad71b3, "tcp_reno_cong_avoid" },
	{ 0xb4e78c93, "tcp_reno_ssthresh" },
	{ 0xaf9816b1, "tcp_register_congestion_control" },
	{ 0xb54533f7, "usecs_to_jiffies" },
	{ 0xc4506289, "nla_put" },
	{ 0x5f754e5a, "memset" },
	{ 0x7f24de73, "jiffies_to_usecs" },
	{ 0xe0d5639f, "tcp_unregister_congestion_control" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x7d11c268, "jiffies" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

