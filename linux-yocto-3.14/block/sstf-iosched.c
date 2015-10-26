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
    list_del_init(&next->queue);
}

static int look_dispatch(struct request_queue *q, int force)
{
    struct look_data *nd = q->elevator->elevator_data;

    //If request queue is not empty
    if(!list_empty(&nd->queue))
    {
        struct request *next_req, *prev_req, *req;

        //neq_req gets the next closest request grater than the current node
        next_req = list_entry(nd->queue.next, struct request, queuelist);
        //prev_req gets the closest request less than the current node
        prev_req = list_entry(nd->prev.next, struct request, queuelist);

        //Time to set rq
        
        //Check if the next is the previous, if there one element in the list
        if(prev_req == next_req)
        {
            rq = prev_req;   
        }
        else
        {

        }
    }   
    return 0;
}

static void look_add_request(struct request_queue *q, struct request *rq)
{

}

static struct request * 
look_former_request(struct request_queue *q, struct request *rq)
{
    struct look_data *nd = q->elevator->elevator_data;

    if(rq->queuelist.next == &nd->queue)
        return NULL;
    return list_entry(rq->queuelist.next, struct request, queuelist);
}

static struct request * 
look_latter_request(struct request_queue *q, struct request *rq)
{
    struct look_data *nd = q->elevator->elevator_data;

    if(rq->queuelist.next == &nd->queue)
        return NULL;
    return list_entry(rq->queuelist.next, struct request, queuelist);
    return NULL;
}

static int look_init_queue(struct request_queue *q, struct elevator_type *e)
{
    
    return 0;
}

static void look_exit_queue(struct elevator_queue *e)
{
    struct look_data *nd = e->elevator_data;

    kfree(nd);
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
