// Implementation of command history
#ifndef _Tobias_HISTORY_
#define _Tobias_HISTORY_

typedef struct historyNode {
    char* cmd;
    struct historyNode* next;
    struct historyNode* prev;
} historyNode;

// Create a new node and allocate memory
historyNode* hist_newNode(void);

// Remove node and free memory
void hist_freeNode(void);

// Insert command in list
void hist_insertCmd(char* cmd);

// Select older command in list
void hist_selectOlderElement(void);

// Select newer command in list
void hist_selectNewerElement(void);

// Put historic command in readBuffer and print
void hist_displayCmd(char* cmd);

#endif
