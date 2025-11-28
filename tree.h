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
        bool allocated;
        };

void  tree_create(Tree* tree);
Node* new_node(Node* parent);
Node* insert_elem(Node* node, int value, size_t rank);
Node* read_node(Node* node, char** pointer, Node* parent);
void  burn_the_tree(Node* node);
void  new_criterion(Node* node);

#endif // TREE_H
