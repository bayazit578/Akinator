#ifndef USER_IO_H
#define USER_IO_H

#include "tree.h"

typedef struct compare {
                char* commons[100] = {};
                char* differences1[100] = {};
                char* differences2[100] = {};
                } compare;

bool    get_answer();
void    akinator_mode(Tree* tree);
void    dialogue_node(Node* node);
void    comparative_mode(Tree* tree);
compare compare_paths(stack* path1, stack* path2);
stack*  search_node_n_stack_path(Node* root);

#endif //USER_IO_H
