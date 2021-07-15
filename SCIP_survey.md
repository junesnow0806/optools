# SCIP调研报告

***

梁峻滔

2021/7/15

***

## 一、SCIP简介

SCIP是一款用于求解混合整数规划问题和混合整数非线性规划问题的解算器，它允许用户控制整个求解过程和访问解算器内部的细节信息。SCIP被实现成C可调用库，并为用户插件提供C++封装类，它还可以作为一个独立的程序，用于求解各种形式的混合整数线性和非线性规划问题。

SCIP的使用通常是和SCIP优化套装(SCIP Optimization Suite)绑定在一起的，SCIP Optimization Suite包含以下几个部分：

* `SCIP`：混合整数(线性和非线性)规划问题的解算器，约束规划问题的框架
* `SoPlex`：线性规划问题解算器
* `ZIMPL`：数学编程语言
* `PaPILO`：parallel presolve for integer and linear optimization
* `UG`：parallel framework for mixed integer (linear and nonlinear) programs 
* `GCG`：generic branch-cut-and-price solver

用户可以用ZIMPL生成线性规划问题、混合整数规划问题等的数学模型，然后将生成的模型加载到SCIP中求解，在求解过程中SCIP可能会用到SoPlex来求解底层的线性规划问题。

## 二、SCIP功能

1. 主要的函数

    main.c中主要用到的函数是`SCIPrunShell()`，该函数在scipshell.c中实现。

    ```c
    //scipshell.c
    SCIP_RETCODE SCIPrunShell(
        int agrc, 
        char **argv, 
        const char *defaultsetname //默认设置文件的文件名
    );
    //SCIPrunShell()运行一个类似shell程序的函数, 在此shell中接收用户输入的命令
    //命令包含用于创建问题的输入文件和参数
    //通过调用SCIPprocessShellArguments()等来读取、处理命令中的参数
    //之后主要是在SCIPprocessShellArguments()中调用fromCommand()函数
    //来创建、求解问题并输出最优解
    
    SCIP_RETCODE SCIPprocessShellArguments(
        SCIP *scip, //SCIP数据结构
        int argc,
        char **argv,
        const char *defaultsetname
    );
    
    /*Problem Creation + Problem Solving + Solution Output*/
    static SCIP_RETCODE fromCommandLine(
    	SCIP *scip,          
        const char *filename //输入文件的文件名
    );
    
    /*fromCommandLine()中的子函数,*/
    /*Problem Creation*/
    //在scip_prob.c中实现
    //reads problem from file and initializes all solving data structures
    SCIP_RETCODE SCIPreadProb(
    	SCIP *scip,
        const char *filename, //problem file name
        const char *extension
    );
    
    /*Problem Solving*/
    //在scip_solve.c中实现
    //transforms, presolves, and solves problem
    SCIP_RETCODE SCIPsolve(SCIP *scip);
    
    /*Solution Output*/
    //在scip_sol.c中实现
    //return the best feasible primal solution so far
    SCIP_SOL *SCIPgetBestSol(SCIP *scip);
    SCIP_RETCODE SCIPcreateSolCopy(
        SCIP *scip,
        SCIP_SOL **sol,     //pointer to store the solution
        SCIP_SOL *sourcesol //primal CIP solution to copy
    );
    //retransforms solution to original problem space
    SCIP_RETCODE SCIPretransformSol(
        SCIP *scip, 
        SCIP_SOL *sol //primal CIP solution
    );
    SCIP_RETCODE SCIPprintSol(
        SCIP *scip,
        SCIP_SOL *sol,       //primal solution
        FILE *file,          //output file (or NULL for standard output)
        SCIP_Bool printzeros //whether variables set to zero be printed
    );
    SCIP_RETCODE SCIPfreeSol(SCIP *scip, SCIP_SOL **sol);
    /*fromCommandLine()中的子函数end*/
        
    //SCIPprocessShellArguments()调用，解析一个由SCIPprintReal()编写的实数值
    unsigned int SCIPparseReal(
        SCIP *scip,
        const char *str,
        double *value,
        char **endptr
    );
    ```

2. 输入输出格式

    ```c
    //main.c
    /** main method starting SCIP */
    int main(
    	int argc,   /**< number of arguments from the shell */
    	char **argv /**< array of shell arguments */
    	)
    {
       SCIP_RETCODE retcode;
    
       (void)signal(SIGTERM, handleSigterm);
       /* run interactive shell */
       retcode = SCIPrunShell(argc, argv, "scip.set");
    
       /* evaluate retrun code of the SCIP process */
       if( retcode != SCIP_OKAY )
       {
          /* write error back trace */
          SCIPprintError(retcode);
          return -1;
       }
    
       return 0;
    }
    ```

    从这段简短的main函数可以发现，SCIP的功能是通过在命令行窗口中输入执行SCIP可执行文件的命令，将输入的命令和名为scip.set的默认设置文件作为输入参数，然后主要通过运行`SCIPrunShell()`函数来实现其功能。在`SCIPrunShell()`中启动一个shell程序，在shell程序中输入求解命令和问题所在文件，之后会相继调用`SCIPreadProb()`、`SCIPsolve()`、`SCIPprintSol()`，求解后将最优解输出到指定文件或者标准输出上。

    输出格式：

    ```c
    //scip_sol.c
    /*SCIPprintSol()内部对于输出文件主要调用了以下函数*/
    //向输出文件中输出目标值的提示信息, 还调用该函数输出其他信息, 在message.c中实现
    SCIPmessageFPrintInfo(scip->messagehdlr, file, "objective value:      ");
    //向输出文件中输出一个实数值(目标函数值), 或+/-∞, 在scip_numerics.c中实现
    SCIPprintReal(scip, file, objvalue, 20, 15); 
    //向输出文件中输出最优解, 在sol.c中实现
    SCIPsolPrint(sol, scip->set, scip->messagehdlr, scip->stat, scip->origprob, scip->transprob, file, FALSE, printzeros);
    ```

    

