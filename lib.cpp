#include "lib.h"
#include <iostream>

unsigned long long getFuctorial(unsigned int n)
{
    if(n == 0 || n == 1)
        return 1;
    return getFuctorial(n - 1)*n;
}