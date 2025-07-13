## ABOUT GPR

GPRS, MEANS GENERAL PURPOSE REGISTER, 即通用寄存器。

IT IS GRANTED THAT GPRs IS 通用寄存器组。

## ABOUT RISC

RISC 一定采取流水线技术提速（就目前课内知识）。

## ABOUT 隐含寻址

Implicit Addressing，举例 ：

- CLR : 清除累加器 $\rightarrow$ 隐含地址为 ACC

- INC : 累加器加 1 $\rightarrow$ 隐含地址为 ACC

## 异步刷新时间如何计算 ？

最大刷新间隔一般会给 2ms，用这个时间去除以行数，即

$\text{异步刷新周期}=\frac{\text{最大单元刷新间隔}}{\text{DRAM行数}}$
