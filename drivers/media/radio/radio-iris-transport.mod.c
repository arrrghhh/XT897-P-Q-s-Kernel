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
	{ 0x82df6143, "smd_read_avail" },
	{ 0xa60663f2, "smd_read" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x323199f4, "kfree_skb" },
	{ 0x86905bab, "smd_write" },
	{ 0x5dc02a6f, "radio_hci_unregister_dev" },
	{ 0x37a0cba, "kfree" },
	{ 0x858c33ab, "radio_hci_recv_frame" },
	{ 0x9d669763, "memcpy" },
	{ 0x134ed5b1, "skb_put" },
	{ 0xdd1509d8, "__alloc_skb" },
	{ 0x8949858b, "schedule_work" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0xa1b21da9, "kmalloc_caches" },
	{ 0x27e1a049, "printk" },
	{ 0xd9b98fc9, "radio_hci_register_dev" },
	{ 0x7c6e75b5, "smd_disable_read_intr" },
	{ 0x66983121, "smd_named_open_on_edge" },
	{ 0x9545af6d, "tasklet_init" },
	{ 0xc365cac0, "kmem_cache_alloc" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xd73979df, "smd_close" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

