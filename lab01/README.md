#实验一

###实验题目:
利用MPI,OpenMP编写简单的程序,测试并行计算系统性能

###实验内容
两道题,每道题需要使用MPI和OpenMP分别实现:

1.求素数个数

实验描述:
给定正整数n,编写程序计算出所有小于等于n的素数的个数

实验要求:
需要测定n=1,000;10,000;100,000;500,000(逗号仅为清晰考虑)时程序运行的时间

2.求Pi值

实验描述:
给定迭代次数n,编写程序计算Pi的值

实验要求:
算法必须使用近似公式求解
需要测定n=1,000;10,000;50,000;100,000(逗号仅为清晰考虑)时程序运行的时间

以上两个实验测试的时间需要在不同的线程数下测量,格式在模版中已经给出

可选内容:
对于以上两个实验,不指定迭代次数,而是规定执行时间,测试在指定运行时间下能迭代的次数.运行时间可以自己设置.