
#ifndef OPENTHREAD_ASSERT_H
#define OPENTHREAD_ASSERT_H

#ifdef CONFIG_OT_ASSERT
//extern void vAssertCalled(void);
//#define OT_ASSERT(cond) if (!(cond)) { printf("assert @ %s, %d\r\n", __FILE__, __LINE__); vAssertCalled();}
#define OT_ASSERT(x) configASSERT( x )
#else
#define OT_ASSERT(cond) 
#endif

#endif