#ifdef __timer_H__
#define __timer_H__

/* 初始化 T0 计时器，使得 1ms 中断一次 */
void T0_1ms_init();
/* 中断操作 */
void T0_isr();

#endif