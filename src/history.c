// Implementation of command history

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Project header files
#include "history.h"
#include "uart.h"
#include "cli.h"

extern char readBuffer[];
extern char readBufferIndex;
historyNode *head = NULL, *tail = NULL;

historyNode* hist_newNode(void) {
    historyNode* node = (historyNode*) calloc (1, sizeof(historyNode));
    return node;
}

void hist_freeNode(void) {
    while (head != NULL){
        free(head);
        head = head->next;
    }
}

void hist_insertCmd(char* cmd) {
    historyNode* node = hist_newNode();
    node->cmd = strdup(cmd);
    if (head == NULL){
        tail = node;
    } else {
        head->prev = node;
    }
    node->next = head;
    head = node;
}

void hist_selectOlderElement(void) {
    if (head != NULL){
        hist_displayCmd(head->cmd);
        if (head->next != NULL){
            head = head->next;
        }
    }
}

void hist_selectNewerElement(void) {
    if (head != NULL){
        hist_displayCmd(head->cmd);
        if (head->prev != NULL){
            head = head->prev;
        }
    }
}

void hist_displayCmd(char* cmd){
    uart_clearLine();
    cli_clearBuffer();
    readBufferIndex=0;
    for (uint8_t i = 0; cmd[i] != '\0'; i++){
        readBuffer[readBufferIndex] = cmd[i];
        readBufferIndex++;
        uart_write(cmd[i]);
    }
}
