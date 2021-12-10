#ifndef _CONSTRAINT_HPP_
#define _CONSTRAINT_HPP_
#include "varible.hpp"
#define LT 0
#define LE 0
#define EQ 0
#define BT 0
#define BE 0

class singleCons
{
public:
    singleCons() = default;
};

class unEqualCons : singleCons
{
public:
    unEqualCons(int varNum, double *co, int type_) : type(type_) //可改为coefficient=co
    {
        coefficient = new double[varNum];
        for (int i = 0; i < varNum; ++i)
            coefficient[i] = co[i];
    }

private:
    int type;
    double *coefficient;
};

class integerCons
{
public:
    integerCons(int code) : varCode(code) {}

private:
    int varCode;
};

class constraint
{
public:
    constraint() = delete;
    constraint(int varNum, std::string *names) : consNum(0), cons(nullptr)
    {
        vars = new varible(varNum, names);
    };
    void addCon();

private:
    varible *vars;
    int consNum;
    singleCons *cons;
};
#endif