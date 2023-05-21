// Implementation of command suggestions

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Project header files
#include "cli.h"
#include "uart.h"

#define ASCII_SPACE             32

void sugg_printSuggestion(cliNode* root, char* word) {
    cliNode* temp = root;
    if (temp->is_end){
        for(uint8_t i=0; word[i]!='\0'; i++) {
            uart_write(word[i]);
        }
        uart_write(ASCII_SPACE);
    }

    for (uint8_t j=0; j < ALPHABET_SIZE; j++){
        if (temp->next[j]){
            char letter = 'a' + j;
            char* newWord = malloc((strlen(word) + 2));
            strcpy(newWord, word);
            newWord[strlen(word)] = letter;
            newWord[strlen(word) + 1] = '\0';
            sugg_printSuggestion(temp->next[j], newWord);
            free(newWord);
        }
    }
}

void sugg_searchPrefix(cliNode* root, char* word) {
    cliNode* temp = root;
    for (uint8_t i=0; i < word[i]!='\0'; i++){
        word[i] = tolower(word[i]);
        uint8_t position = word[i] - 'a';

        if (!temp->next[position]){
            // Command does not exist
            return;
        }
        temp = temp->next[position];
    }
    if (temp->is_end){
        // Command is already correct
    }
    // Find all possible commands
    sugg_printSuggestion(temp, word);
    return;
}
