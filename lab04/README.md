# 第四次实验

## 实验题目

利用MPI实现并行排序算法

## 实验内容

使用MPI，实现PSRS（Parallel sorting by regular sampling）算法，算法具体描述可以参考以下网站：http://csweb.cs.wfu.edu/bigiron/LittleFE-PSRS/build/html/PSRSalgorithm.html

## 实验要求：

1. 实验结果对待排序数组的大小没有限制，请自行选择适合硬件环境的大小（一般来说，排序的数目在100w以上才能体现出并行的加速情况）。要求在报告中需要有待排序数目为64时的运行结果的截图，以确认排序结果的正确性。
2. 代码中允许使用qsort函数进行对局部数组的排序。