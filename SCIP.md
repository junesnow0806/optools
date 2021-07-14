

 

**SCIP** is a framework to solve constraint integer programs (CIPs) and mixed-integer nonlinear programs. In particular,
-   **SCIP** incorporates a mixed-integer programming (MIP) solver as well as
-   an LP based mixed-integer nonlinear programming (MINLP) solver, and
-   is a framework for branch-and-cut-and-price.

## CSIP

为SCIP的C接口

## 函数

### retCodeSCIPtoCSIP

```c
static inline int retCodeSCIPtoCSIP(int scipRetCode)
```

将SCIP的返回值转化为CSIP的

输入SCIP的返回

返回对应的CSIP的编码

### retCodeCSIPtoSCIP

```c
static inline int retCodeCSIPtoSCIP(int csipRetCode)
```

基本同retCodeSCIPtoCSIP

将CSIP编码转换为SCIP

### CSIP_CALL

```c
#define CSIP_CALL(x) 
```

在CSIP内捕获返回代码,判断x是否为CSIP_RETCODE_OK,若不是，则错误信息，结束进程

### SCIP_in_CSIP

```c
#define SCIP_in_CSIP(x)
```

实际上就是

```c
CSIP_CALL( retCodeSCIPtoCSIP(x) )
```

catch SCIP return code from CSIP

### CSIP_in_SCIP

基本同SCIP_in_CSIP

```c
#define CSIP_in_SCIP(x) SCIP_CALL( retCodeCSIPtoSCIP(x) )
```

###  createLinCons

```c
static
CSIP_RETCODE createLinCons(CSIP_MODEL *model, int numindices, int *indices,
                           double *coefs, double lhs, double rhs, SCIP_CONS **cons)
```

创建线性约束条件

### addCons

```c
static
CSIP_RETCODE addCons(CSIP_MODEL *model, SCIP_CONS *cons, int *idx)
```

添加约束条件

### createExprtree

```c
static
CSIP_RETCODE createExprtree(
    CSIP_MODEL *model, int nops, CSIP_OP *ops, int *children, int *begin,
    double *values, SCIP_EXPRTREE **tree)
```

创建后缀表达式树

### strDup

```c
static
char *strDup(const char *s)
```

将字符串s复制一份,返回复制得到的字符串的头指针

### correctObjectiveFunction

```c
CSIP_RETCODE correctObjectiveFunction(CSIP_MODEL *model)
```

纠正目标表达式

The purpose of this function is to change an epigraph objective to represent the correct objective sense

输入为所求解的模型

### CSIPmajorVersion

```c
int CSIPmajorVersion()
```

返回版本信息

### CSIPminorVersion

```c
int CSIPminorVersion()
```

返回版本信息

### CSIPpatchVersion

```c
int CSIPpatchVersion()
```

返回版本信息

### CSIPgetVersion

```c
int CSIPgetVersion()
{
    return (100 * CSIPmajorVersion() + 10 * CSIPminorVersion() + 1 * CSIPpatchVersion());
}
```

返回完整的版本信息

### CSIPcreateModel

```c
CSIP_RETCODE CSIPcreateModel(CSIP_MODEL **modelptr)
```

创建一个默认是模型,传入模型的指针

### CSIPfreeModel

```c
CSIP_RETCODE CSIPfreeModel(CSIP_MODEL *model)
```

调用free释放，删除模型

### CSIPaddVar

```c
CSIP_RETCODE CSIPaddVar(CSIP_MODEL *model, double lowerbound, double upperbound,
                        int vartype, int *idx)
```

向模型中添加变量

### CSIPchgVarLB

```c
CSIP_RETCODE CSIPchgVarLB(CSIP_MODEL *model, int numindices, int *indices,
                          double *lowerbounds)
```

改变模型中某些变量的下界

numindices为需要改变下界的变量的数量

将indices[i]的下界变为lowerbounds[i]

### CSIPchgVarUB

```c
CSIP_RETCODE CSIPchgVarUB(CSIP_MODEL *model, int numindices, int *indices,
                          double *upperbounds)
```

改变模型中某些变量的上界

与CSIPchgVarLB几乎相同

### CSIPchgVarType

```c
CSIP_RETCODE CSIPchgVarType(
    CSIP_MODEL *model, int varindex, CSIP_VARTYPE vartype)
```

改变变量类型

### CSIPgetVarType

```c
CSIP_VARTYPE CSIPgetVarType(CSIP_MODEL *model, int varindex)
```

返回变量类型

### CSIPaddLinCons

```c
CSIP_RETCODE CSIPaddLinCons(CSIP_MODEL *model, int numindices, int *indices,
                            double *coefs, double lhs, double rhs, int *idx)
```

添加线性约束条件

### CSIPaddQuadCons

```c
CSIP_RETCODE CSIPaddQuadCons(CSIP_MODEL *model, int numlinindices,
                             int *linindices,
                             double *lincoefs, int numquadterms,
                             int *quadrowindices, int *quadcolindices,
                             double *quadcoefs, double lhs, double rhs, int *idx)
```

添加二次约束条件

### CSIPaddNonLinCons

```c
CSIP_RETCODE CSIPaddNonLinCons(
    CSIP_MODEL *model, int nops, CSIP_OP *ops, int *children, int *begin,
    double *values, double lhs, double rhs, int *idx)
```

添加非线性约束条件

### CSIPaddSOS1

```c
CSIP_RETCODE CSIPaddSOS1(
    CSIP_MODEL *model, int numindices, int *indices, double *weights, int *idx)
```

我没看懂这个,估计是添加目标函数啥的吧

### CSIPaddSOS2

```c
CSIP_RETCODE CSIPaddSOS2(
    CSIP_MODEL *model, int numindices, int *indices, double *weights, int *idx)
```

也没看懂

### CSIPsetObj

```
CSIP_RETCODE CSIPsetObj(CSIP_MODEL *model, int numindices, int *indices,
                        double *coefs)
```

设置目标函数

### CSIPsetQuadObj

```c
CSIP_RETCODE CSIPsetQuadObj(CSIP_MODEL *model, int numlinindices,
                            int *linindices, double *lincoefs, int numquadterms,
                            int *quadrowindices, int *quadcolindices,
                            double *quadcoefs)
```

设置二次目标函数

### CSIPsetNonlinearObj

```c
CSIP_RETCODE CSIPsetNonlinearObj(
    CSIP_MODEL *model, int nops, CSIP_OP *ops, int *children, int *begin,
    double *values)
```

设置非线性目标函数

### CSIPsetSenseMinimize

```c
CSIP_RETCODE CSIPsetSenseMinimize(CSIP_MODEL *model)
```

没看懂...把源码贴上来吧

```c
CSIP_RETCODE CSIPsetSenseMaximize(CSIP_MODEL *model)
{
    SCIP_in_CSIP(SCIPfreeTransform(model->scip));

    if (SCIPgetObjsense(model->scip) != SCIP_OBJSENSE_MAXIMIZE)
    {
        SCIP_in_CSIP(SCIPsetObjsense(model->scip, SCIP_OBJSENSE_MAXIMIZE));
        CSIP_CALL(correctObjectiveFunction(model));
    }

    return CSIP_RETCODE_OK;
}
```

### CSIPsolve

```c
CSIP_RETCODE CSIPsolve(CSIP_MODEL *model)
```

求解模型

### CSIPinterrupt

```c
CSIP_RETCODE CSIPinterrupt(CSIP_MODEL *model)
{
    SCIP_in_CSIP(SCIPinterruptSolve(model->scip));
    return CSIP_RETCODE_OK;
}
```

中断

### CSIPgetStatus

```c
CSIP_STATUS CSIPgetStatus(CSIP_MODEL *model)
```

返回状态

### CSIPgetObjValue

```c
double CSIPgetObjValue(CSIP_MODEL *model)
```

返回目标函数的值

### CSIPgetObjBound

```c
double CSIPgetObjBound(CSIP_MODEL *model)
{
    return SCIPgetDualbound(model->scip);
}
```

返回目标约束

### CSIPgetVarValues

```c
CSIP_RETCODE CSIPgetVarValues(CSIP_MODEL *model, double *output)
```

将变量值复制到数组output中

### CSIPgetParamType

```c
CSIP_PARAMTYPE CSIPgetParamType(CSIP_MODEL *model, const char *name)
```

获得name的参数类型

### CSIPsetBoolParam

```c
CSIP_RETCODE CSIPsetBoolParam(
    CSIP_MODEL *model, const char *name, int value)
```

设置bool参数

### CSIPsetIntParam

```c
CSIP_RETCODE CSIPsetIntParam(
    CSIP_MODEL *model, const char *name, int value)
```

设置int参数

### CSIPsetLongintParam

```
CSIP_RETCODE CSIPsetLongintParam(
    CSIP_MODEL *model, const char *name, long long value)
```

设置long int 参数

### CSIPsetRealParam

```c
CSIP_RETCODE CSIPsetRealParam(
    CSIP_MODEL *model, const char *name, double value)
```

设置double参数

### CSIPsetCharParam

```c
CSIP_RETCODE CSIPsetCharParam(
    CSIP_MODEL *model, const char *name, char value)
```

设置char参数

### CSIPsetStringParam

```c
CSIP_RETCODE CSIPsetStringParam(
    CSIP_MODEL *model, const char *name, const char *value)
```

设置cstring参数

### CSIPgetNumVars

```c
int CSIPgetNumVars(CSIP_MODEL *model)
{
    return model->nvars;
}
```

返回变量个数

### CSIPgetNumConss

```c
int CSIPgetNumConss(CSIP_MODEL *model)
{
    return model->nconss;
}
```

返回约束个数

### CSIPsetInitialSolution

```c
CSIP_RETCODE CSIPsetInitialSolution(CSIP_MODEL *model, double *values)
```

设置初始解

将各个变量依次赋值为values数组中的值

### CSIPgetInternalSCIP

```c
void *CSIPgetInternalSCIP(CSIP_MODEL *model)
{
    return model->scip;
}
```
