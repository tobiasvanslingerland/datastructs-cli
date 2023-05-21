// Implementation of command suggestions
#ifndef _Tobias_SUGG_
#define _Tobias_SUGG_

// Print all possible commands using current prefix
void sugg_printSuggestion(cliNode* root, char* word);

// Check if prefix exists in tree
void sugg_searchPrefix(cliNode* root, char* word);

#endif
