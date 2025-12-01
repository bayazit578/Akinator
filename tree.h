#ifndef TREE_H
#define TREE_H

#include "include.h"

typedef struct Node Node;

typedef struct Tree {
        Node*  root;
        size_t size;
        } Tree;

struct Node {
        char*  value;
        Node*  parent;
        Node*  left;
        Node*  right;
        size_t rank;
        bool   allocated;
        };

void   tree_create(Tree* tree);
Node*  new_node(Node* parent);
Node*  insert_elem(Node* node, int value, size_t rank);
Node*  read_node(Node* node, char** pointer, Node* parent);
void   burn_the_tree(Node* node);
void   new_criterion(Node* node);
stack* path_to_leaf(Node* node);
void   path_to_stack(stack** path_stk, Node* node, error* err_info);
Node*  leaf_search(Node* node, const char* name);
void tree_printf(Node* node, FILE* out_file);

#endif // TREE_H
