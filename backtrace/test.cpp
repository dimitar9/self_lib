#include "stacktrace.h"
#include <iostream>
#include <string>

int funca()
{
    int a = 0;
    int b = a+1;
    std::cout << "result from funca is " << a+b << std::endl;
    print_stacktrace(stdout);

}

int main()
{
    funca();
}
