// UART connection with PC
#ifndef _Tobias_UART_
#define _Tobias_UART_

// Initialize UART connection
void uart_init(void);

// Read data from UART
char uart_read(void);

// Write data to UART
void uart_write(char uartPrompt);

// Send an enter over UART
void uart_endLine(void);

// Remove last typed character
void uart_backSpace(void);

// Clear the entire line
void uart_clearLine(void);

// End UART connection and shut down program
void uart_end(void);

#endif
