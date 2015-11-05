/**
 *
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/sched.h>
#include <linux/kernel.h>   /* printk() */
#include <linux/slab.h>     /* kmalloc() */
#include <linux/fs.h>       /* everything... */
#include <linux/errno.h>    /* error codes */
#include <linux/timer.h>
#include <linux/types.h>    /* size_t */
#include <linux/fcntl.h>    /* O_ACCMODE */
#include <linux/hdreg.h>    /* HDIO_GETGEO */
#include <linux/kdev_t.h>
#include <linux/vmalloc.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
#include <linux/buffer_head.h>  /* invalidate_bdev */
#include <linux/bio.h>


enum {
    RM_SIMPLE  = 0, /* The extra-simple request function */
    RM_FULL    = 1, /* The full-blown version */
    RM_NOQUEUE = 2, /* Use make_request */
};
static int request_mode = RM_SIMPLE;

#define KERNEL_SECTOR_SIZE  512

struct sbd_dev {
        int size;                       /* Device size in sectors */
        u8 *data;                       /* The data array */
        short users;                    /* How many users */
        short media_change;             /* Flag a media change? */
        spinlock_t lock;                /* For mutual exclusion */
        struct request_queue *queue;    /* The device request queue */
        struct gendisk *gd;             /* The gendisk structure */
        struct timer_list timer;        /* For simulated media changes */
};

static struct sbd_dev *Devices = NULL;

static void sbd_transfer(struct sbd_dev *dev, unsigned long sector,
        unsigned long nsect, char *buffer, int write) {

}

static void sbd_request(struct request_queue *q) {

}

static int sbd_xfer_bio(struct sbd_dev *dev, struct bio *bio) {

}

static int sbd_xfer_request(struct sbd_dev *dev, struct request *req) {

}

static void sbd_full_request(struct request_queue *q) {

}
static void sbd_make_request(struct request_queue *q, struct bio *bio) {

}

static int sbd_open(struct block_device *bdev, fmode_t mode) {

}

static void sbd_release(struct gendisk *disk, fmode_t mode) {

}

int sbd_media_changed(struct gendisk *gd) {

}

int sbd_revalidate(struct gendisk *gd) {

}

void sbd_invalidate(unsigned long ldev){

}

int sbd_ioctl (struct block_device *bdev, fmode_t mode,
                 unsigned int cmd, unsigned long arg){

}


static struct block_device_operations sbd_ops = {
    .owner           = THIS_MODULE,
    .open            = sbd_open,
    .release     = sbd_release,
    .media_changed   = sbd_media_changed,
    .revalidate_disk = sbd_revalidate,
    .ioctl           = sbd_ioctl
};

static void setup_device(struct sbd_dev *dev, int which) {

}

static int __init sbd_init(void) {

}

static void sbd_exit(void) {

}

module_init(sbd_init);
module_exit(sbd_exit);
