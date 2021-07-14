# 调研内容*（还没学怎么看内部函数实现，把功能和输入方式输出结果总结了一下）* 

* 调研输入输出和功能，写成调研报告
  * GLPK
  * SCIP
  * R-optimization   

## GLPK

### main components

* primal and dual simplex methods *(原对偶单纯形法)*
* primal-dual interior-point method*（原对偶内点法）*
* branch-and-cut method*（分支切割法）*
  * *以上三种为求解方法*
* translator for GNU MathProg*（翻译Mathporg（AMPL）语言）*
  * *MathProg模型语言将纯数学语言描述的模型转化为求解器能读懂的格式*
* application program interface (API)*（应用程序接口）*
  * *可以使用C/C++/JAVA...*
* stand-alone LP/MIP solver*（独立的线性/混合整数规划求解器）*
  * *求解出输出的结果*

## 操作

* **input**

  * MathProg Format
    * .ampl直接描述LP
    * mod*（LP的形状）*和data两个文件
  * 变量*（取值范围如大于0）*
  * 目标函数*（由变量如何组合得到，求最大/最小值）*
  * 约束方程*（变量的组合大于/小于某常数）*
  * 格式示例如下：

  #### 数学模型
  *图片我放不上来*
 
  ***参数就是模型中的常量***

  param n,integer,>=0; 
  param s,integer,>=0;
  param t,integer,>=0;
  param c{(i, j) in A},integer,>=1,<=20;

  ***集合就是模型中下标的索引空间***
  
  set V := 0..n; 
  set P within V;
  set Aplus := V cross V;
  set Al := V cross Aplus;
  set A within Aplus;

  ***变量就是模型中的变量***
 
  var x{(i, j) in Aplus}, binary;
  var lamd{(k,i,j) in Al}, binary;

  ***目标函数***
 
  minimize obj : sum {(u,v) in A} c[u,v]*x[u,v];

  *约束条件，必须给每个约束条件命名，名字后的花括号是约束条件中的索引空间，求和函数的索引范围放在sum后的花括号中。*
  
  s.t.
  second1{v in V: v = s}: (sum{(i,v) in A} x[i,v]) - (sum{(v,j) in A} x[v,j]) = -1;                             
  second2{v in V: v = t}: (sum{(i,v) in A} x[i,v]) - (sum{(v,j) in A} x[v,j]) = 1;
  second3{v in V: v <> s and v <> t}: (sum{(i,v) in A} x[i,v]) - (sum{(v,j) in A} x[v,j]) = 0; 
  third{v in P}: sum{(u,v) in A} x[u,v]=1;                                         
  sixth{i in V,j in V,k in V: i <> j}: lamd[k,i,j]+lamd[k,j,i]>=x[i,j];            
  seventh{i in V,k in V: i <> k}: sum {j in V diff {i}} lamd[k,i,j]<=1;       
  eighth{j in V,k in V: k <> j}: lamd[k,k,j]=0;                                        
  ninth{u in V,v in V diff {u}: (u,v) not in A}:  x[u,v]=0;                        
  tenth{u in V,v in V: (u,v) in A and (v,u) in A}: x[u,v]+x[v,u]<=1; 

  ***开始求解***                      
  
  solve;

  ***输出变量的值***
 
  display  {(i,j) in A} x[i,j];


  end;

* **output**
  * 取最优结果时变量的值