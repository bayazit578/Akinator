#include "dump.h"

#include "include.h"
#include "tree.h"

void tree_dump(Tree* tree, const char* filename) {
    if (tree->root == NULL) {
        fprintf(stderr, RED "List is NULL" RESET "\n");
        return;
    }
    FILE* dot_file = fopen(filename, "w");
    if (dot_file == NULL) {
        fprintf(stderr, RED "Cannot create DOT file" RESET "\n");
        return;
    }

    fprintf(dot_file, "digraph G {\n"
                      "    rankdir=TB;\n"
                      "    bgcolor=\"transparent\";\n"
                      "    node [shape=plaintext, "
                                "style=filled, "
                                "color=\"#ffffffff\", "
                                "fontname=\"Times New Roman\", "
                                "fontcolor=\"white\", "
                                "charset=\"UTF-8\"; "
                                "fontsize=15];\n\n"
                      "    edge[color = \"red\"];\n");
    node_dump(tree->root, dot_file);

    fprintf(dot_file, "}\n");
    fclose(dot_file);
}

void node_dump(Node* node, FILE* dot_file) {
    if(!node)
        return;

    fprintf(dot_file, "    node%zu [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n"
                      "           <TR><TD COLSPAN=\"2\">%s</TD></TR>\n", node, node->value);
    if(node->left != NULL)
        fprintf(dot_file, "           <TR><TD>нет</TD>");
    else
        fprintf(dot_file, "           <TR><TD>0</TD>");
    if(node->right != NULL)
        fprintf(dot_file, "           <TD>да</TD></TR>\n");
    else
        fprintf(dot_file, "           <TD>0</TD></TR>\n");
    fprintf(dot_file, "           </TABLE>>, fillcolor=\"#26f950ff\"];\n");

    fprintf(dot_file, "    {\n"
                      "        rank=%zu;\n"
                      "        node%zu;\n"
					  "    }\n", node->rank, node);

    if(node->left) {
        node_dump(node->left, dot_file);
        fprintf(dot_file, "    node%zu->node%zu\n", node, node->left);
    }

    if(node->right) {
        node_dump(node->right, dot_file);
        fprintf(dot_file, "    node%zu->node%zu\n", node, node->right);
    }
}
