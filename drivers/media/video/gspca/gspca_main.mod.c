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
	{ 0xf9a482f9, "msleep" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x555a9f39, "dev_set_drvdata" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0xc87c1f84, "ktime_get" },
	{ 0x7a373a27, "usb_kill_urb" },
	{ 0xed205d6b, "__video_register_device" },
	{ 0x16b02824, "mutex_unlock" },
	{ 0x999e8297, "vfree" },
	{ 0xfc6e8775, "__init_waitqueue_head" },
	{ 0xdd0a2ba2, "strlcat" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x5f754e5a, "memset" },
	{ 0xaf473139, "mutex_lock_interruptible" },
	{ 0x575551a1, "__mutex_init" },
	{ 0x27e1a049, "printk" },
	{ 0x66aadfe0, "video_unregister_device" },
	{ 0xd2b5b05d, "usb_set_interface" },
	{ 0x328a05f1, "strncpy" },
	{ 0xe5981256, "mutex_lock" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x32a109c1, "usb_free_coherent" },
	{ 0x2196324, "__aeabi_idiv" },
	{ 0xd1384d0f, "vm_insert_page" },
	{ 0xf7a4c27c, "module_put" },
	{ 0xf2e03566, "usb_submit_urb" },
	{ 0xc365cac0, "kmem_cache_alloc" },
	{ 0x8ac6793, "video_devdata" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0x79007eb4, "input_register_device" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0xefbef8a7, "usb_clear_halt" },
	{ 0x39c96550, "input_free_device" },
	{ 0xa0b04675, "vmalloc_32" },
	{ 0x341dbfa3, "__per_cpu_offset" },
	{  0xf1338, "__wake_up" },
	{ 0x37a0cba, "kfree" },
	{ 0x9d669763, "memcpy" },
	{ 0xedd330b9, "input_unregister_device" },
	{ 0x69ff5332, "prepare_to_wait" },
	{ 0xbc3d21af, "finish_wait" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x8c707bc2, "usb_ifnum_to_if" },
	{ 0x701d0ebd, "snprintf" },
	{ 0x1a45de75, "vmalloc_to_page" },
	{ 0x8bb3c2fa, "usb_alloc_coherent" },
	{ 0x95968a3, "dev_get_drvdata" },
	{ 0x88435b7b, "usb_free_urb" },
	{ 0x1a6e6db3, "video_ioctl2" },
	{ 0x1d4cd00d, "usb_alloc_urb" },
	{ 0xdf4c8767, "ns_to_timeval" },
	{ 0xfccb7bc1, "input_allocate_device" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

