/*
 * elevator look
 */
#include <linux/blkdev.h>
#include <linux/elevator.h>
#include <linux/bio.h>
#include <linux/module.h>
#include <linux/slab.h>

struct look_data {
    struct list_head queue;
};

static void look_merged_requests
(struct request_queue *q, struct request *rq, struct request *next)
{

}

static int look_dispatch(struct request_queue *q, int force)
{

    return 0;
}

static void look_add_request(struct request_queue *q, struct request *rq)
{

}

static struct request * 
look_former_request(struct request_queue *q, struct request *rq)
{

    return NULL;
}

static struct request * 
look_latter_request(struct request_queue *q, struct request *rq)
{

    return NULL;
}

static int look_init_queue(struct request_queue *q, struct elevator_type *e)
{

    return 0;
}

static void look_exit_queue(struct elevator_queue *e)
{

}

static struct elevator_type elevator_look = {
    .ops = {
        .elevator_merge_req_fn = look_merged_requests,
        .elevator_dispatch_fn = look_dispatch,
        .elevator_add_req_fn = look_add_request,
        .elevator_former_req_fn = look_former_request,
        .elevator_latter_req_fn = look_latter_request,
        .elevator_init_fn = look_init_queue,
        .elevator_exit_fn = look_exit_queue,
    },
    .elevator_name = "look",
    .elevator_owner = THIS_MODULE,

};

static int __init look_init(void)
{
	return elv_register(&elevator_look);
}

static void __exit look_exit(void)
{
	elv_unregister(&elevator_look);
}

module_init(look_init);
module_exit(look_exit);


MODULE_AUTHOR("Taylor Fahlman");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LOOK IO scheduler");
