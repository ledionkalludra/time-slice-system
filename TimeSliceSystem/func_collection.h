#pragma once

#ifdef _WIN32
#include "windows.h"
#define SLEEP(x) Sleep(x)
#else
#include "unistd.h"
#define SLEEP(x) sleep(x/1000)
#endif

#define PRINT_FUNCTION_AND_SLEEP(x) printf("%s: Start -> Sleep %ds -> Stop\n", __FUNCTION__, x); SLEEP(x);

void f_a()
{
    PRINT_FUNCTION_AND_SLEEP(500);
}

void f_b()
{
    PRINT_FUNCTION_AND_SLEEP(500);
}

void f_c()
{
    PRINT_FUNCTION_AND_SLEEP(500);
}

void f_d()
{
    PRINT_FUNCTION_AND_SLEEP(500);
}

void f_e()
{
    PRINT_FUNCTION_AND_SLEEP(500);
}