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
	{ 0xf41affc5, "eth_change_mtu" },
	{ 0xdbe0d8a9, "eth_validate_addr" },
	{ 0xf6365777, "spi_register_driver" },
	{ 0xfe481733, "driver_unregister" },
	{ 0xfcec0987, "enable_irq" },
	{ 0x7fd3d2e9, "__netif_schedule" },
	{ 0x2a3aa678, "_test_and_clear_bit" },
	{ 0x87f8aada, "netif_rx" },
	{ 0xd4d20e32, "eth_type_trans" },
	{ 0x134ed5b1, "skb_put" },
	{ 0x7ad2ac20, "__netdev_alloc_skb" },
	{ 0x27bbf221, "disable_irq_nosync" },
	{ 0xce1a4c6e, "register_netdev" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0x79aa04a2, "get_random_bytes" },
	{ 0x3ee07391, "netdev_warn" },
	{ 0x555a9f39, "dev_set_drvdata" },
	{ 0x575551a1, "__mutex_init" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x22635797, "regulator_enable" },
	{ 0xc68546cb, "regulator_get" },
	{ 0x1556b68, "dev_err" },
	{ 0x5a7b4886, "alloc_etherdev_mqs" },
	{ 0xf3e2d53, "mii_ethtool_gset" },
	{ 0x47ad62bd, "mii_ethtool_sset" },
	{ 0x73e20c1c, "strlcpy" },
	{ 0x955aee5b, "mii_nway_restart" },
	{ 0x1f93d706, "mii_link_ok" },
	{ 0x27cb133b, "eeprom_93cx6_multiread" },
	{ 0x822222db, "eeprom_93cx6_write" },
	{ 0x98bb5a22, "eeprom_93cx6_read" },
	{ 0x63d2ff63, "eeprom_93cx6_wren" },
	{ 0x58c459f3, "skb_queue_tail" },
	{ 0x178ba18c, "_raw_spin_unlock" },
	{ 0x8949858b, "schedule_work" },
	{ 0x71c90087, "memcmp" },
	{ 0xc4097c34, "_raw_spin_lock" },
	{ 0xfaf98462, "bitrev32" },
	{ 0xa34f1ef5, "crc32_le" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x80639ded, "generic_mii_ioctl" },
	{ 0x429434cf, "free_netdev" },
	{ 0xfe990052, "gpio_free" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x70b7de90, "unregister_netdev" },
	{ 0x5c58d00b, "regulator_put" },
	{ 0x3c8dbfeb, "regulator_disable" },
	{ 0x32fd9529, "_dev_info" },
	{ 0x55c3f244, "netif_device_detach" },
	{ 0x92b57248, "flush_work" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0x27e1a049, "printk" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x4fa16f9c, "netdev_info" },
	{ 0xffb5bd61, "consume_skb" },
	{ 0xfda37321, "skb_dequeue" },
	{ 0x3ad4a4b5, "netif_device_attach" },
	{ 0x95968a3, "dev_get_drvdata" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0xa5bf123e, "netdev_printk" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x9d669763, "memcpy" },
	{ 0x16b02824, "mutex_unlock" },
	{ 0xe5981256, "mutex_lock" },
	{ 0x5c413d6c, "netdev_err" },
	{ 0x4f74239f, "spi_sync" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=eeprom_93cx6";

