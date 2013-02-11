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
	{ 0x528c709d, "simple_read_from_buffer" },
	{ 0x701d0ebd, "snprintf" },
	{ 0x772b5423, "platform_driver_register" },
	{ 0xad998077, "complete" },
	{ 0xe19271d3, "misc_register" },
	{ 0xc3593841, "msm_bus_scale_register_client" },
	{ 0x544253c4, "qce_hw_support" },
	{ 0x555a9f39, "dev_set_drvdata" },
	{ 0xe4f29308, "qce_open" },
	{ 0x9545af6d, "tasklet_init" },
	{ 0xfc6e8775, "__init_waitqueue_head" },
	{ 0x93fca811, "__get_free_pages" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x76c6f7a2, "mem_section" },
	{ 0xda95f8b8, "meminfo" },
	{ 0x701169c9, "vmeminfo" },
	{ 0x52a48ea2, "put_pmem_file" },
	{ 0x37a0cba, "kfree" },
	{ 0x5d4d0707, "get_pmem_file" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x2f4ea1ac, "wait_for_completion" },
	{ 0x8ddab831, "_raw_spin_unlock_irqrestore" },
	{ 0x1a9b678e, "_raw_spin_lock_irqsave" },
	{ 0xad90232b, "qce_process_sha_req" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0x9d669763, "memcpy" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xb03f0e17, "qce_ablk_cipher_req" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xdfabe0ff, "scm_call" },
	{ 0xa1b21da9, "kmalloc_caches" },
	{ 0xc365cac0, "kmem_cache_alloc" },
	{ 0x7a4497db, "kzfree" },
	{ 0x27e1a049, "printk" },
	{ 0x16b02824, "mutex_unlock" },
	{ 0x78f062cb, "msm_bus_scale_client_update_request" },
	{ 0xe5981256, "mutex_lock" },
	{ 0x82072614, "tasklet_kill" },
	{ 0x302e19cb, "misc_deregister" },
	{ 0xcf8cc5ee, "msm_bus_scale_unregister_client" },
	{ 0x575c81e1, "qce_close" },
	{ 0x95968a3, "dev_get_drvdata" },
	{ 0xf1f2333d, "platform_driver_unregister" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=qce40";


MODULE_INFO(srcversion, "01ADB61CF65176B8CA28B67");
