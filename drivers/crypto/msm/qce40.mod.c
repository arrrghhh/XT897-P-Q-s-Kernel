#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x33bdc7f0, "module_layout" },
	{ 0xa1b21da9, "kmalloc_caches" },
	{ 0xd2121e75, "clk_reset" },
	{ 0x7d36b0de, "clk_enable" },
	{ 0x1bcd0f4f, "dma_unmap_sg" },
	{ 0x82de88e9, "dma_map_sg" },
	{ 0x247e89fc, "clk_disable" },
	{ 0x2e1ca751, "clk_put" },
	{ 0xd5152710, "sg_next" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x1556b68, "dev_err" },
	{ 0xe4d14011, "msm_dmov_enqueue_cmd" },
	{ 0x64349784, "dma_free_coherent" },
	{ 0x79a3bf25, "platform_get_resource" },
	{ 0x7e088ad5, "dma_alloc_coherent" },
	{ 0x32fd9529, "_dev_info" },
	{ 0xc365cac0, "kmem_cache_alloc" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x4543f03b, "clk_get" },
	{ 0x461496, "clk_set_rate" },
	{ 0x851c94, "platform_get_resource_byname" },
	{ 0x37a0cba, "kfree" },
	{ 0x9d669763, "memcpy" },
	{ 0x45a55ec8, "__iounmap" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x8ff97ceb, "__msm_ioremap" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "024B2632D919B85C4C856DA");
