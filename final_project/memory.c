#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>  

MODULE_LICENSE("Dual BSD/GPL");

#define MEMORY_MAJOR 60
#define MEMORY_SIZE 10000 * 1024

static int memory_major = MEMORY_MAJOR;
static char memory_buffer[MEMORY_SIZE] = {0};

static int memory_open(struct inode *inode, struct file *filp) {
    return 0;
}

static int memory_release(struct inode *inode, struct file *filp) {
    return 0;
}

static ssize_t memory_read(struct file *filp, char *buf, size_t count, loff_t *f_pos) {
    if (*f_pos >= MEMORY_SIZE) {
        return 0;  // End of file
    }

    if (count > MEMORY_SIZE - *f_pos) {
        count = MEMORY_SIZE - *f_pos;  // Adjust count to avoid buffer overflow
    }

    if (copy_to_user(buf, memory_buffer + *f_pos, count) != 0) {
        return -EFAULT;  // Error copying data to user space
    }

    *f_pos += count;
    return count;
}

static ssize_t memory_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos) {
    if (*f_pos >= MEMORY_SIZE) {
        return -ENOSPC;  // No space left on device
    }

    if (count > MEMORY_SIZE - *f_pos) {
        count = MEMORY_SIZE - *f_pos;  // Adjust count to avoid buffer overflow
    }

    if (copy_from_user(memory_buffer + *f_pos, buf, count) != 0) {
        return -EFAULT;  // Error copying data from user space
    }

    *f_pos += count;
    return count;
}

static struct file_operations memory_fops = {
    .open = memory_open,
    .read = memory_read,
    .write = memory_write,
    .release = memory_release,
};

// Define the proc file operations
static struct proc_ops memory_proc_ops = {
    .proc_read = memory_read,
    .proc_write = memory_write,
};

// Define the proc file entry
static struct proc_dir_entry *memory_proc_entry;

static int __init memory_init(void) {
    int result;

    result = register_chrdev(memory_major, "memory", &memory_fops);
    if (result < 0) {
        pr_err("memory: cannot obtain major number %d\n", memory_major);
        return result;
    }

    // Create the proc entry
    memory_proc_entry = proc_create("memory", 0, NULL, &memory_proc_ops);
    if (!memory_proc_entry) {
        pr_err("memory: failed to create proc entry\n");
        unregister_chrdev(memory_major, "memory");
        return -ENOMEM;
    }

    pr_info("Memory module initialized\n");
    return 0;
}

static void __exit memory_exit(void) {
    // Remove the proc entry
    proc_remove(memory_proc_entry);

    unregister_chrdev(memory_major, "memory");
    pr_info("Memory module exited\n");
}

module_init(memory_init);
module_exit(memory_exit);
