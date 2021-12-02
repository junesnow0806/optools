#ifndef _CONSTRAINT_HPP_
#define _CONSTRAINT_HPP_
#include "varible.hpp"
#define LT 0
#define LE 0
#define EQ 0
#define BT 0
#define BE 0
#endif

class singleCons
{
    singleCons() = delete;
};

class unEqualCons : singleCons
{
private:
    int type;
    double *coefficient;
    unEqualCons(int varNum);
};

class integerCons
{
private:
    int varCode;
};

class constraint
{
private:
    varible vars;
    int consNum;
    singleCons *cons;
};