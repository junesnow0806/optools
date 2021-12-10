#ifndef _VARIBLE_HPP_
#define _VARIBLE_HPP_
#include <string>

class varible
{
public:
    varible() = delete;
    varible(int num, std::string *ptr) : varNum(num), names(ptr) {}
    ~varible()
    {
        delete[] names;
    }

private:
    int varNum;
    std::string *names;
};
#endif