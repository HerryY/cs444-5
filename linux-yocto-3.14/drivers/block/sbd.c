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

    unsigned long offset = sector*KERNEL_SECTOR_SIZE;
    unsigned long nbytes = nsect*KERNEL_SECTOR_SIZE;

    if((offset + nbytes) > dev->size)
    {
        printk(KERN_NOTICE "Beyond end wriet (%ld %ld)\n", offset, nbytes);
        return;
    }

    if(write)
        memcpy(dev->data + offset, buffer, nbytes);
    else
        memcpy(buffer, dev->data + offset, nbytes);
}

static void sbd_request(struct request_queue *q) {

    struct request *req;

    //simplified version of the full request
    //Gets the next incomplete request on queue
    while((req = elv_next_request(q)) != NULL)
    {
        struct sbull_dev *dev = req->rq_disk->private_data;
        //End request if it's non-fs
        if(!blk_fs_request(req))
        {
            printk(KERN_NOTICE "Skip non-fs request\n");
            end_request(req, 0);
            continue;
        }
        //Send request to transfer function
        sbd_transfer(dev, req->sector, req->current_nr_sectors,
                req->buffer, rq_data_dir(req));
        //Make sure to end request
        end_request(req, 1);
    }
}

static int sbd_xfer_bio(struct sbd_dev *dev, struct bio *bio) {

    int i;
    struct bio_vec *bvec;
    sector_t sector = bio->bi_sector;

    //Iterate throught each section
    bio_for_each_segment(bvec, bio, i)
    {
        char *buffer = __bio_kmap_atomic(bio, i, KM_USER0);
        sbd_transfer(dev, sector, bio_cur_sectors(bio),
                buffer, bio_data_dir(bio) == WRITE);
        sector += bio_cur_sectors(bio);
        __bio_kunmap_atomic(bio, KM_USER0);
    }
    return 0;
}

static int sbd_xfer_request(struct sbd_dev *dev, struct request *req) {

    struct bio *bio;
    int nsect = 0;

    //steps through each request and sends it to xfer_bio
    rq_for_each_bio(bio, req)
    {
        sbd_xfer_bio(dev, bio);
        nsect += bio->bi_size/KERNEL_SECTOR_SIZE;
    }

    return nsect;
}

static void sbd_full_request(struct request_queue *q) {
    
    struct request *req;
    int sectors_xferred; 
    struct sbd_dev *dev = q->queuedata;

    //Takes request and sends i to xfer_reqest
    while ((req = elv_next_request(q)) != NULL)
    {
        if(!blk_fs_request(req))
        {
            printk(KERN_NOTICE "Skips non-fs request\n");
            end_request(req, 0);
            continue;
        }
        sectors_xferred = sbd_xfer_reqest(dev, req);
        //Makes sure that the request gets completed
        if(!end_that_request_first(req, 1, sectors_xferred))
        {
            blkdev_dequeue_request(req);
            end_that_request_last(req);
        }
    }

}
static void sbd_make_request(struct request_queue *q, struct bio *bio) {

    struct sbd_dev *dev = q->queuedata;
    int status;

    //Goes through the bio request without a request queue
    status = sbd_xfer_bio(dev, bio);
    bio_endio(bio, bio->bi_size, status);
    return 0;
}

static int sbd_open(struct block_device *bdev, fmode_t mode) {
    
    struct sbd_dev *dev = inode->i_bdev->bd_disk->private_data;

    del_trime_sync(&dev->time);
    flip->private_data = dev;
    spin_lock(&dev->lock);
    if(!dev->users)
        check_disk_change(inode->i_bdev);
    dev->users++;
    spin_unlock(&dev->lock);
    return 0;
}

static void sbd_release(struct gendisk *disk, fmode_t mode) {

    struct sbd_release(struct inode *inode, struct *file flip)

    spin_lock(&dev->lock);
    dev->users--;

    if(!dev->users) {
        dev->timer.expires = jiffies + INVALIDATE_DELAY;
        add_time(&dev->timer);
    }

    spin_unlock(&dev->lock);

    return 0;
}

int sbd_media_changed(struct gendisk *gd) {

    struct sbd_dev *dev = gd->private_data;

    return dev->media_change;
}

int sbd_revalidate(struct gendisk *gd) {
    
    struct sbd_dev *dev = gd->private_data;

    if(dev->media_change) 
    {
        dev->media_change = 0;
        memset(dev->data, 0, dev->size);
    }
    return 0;
}

void sbd_invalidate(unsigned long ldev){

}

int sbd_ioctl (struct inode *inode, struct file *flip,
                 unsigned int cmd, unsigned long arg){

    long size;
    struct hd_geometry geo;
    struct sbd_dec *dev = flip->private_data;

    switch(cmd)
    {
        case HDIO_GETGEO:
            size = dev->size*(hardsect_size/KERNEL_SECTOR_SIZE);
            geo.cylinders = (size & ~0x3f) >>6;
            geo.heads = 4;
            geo.sectors = 16;
            geo.start = 4;
            if(copy_to_user((void __user *) arg, &geo, sizeof(geo)))
                return -EFAULT;

        return 0;
    }

    return -ENOTTY;
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

    memset(dev, 0, sizeof(struct sbd_dev));
    dev->size = nsectors*hardsect_size;
    dev->data = vmalloc(dev->size);
    if(dev->data == NULL)
    {
        printk(KERN_NOTICE "Vmalloc failure\n");
        return;
    }
    spin_lock_init(&dev->lock);

    dev->queue = blk_init_queue(sdb_request, &dev->lock);
    
    dev->gd = alloc_disk(SBD_MINORS);
    if(!dev->gd)
    {
        printk(KERN_NOTICE "Alloc Disk failure\n");
        goto out_vfree;
    }

    dev->gd->major = sbd_major;
    dev->gd->first_major = which*SBD_MINORS;
    dev->gd->fops = &sbd_ops;
    dev->gd->queue = dev->queue;
    dev->gd->private_data = dev;
    snprintf(dev->gd->disk_name, 32, "sbd%c", which + 'a');
    set_capacity(dev->gd, nsectors*(hardsect_size/KERNEL_SECTOR_SIZE));
    add_disk(dev->gd);
    return;

  out_vfree:
        if(dev->data)
            vfree(dev->data);
}

static int __init sbd_init(void) {

    int i;

    sbd_major = register_blkdev(sbd_major, "sbd");
    if(sbd_major <= 0)
    {
        printk(KERN_WARNING "sbd: Can't get major number\n");
        return -EBUSY;
    }
}

static void sbd_exit(void) {

}

module_init(sbd_init);
module_exit(sbd_exit);
