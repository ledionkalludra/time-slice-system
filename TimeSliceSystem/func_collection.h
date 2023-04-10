#pragma once

#include "time.h"

// macro prints the function, its sleep time and then sleeps
#define PRINT_FUNCTION_AND_SLEEP(x) printf("%s: Start -> Sleep %dms -> Stop\n", __FUNCTION__, x); sleep_ms(x);


// sleep for ms
int sleep_ms(int milliseconds)
{
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    return nanosleep(&ts, NULL);
}

void f_a()
{
    PRINT_FUNCTION_AND_SLEEP(50);
}

void f_b()
{
    PRINT_FUNCTION_AND_SLEEP(50);
}

void f_c()
{
    PRINT_FUNCTION_AND_SLEEP(50);
}

void f_d()
{
    PRINT_FUNCTION_AND_SLEEP(20);
}

void f_e()
{
    PRINT_FUNCTION_AND_SLEEP(20);
}