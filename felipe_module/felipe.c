#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Luis Felipe Hernandez");
MODULE_DESCRIPTION("USB Flash Drive Driver exercise");
MODULE_VERSION("0.1");
/* Prev Example using cli args
 * #include <linux/moduleparam.h>
 * static int cli_arg = 0;
 * module_param(cli_arg, int, 0644);
 */

/*
 * Alternatively using macros
 * module_param(cli_arg, int, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
 */

static struct usb_device_id usb_table[] = {
	{ USB_DEVICE(0x21c4, 0x0809) },
	{}
};
MODULE_DEVICE_TABLE(usb, usb_table);

static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	pr_alert("FELIPE MODULE: USB flash drive plugged in (VID: %04X, PID: %04X)\n", id->idVendor, id->idProduct);
	return 0;
}

static void usb_disconnect(struct usb_interface *interface)
{
	pr_alert("FELIPE MODULE: USB flash drive removed\n");
}

static struct usb_driver custom_usb_driver = {
	.name = "felipe_usb_flash_driver",
	.id_table = usb_table,
	.probe = usb_probe,
	.disconnect = usb_disconnect,
};

static int __init mod_init(void)
{
	int result;
	result = usb_register(&custom_usb_driver);
	if (result) {
		pr_alert("FELIPE MODULE: usb_register failed. Error: %d\n", result);
	} else {
		pr_alert("FELIPE MODULE: USB driver registered succesfully\n");
	}
	return result;
}

static void __exit cleanup_mod(void)
{
	usb_deregister(&drv);
	pr_info("FELIPE MODULE: USB driver unregistered\n");
}

module_init(init_mod);
module_exit(cleanup_mod);
