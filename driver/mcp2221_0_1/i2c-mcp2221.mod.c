#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0xd2901226, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x226c32c1, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xd8a7a277, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xfa1499e8, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xe5953ff0, __VMLINUX_SYMBOL_STR(i2c_add_adapter) },
	{ 0xf6a5c7f4, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0xc277280a, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x74c756f2, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x28318305, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x9e88526, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xeb1b3f7a, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0x910e0dc, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x84f43e8d, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa6bbd805, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x84cc4934, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xe807b57a, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x6075bbd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xf08242c2, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x2207a57f, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x75f68bb7, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xa31c8204, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x57aee259, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0xcb1fa5b3, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xbfbf368f, __VMLINUX_SYMBOL_STR(i2c_del_adapter) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v04D8p00DDd*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "7BDBCACEC4B26CC62660E4C");
