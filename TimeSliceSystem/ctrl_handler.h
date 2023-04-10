#pragma once

#include "stdio.h"
#include "stdbool.h"
#include "signal.h"

// https://learn.microsoft.com/de-de/cpp/c-runtime-library/reference/signal?view=msvc-170

// signal to set on exit for graceful shutdown
sig_atomic_t volatile g_running = 1;

void ctrl_handler(int signum)
{
    // SIGINT tells it is an interrupt signal
    if (signum == SIGINT) {
        printf("\nCTRL+C detected!\n");
        // unset running flag
        g_running = 0;
    }
}

bool set_ctrl_handler() 
{
    // set handler for sigint
    signal(SIGINT, &ctrl_handler);
}   
