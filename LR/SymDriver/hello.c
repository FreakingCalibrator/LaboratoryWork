//#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/kthread.h>

struct task_struct *ts;
int thread(void* ts)
{
	while(1)
	{
		printk("Hello. I am kernel thread!\n");
		msleep(10000);
		if (kthread_should_stop())
			break;
	}
	return 0;
}
static int hello_init(void)
{
	printk(KERN_ALERT "I bear a charmed life,\n");
	ts=kthread_run(thread, NULL, "foo kthread");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Out, out, brief candle!\n");
	kthread_stop(ts);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shakespeare");
MODULE_DESCRIPTION("A Hello, world module");
