# SCIP

## 应用程序（有7个文件夹，和问题具体相关的数学还没到位，不是很看得懂）

* coloring
  * pricer 和相关模型（.col输入）
* cycleclustering
  * 解决cycle clustering 问题：例 * 不可逆马尔科夫过程中循环检测的整数规划 * (.spa输入)
* MinIISC
  * 解决最小IIS-cover问题
* PolySCIP
  * 解决 multi-criteria integer programming and multi-criteria linear programming problems
  * 和GLPK类似
* ringpacking
  * 分支-价格方法（递归circle packing问题）
* Scheduler
  * 调度问题
* STP
  * 解决Stiner tree问题（基于分支支和切割的SCIP-Jack求解器）



### coloring

* pricer_coloring.c
  * pricer：*如何执行 column generation*
* cons_storeGraph.c
  * 约束处理程序：*如何在节点上存储分支决策并通过propagation来强制执行分支决策*
* branch_coloring.c 
  * 默认分支规则：*如何将约束添加到分支定界节点*
* branch_strongcoloring.c
  * 第二个分支规则：*一些更复杂的分支方法*
* heur_init.c
  * 初始解
* probdata_coloring.c
  * 描述问题data



### cycleclustering

* ~



### MinIISC

* Benders.c 
  * 基本的Bender算法
* 采取一些其他技巧加速





### ringpacking

* ~



### scheduler

* reader_sm.h
  * RCPSP（资源受限的调度）
* reader_sch.h
  * RCPSP/max（具有最小和最大时间滞后的资源受限的调度）
* reader_rcp.h
  * pack instance（并不清楚是什么问题



### STP（不知道Stiner tree是什么）

* reader_stp.c
* probdata_stp.c
* heur_tm.c
* heur_prune.c
* heur_local.c
* heur_rec.c
* reduce_alt.c
* reduce_bnd.c
* cons_stp.c
* prop_stp.c
* event_bestsol.c