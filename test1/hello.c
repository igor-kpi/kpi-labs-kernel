#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

#include "world.h"

MODULE_AUTHOR("Ihor <igor-kpi@ukr.net>");
MODULE_DESCRIPTION("Hello world");
MODULE_LICENSE("GPL");

static uint count = 1;

module_param(count, uint, S_IRUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(count, "Number of iterations");

static int __init hello_init(void) {
    if (count > 10) {
        pr_emerg("Emergency!");
        return -EINVAL;
    }

    if (count == 0 || (count >= 5 && count <= 10))
        pr_warn("Warning!\n");

    for (int i = 0; i < count; i++) {
        print_hello(i);
    }

    return 0;
}

static void __exit hello_exit(void) {
}

module_init(hello_init)

module_exit(hello_exit)
