#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
void irq_handeler(int irq,void *dev_id/*,struct pt_regs *regs*/){

	printk("process \n");

	/*return IRQ_RETVAL(1);*/
}

static int reg_irq(void){
	int ret;
	printk(KERN_ALERT "Going to Register \n");
	
	ret=request_irq(1,(irq_handler_t)irq_handeler,IRQF_SHARED ,"Keyboard irq handel",(void *)(irq_handeler));
	if(ret<0){
		printk(KERN_ALERT "Allocate interrupt \n");
	}
	return 0;
}


static void unreg_irq(voi){
	printk(KERN_ALERT "Going for Unregister \n");
	free_irq(1,(void *)irq_handeler);
}

module_init(reg_irq);
module_exit(unreg_irq);