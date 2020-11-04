#include<iostream>

#define s5(a)       Connect_##a
#define s(p)        #p

void Connect_Test(const char* p)
{
    std::cout << "this is Connect Test" << std::endl;
    std::cout << p << std::endl;
}

int main()
{
    s5(Test)("Hello world");

    std::cout << "=======================" << std::endl;
    std::cout << s(p) << std::endl;
    return 0;
}