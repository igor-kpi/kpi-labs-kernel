#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

MODULE_AUTHOR("Ihor <igor-kpi@ukr.net>");
MODULE_DESCRIPTION("Hello world");
MODULE_LICENSE("GPL");

static uint count = 1;

module_param(count, uint, S_IRUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(count, "Number of iterations");

LIST_HEAD(tt_list);

struct time_trace {
    struct list_head list;
    uint i;
    ktime_t time;
};

static int __init hello_init(void) {
    if (count > 10) {
        printk(KERN_EMERG "Emergency!");
        return -EINVAL;
    }

    if (count == 0 || (count >= 5 && count <= 10))
        printk(KERN_WARNING "Warning!\n");

    for (int i = 0; i < count; i++) {
        struct time_trace *item = kmalloc(sizeof(struct time_trace), GFP_KERNEL);
        item->i = i;
        item->time = ktime_get();
        list_add(&item->list, &tt_list);

        printk(KERN_INFO "Hello, world! %d\n", i);
    }

    return 0;
}

static void __exit hello_exit(void) {
    struct time_trace *pos, *n;
    list_for_each_entry_safe(pos, n, &tt_list, list) {
        printk(KERN_INFO "Iteration %d: %lld\n", pos->i, ktime_to_ns(pos->time));
        list_del(&pos->list);
        kfree(pos);
    }
}

module_init(hello_init)
module_exit(hello_exit)
