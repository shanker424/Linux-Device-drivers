#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>


/******Module Init******/

static int  __init helloworld_init(void)
{

	pr_info("hello world \n");
	return 0;
} 


/*********Module exit*****/

static void __exit  helloworld_exit(void){

	pr_info("bye world \n");
	
} 

module_init(helloworld_init);
module_exit(helloworld_exit);

MODULE_AUTHOR("shanker <shanker424@gmail.com>");
MODULE_LICENSE("GPL");
