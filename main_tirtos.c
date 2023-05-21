//Start thread that runs CLI
#include <stdint.h>
#include <stddef.h>

// POSIX Header files
#include <pthread.h>

// RTOS header files
#include <ti/sysbios/BIOS.h>
#include <ti/drivers/Board.h>
#include <ti/drivers/GPIO.h>

// Driver configuration
#include "ti_drivers_config.h"

extern void *cliThread(void *arg0);

// Stack size in bytes
#define THREADSTACKSIZE 4096


int main(void)
{
    pthread_t thread;
    pthread_attr_t attrs;
    struct sched_param priParam;
    int retc;

    Board_init();

    // Initialize the attributes structure with default values
    pthread_attr_init(&attrs);

    // Set priority, detach state, and stack size attributes
    priParam.sched_priority = 1;
    retc                    = pthread_attr_setschedparam(&attrs, &priParam);
    retc |= pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0)
    {
        // failed to set attributes
        while (1) {}
    }

    retc = pthread_create(&thread, &attrs, cliThread, NULL);
    if (retc != 0)
    {
        // pthread_create() failed
        while (1) {}
    }

    BIOS_start();

    return (0);
}
