# DataStructure-ZNJ-SHU
我于2022学年的冬春学期选了由**朱能军**老师授课的《SJ结构》，本仓库整合了所有小组实验的代码，据了解截至目前（2024学年）实验内容仅存在部分出入。

项目旨在面向编程初学者，追求开箱即用。代码层面摒弃了浓厚的SJ风格，数据结构和算法上部分参考了 Sartaj Sahni 的 *Data Structures, Algorithms, and Aplications in C++*，实现上尽可能采用现代 C++ 语法。

这里是我和 C++ 结缘的地方，希望通过维护本仓库为同学们提供一些参考与启发。如果您对本项目的任何地方存在疑问，如不理解代码实现，或是发现了 bug，欢迎提交 issues。如果您愿意贡献代码，包括同步最新的实验内容，也欢迎提交 pull requests。

最后感谢合作过的三位组员 @donghaidiwang @ZhiXinYo @1nv1nce

## 环境配置
* IDE：Visual Studio Community
* 项目构建：CMake
* 语言标准：C++20及以上

注：如果你已有一定的开发基础，完全可以选用自己熟悉的工具，我会推荐 Visual Studio Code/Cursor

## 使用方法
打开项目文件夹，右键点击 `使用Visual Studio打开（Open with Visual Studio）`。

仅运行代码时建议将配置改为 `x64-Release`，这样编译器可以对代码进行优化，从而提升运行效率。

每个实验单独为一个解决方案（solution），点击上方的菜单选择

## 常见问题

## 关于课程
依照2022学年经历，一个学期共有一次个人实验和四次小组实验。个人实验于第一周当场验收，完成可以作为加分项，这里不提供代码；小组实验需要一起完成代码和报告，三个人一组，验收会按照组号顺序或倒序进行（就我的经历而言），所以每个小组会分到其中一个实验的验收，组号可自选。

## 实验内容
### 冬季学期
* [实验一 面试安排](winter/exp01-interview-arrangement/README.md)
* [实验二 车厢调度](winter/exp02-car-scheduling/README.md)
* [实验三 文学研究助手](winter/exp03-literature-assistant/README.md)
* [实验四 二叉树拓展及标记二叉树](winter/exp04-binary-tree/README.md)

### 春季学期
* [实验一 有向网的邻接矩阵验证及拓展](spring/exp01-adjacent-matrix-weighted-directed-graph/README.md)
* [实验二 无向网的邻接表验证和拓展](spring/exp02-adjacent-list-weighted-undirected-graph/README.md)
* [实验三 查找算法验证及设计](spring/exp03-search/README.md)
* [实验四 排序算法验证及设计](spring/exp04-sort/README.md)

## 日志
### 2025.04.04
* 更新了所有实验代码
* 将 Premake 更换为 CMake 以向主流工具靠拢
* 提取公共代码至 utils, 以动态/静态链接库的方式供实验调用
* 移除仅 Windows 的系统命令调用以支持跨平台运行
* 将编码方式更正为 utf-8, 同时去除代码中的中文字符, 以避免部分 IDE 无法识别
* 修复菜单选项判断条件错误的 bug
* 优化了文档
* 规范头文件引入顺序
* 移除了冗余的命名空间
* 将 `MyDS::` 命名空间改为 `myds::`
* 将函数的命名风格从帕斯卡命名法改为驼峰命名法