# 实验 4-3: 铁路交通网的最短路径

## 1. 问题描述

输入一个无向铁路交通图、始发站和终点站，用Dijkstra算法计算从始发站到终点站的最短路径。

__输入要求__: 
第一行是两个数n，m(1 < n < 100000，1 < m < 1000000)，分别表示顶点数量和边的数量
接下来的m行每行输入三个数a、b、w；表示顶点a与顶点b之间有长度为w的边相连，顶点编号从1到n
最后输入两个数s，t表示遍历的起始顶点编号和终点编号
__输出要求__:
一个数为从起点到终点的最短路径长度

## 2. 算法的描述

### 2.1 数据结构的描述

初始时，设每个点的距离都是未知的(-1), 然后逐次标记距离，即若距离为所有点中的最短距离，则标记这个点，并重新开始搜索下一个点，知道到达终点点的编号。

### 2.2 程序结构的描述

在 `main()` 函数中，Dijkstra算法从 94 行开始至 122 行，主要的思路如描述中所示

## 3. 算法的时间分析

Dijkstra 的时间复杂度为 `O(N^2)`

## 4. 实验体会和收获

该试验是我对三个算法：Kruskal、Prim 和 Dijkstra 更加熟悉，能更熟练地对图进行各种操作。