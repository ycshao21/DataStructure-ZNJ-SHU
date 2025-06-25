# 更新日志
## 2025.06.25
### 修复问题
* 修复了 `AdjMatWDirGraph::printAdjacentMatrix` 打印错位的问题

### 新增内容
* 新增了 `AdjMatWDirGraph::getVertex` 方法，用于根据索引访问顶点

### 修改内容
* 使用 `std::size_t` 替代 `int` 作为索引和计数类型
* 将获取邻接顶点相关方法的返回值从指针类型改为索引值
* 当边列表和邻接矩阵为空时显示 "None"
* 将 `AdjMatWDirGraph::getIndexOfVertex` 的访问权限改为 `public`
* `AdjMatWDirGraph::getIndexOfVertex` 不再抛出 `VertexNotFound` 异常
* 将 `VertexAlreadyExists` 和 `EdgeAlreadyExists` 异常重命名为 `DuplicateVertex` 和 `DuplicateEdge`，将 `InfiniteWeight` 重命名为 `InvalidWeight`
* 调整 `printPath` 函数，只保留打印路径的功能

### 移除内容
* 移除了 `IllegalParameterValue` 异常