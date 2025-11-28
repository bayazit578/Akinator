#ifndef DUMP_H
#define DUMP_H

#include "include.h"
#include "tree.h"

void tree_dump(Tree* tree, const char* filename);
void node_dump(Node* node, FILE* dot_file);

#endif //DUMP_H
