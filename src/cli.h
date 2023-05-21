// Implementation of command line interface
#ifndef _Tobias_CLI_
#define _Tobias_CLI_

#include <stdbool.h>

#define ALPHABET_SIZE           26

typedef void (*funcPtr)();
typedef struct cliNode {
    char str;
    funcPtr func;
    struct cliNode *next[ALPHABET_SIZE];
    bool is_end;
} cliNode;

// Create a new node and allocate memory
cliNode* cli_newNode(char str);

// Remove node and free memory
void cli_freeNode(cliNode* node);

// Insert string into tree
cliNode* cli_insertTree(cliNode* root, char* word, void (*func)());

// Search tree for string
funcPtr cli_searchTree(cliNode* root, char* word);

// Print whether string is found in tree or not and executes
void cli_printSearch(cliNode* root, char* word);

// Send list of all commands over uart
void cli_help(void);

// Set uart input buffer to zero
void cli_clearBuffer(void);

// Print list of commands that have the selected prefix
void cli_printSuggestion(cliNode* root, char* word);

// Search whether prefix is found in tree or not
void cli_searchPrefix(cliNode* root, char* word);

#endif
