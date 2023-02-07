/* Write a simple "Hello, world!" kernel module, extend your kernel module to print the following information to the kernel log:The name and PID of the current process. The name and PID of the parent process. Extend your kernel module to walk the process tree, starting from the current process, until you reach the process with pid 0 */



#include <linux/init.h>
/* for kernel access */
#include <linux/kernel.h>
/* for permission's */
#include <linux/module.h>
/* for pointer denoation */
#include <linux/sched.h>

/* Module permission's */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dineshkumar Subramaniam");
MODULE_DESCRIPTION("Hello world module! ");

/* __init function */
static int __init hello_init(void)
{
    /* Contains information about the process such as its state, PID */
    struct task_struct *file;

    printk(KERN_INFO "Hello world...!\n");
    file = current;
    
    /* file->comm - represents the name of a process */
    /* file->pid - represents the process ID (PID) of the process */ 
    printk(KERN_INFO "Current process name: %s PID: %d\n", file->comm, file->pid);
    
    /* represents the parent process of the current process */
    file = file->real_parent;
    
    /* file->comm - represents the name of a process */
    /* file->pid - represents the process ID (PID) of the process */
    printk(KERN_INFO "Parent process name: %s PID: %d\n", file->comm, file->pid);

    printk(KERN_INFO "Entering to process\n");

    /* The loop continues as long as file->pid is not equal to 0 */    
    for (file = current; file->pid != 0; file = file->real_parent) 
    {
        printk(KERN_INFO "Process name: %s PID: %d\n", file->comm, file->pid);
    }

    return 0;
}

/* __exit function */
static void __exit hello_exit(void)
{
    printk(KERN_INFO "Exiting...!\n");
}

/* Macros for loading module when insmod and rmmod gets called */
module_init(hello_init);
module_exit(hello_exit);

