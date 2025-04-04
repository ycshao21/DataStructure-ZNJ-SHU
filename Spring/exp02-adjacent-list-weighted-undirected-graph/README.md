# 实验二 无向网的邻接表验证和拓展
```
模仿有向图的邻接表类模板，完成（带权：非负）无向网的邻接表类模板的设计与实现。要求实现图的基本运算（如增加删除顶点和边等），并增加如下成员函数：
1. CountDegree(v)：统计顶点v的度；
2. ConnectedComponent()：求图的连通分量数目；
3. 验证Kruskal和Prim两种最小生成树算法，并设计或实现除此以外的另一种最小生成树算法，如“破圈法”等（仅考虑连通图）；
4. hasUniqueMinTree()，判断无向网是否存在唯一的最小生成树（仅考虑连通图）。
```

破圈法中判断回路的方法证明可以参考 https://rivers-shall.github.io/2018/11/19/Necessary-And-Sufficient-Condition-for-Unique-MST/ 。