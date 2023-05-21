// UART connection with PC

#include <stdint.h>
#include <stddef.h>

// RTOS header files
#include <ti/drivers/UART2.h>

// Driver configuration
#include "ti_drivers_config.h"

// Project header files
#include "uart.h"
#include "cli.h"
#include "history.h"

#define UART_BAUDRATE   115200

static UART2_Handle uart;
static UART2_Params uartParams;
static uint32_t status = UART2_STATUS_SUCCESS;

extern cliNode *cliTree;
extern historyNode *historyList;

void uart_init(void){
    // Create a UART where the default read and write mode is BLOCKING
    UART2_Params_init(&uartParams);
    uartParams.baudRate = UART_BAUDRATE;

    uart = UART2_open(CONFIG_UART2_0, &uartParams);

    if (uart == NULL)
    {
        /* UART2_open() failed */
        while (1) {}
    }

    const char initPrompt[] = "Type help for list of commands.\r\n";
    for (int i=0; i<sizeof(initPrompt); i++){
        uart_write(initPrompt[i]);
    }
}

char uart_read(void){
    char uartResult;
    size_t bytesRead = 0;
    while (bytesRead == 0)
    {
        status = UART2_read(uart, &uartResult, 1, &bytesRead);

        if (status != UART2_STATUS_SUCCESS)
        {
            /* UART2_read() failed */
            while (1)
            {
            }
        }
    }
    return uartResult;
}

void uart_write(char uartPrompt){
    size_t bytesWritten = 0;
    while (bytesWritten == 0)
    {
        status = UART2_write(uart, &uartPrompt, sizeof(uartPrompt), &bytesWritten);

        if (status != UART2_STATUS_SUCCESS)
        {
            // UART2_write() failed
            while (1)
            {
            }
        }
    }
}

void uart_endLine(void){
    const char endLine[] = "\r\n";
    size_t bytesWritten = 0;
    while (bytesWritten == 0)
    {
        status = UART2_write(uart, endLine, sizeof(endLine), &bytesWritten);

        if (status != UART2_STATUS_SUCCESS)
        {
            // UART2_write() failed
            while (1)
            {
            }
        }
    }
}

void uart_backSpace(void){
    const char backSpace[] = "\x1b[D \x1b[D";
    size_t bytesWritten = 0;
    while (bytesWritten == 0)
    {
        status = UART2_write(uart, backSpace, sizeof(backSpace), &bytesWritten);

        if (status != UART2_STATUS_SUCCESS)
        {
            // UART2_write() failed
            while (1)
            {
            }
        }
    }
}

void uart_clearLine(void){
    const char clearLine[] = "\x1B[2K \x1B[1G";
    size_t bytesWritten = 0;
    while (bytesWritten == 0)
    {
        status = UART2_write(uart, clearLine, sizeof(clearLine), &bytesWritten);

        if (status != UART2_STATUS_SUCCESS)
        {
            // UART2_write() failed
            while (1)
            {
            }
        }
    }
}

void uart_end(void){
    const char endPrompt[] = "\r\nClosing UART connection. Have a nice day.\r\n";
    size_t bytesWritten = 0;
    while (bytesWritten == 0)
    {
        UART2_write(uart, endPrompt, sizeof(endPrompt), &bytesWritten);

        if (status != UART2_STATUS_SUCCESS)
        {
            // UART2_write() failed
            while (1)
            {
            }
        }
    }
    cli_freeNode(cliTree);
    hist_freeNode();
    while(1){
        //Loop forever
    }
}

