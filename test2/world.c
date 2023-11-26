#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

#include "world.h"

MODULE_AUTHOR("Ihor <igor-kpi@ukr.net>");
MODULE_DESCRIPTION("World hello");
MODULE_LICENSE("GPL");

LIST_HEAD(tt_list);

static uint it = 0;

struct time_trace {
    struct list_head list;
    uint i;
    ktime_t start;
    ktime_t end;
};

void print_hello(int i) {
    struct time_trace *item = kmalloc(sizeof(struct time_trace), GFP_KERNEL);
    item->i = it++;

    item->start = ktime_get();
    pr_info("Hello, world! %d\n", i);
    item->end = ktime_get();

    list_add(&item->list, &tt_list);
}

EXPORT_SYMBOL(print_hello);

static int __init world_init(void) {
    return 0;
}

static void __exit world_exit(void) {
    struct time_trace *pos, *n;
    list_for_each_entry_safe(pos, n, &tt_list, list) {
        pr_info("Iteration %d: %lldns\n", pos->i, ktime_to_ns(pos->end - pos->start));
        list_del(&pos->list);
        kfree(pos);
    }
}

module_init(world_init)

module_exit(world_exit)
