// Implementation of command line interface

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// RTOS header files
#include <ti/drivers/GPIO.h>

// Driver configuration
#include "ti_drivers_config.h"

// Project header files
#include "cli.h"
#include "history.h"
#include "leds.h"
#include "uart.h"
#include "cmds.h"
#include "suggestions.h"

#define BUFFER_SIZE             255

#define ASCII_ENTER             13
#define ASCII_BACKSPACE         8
#define ASCII_TAB               9
#define ASCII_SPACE             32
#define ASCII_ESCAPE            27
#define ASCII_BRACKET           91

#define ASCII_CAPITAL_A         65
#define ASCII_CAPITAL_Z         90
#define ASCII_SMALL_A           97
#define ASCII_SMALL_Z           122

char readBuffer[BUFFER_SIZE];
char readBufferIndex = 0;

cliNode *cliTree = NULL;
extern historyNode *historyList;

void cli_init(void) {
    cliTree = cli_newNode('\0');
    for (int i=0; i < AMOUNT_OF_COMMANDS; i++) {
        cliTree = cli_insertTree(cliTree, cmdList[i], funcList[i]);
    }
}

cliNode* cli_newNode(char str) {
    cliNode* node = (cliNode*) calloc (1, sizeof(cliNode));
    for (uint8_t i = 0; i < ALPHABET_SIZE; i++) {
        node->next[i] = NULL;
    }
    node->is_end = false;
    node->str = str;
    return node;
}

void cli_freeNode(cliNode* node) {
    for(uint8_t i=0; i < ALPHABET_SIZE; i++) {
        if (node->next[i] != NULL) {
            cli_freeNode(node->next[i]);
        }
    }
    free(node);
}

cliNode* cli_insertTree(cliNode* root, char* word, void (*func)()) {
    cliNode* temp = root;

    for (uint8_t i=0; word[i] != '\0'; i++) {
        uint8_t idx = (uint8_t) word[i] - 'a';
        if (temp->next[idx] == NULL) {
            temp->next[idx] = cli_newNode(word[i]);
        }
        else {

        }
        temp = temp->next[idx];
    }
    temp->func = func;
    temp->is_end = true;
    return root;
}

funcPtr cli_searchTree(cliNode* root, char* word) {
    cliNode* temp = root;

    for(uint8_t i=0; word[i]!='\0'; i++) {
        word[i] = tolower(word[i]);
        uint8_t position = word[i] - 'a';
        if (temp->next[position] == NULL) {
            return NULL;
        }
        temp = temp->next[position];
    }
    if (temp != NULL && temp->is_end == true) {
        return temp->func;
    }
    else {
        return NULL;
    }
}

void cli_printSearch(cliNode* root, char* word) {
    funcPtr cmd = cli_searchTree(root, word);
    if (cmd == NULL) {
        char nf[] = "Command not found";
        for (uint8_t i=0; i<sizeof(nf); i++){
            uart_write(nf[i]);
        }
        uart_endLine();
    }
    else {
        char f[] = "Command accepted";
        for (uint8_t i=0; i<sizeof(f); i++){
            uart_write(f[i]);
        }
        uart_endLine();
        cmd();
    }
}

void cli_help(void) {
    for (uint8_t i=0; i < AMOUNT_OF_COMMANDS; i++){
        char* str = cmdList[i];
        for(uint8_t j=0; str[j]!='\0'; j++) {
            uart_write(str[j]);
        }
        uart_endLine();
    }
}

void cli_clearBuffer(void) {
    for (uint8_t i=0; i < BUFFER_SIZE; i++){
        readBuffer[i] = 0;
    }
}

void *cliThread(void *arg0) {

    GPIO_init();

    uart_init();
    leds_init();
    cli_init();

    bool escActive = false;

    // Main loop
    while (1)
    {
        char uartInput = uart_read();
        switch (uartInput)
        {
        case ASCII_ENTER:
            uart_endLine();
            cli_printSearch(cliTree, readBuffer);
            hist_insertCmd(readBuffer);
            cli_clearBuffer();
            readBufferIndex=0;
            break;

        case ASCII_BACKSPACE:
            if (readBufferIndex > 0) {
                readBuffer[readBufferIndex] = 0;
                readBufferIndex--;
                readBuffer[readBufferIndex] = 0;
            }
            uart_backSpace();
            break;

        case ASCII_TAB:
            uart_endLine();
            char c[] = "Possible commands: ";
            for (uint8_t i = 0; i < sizeof(c); i++){
                uart_write(c[i]);
            }
            sugg_searchPrefix(cliTree, readBuffer);
            uart_endLine();
            cli_clearBuffer();
            readBufferIndex=0;
            break;

        case ASCII_ESCAPE:
            escActive = true;
            break;

        case ASCII_BRACKET:
            //do nothing
            break;

        default:
            if (escActive){
                if (uartInput == 'A'){ //Arrow up
                    hist_selectOlderElement();
                }
                else if (uartInput == 'B'){ //Arrow down
                    hist_selectNewerElement();
                }
                escActive = false;
            } else
            if ((ASCII_CAPITAL_A <= uartInput && uartInput <= ASCII_CAPITAL_Z) || (ASCII_SMALL_A <= uartInput && uartInput <= ASCII_SMALL_Z)){ //NaN
                uart_write(uartInput);
                if (readBufferIndex < BUFFER_SIZE){
                    readBuffer[readBufferIndex] = uartInput;
                    readBufferIndex++;
                }
            }
            break;
        }
    }
}
