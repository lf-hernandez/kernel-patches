#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static int cli_arg = 0;
module_param(cli_arg, int, 0644);
/*
 * Alternatively using macros
 * module_param(cli_arg, int, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
 */
static int init_mod(void)
{
	pr_alert("Hello\nModule loaded into kernel with param: %d\n", cli_arg);
	return 0;
}

static void cleanup_mod(void)
{
	pr_alert("Module removed from kernel\nGoodbye\n");
}

module_init(init_mod);
module_exit(cleanup_mod);
