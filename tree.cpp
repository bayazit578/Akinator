#include "tree.h"

#include "include.h"
#include "constants.h"

void tree_create(Tree* tree) {
    tree->root = new_node(NULL);
    tree->size = 1;
}

Node* new_node(Node* parent) {
    Node* new_node = (Node*)calloc(1, sizeof(Node));

    assert(new_node && "Error of new_node allocation.");

    new_node->value = NULL;
    new_node->parent = parent;
    new_node->left = NULL;
    new_node->right = NULL;

    new_node->allocated = false;//вспомогательные элементы
    new_node->rank = 0;

    return new_node;
}

Node* insert_elem(Node* node, char* value, size_t rank) {
    if(node == NULL) {
        Node* node = new_node(NULL);

        node->value = value;
        node->rank = rank;
        return node;
    }

    // printf("ptr:%p\n", node);

    if(value < node->value)
        node->left = insert_elem(node->left, value, rank + 1);
    else if(value > node->value)
        node->right = insert_elem(node->right, value, rank + 1);

    return node;
}

Node* read_node(Node* node, char** pointer, Node* parent) {
    while(**pointer == ' ')
        (*pointer)++;

    if (**pointer == ')')
        (*pointer)++;

    if(**pointer == '(') {
        (*pointer)++;

        node = new_node(parent);

        if(**pointer == '\"') {
            (*pointer)++;

            size_t counter = 0;
            while((*pointer)[counter] != '\"' && (*pointer)[counter] != '\0') {//value = *pointer
                counter++;
            }
            node->value = *pointer;
            node->value[counter] = '\0';//закрытие строки

            node->allocated = false;

            *pointer += (counter + 1);

            if(**pointer == '\"')
                (*pointer)++;
        }

        node->left = read_node(node->left, pointer, node);

        node->right = read_node(node->right, pointer, node);

        while (**pointer == ' ')
            (*pointer)++;

        if (**pointer == ')')
            (*pointer)++;

        #ifndef NDEBUG
            printf("------------------\n"
                   "node:%p\n"
                   "value:%s\n"
                   "parent:%p\n"
                   "left:%p\n"
                   "right:%p\n", node, node->value, node->parent,
                                 node->left, node->right);
            if((node->left) && (node->right)) {
                printf("left value:%s\n"
                       "right value:%s\n", node->left->value, node->right->value);
            }
            printf("------------------\n");
        #endif //NDEBUG

        return node;
    }

    else if(!memcmp(*pointer, "nil", 3)) {
        (*pointer) += 3;
        return NULL;
    }

    fprintf(stderr, RED "Invalid tree entry form: %c.\n" RESET, **pointer);
    return NULL;
}

void burn_the_tree(Node* node) {

    if(node->left)
        burn_the_tree(node->left);

    if(node->right)
        burn_the_tree(node->right);

    if(node) {
        if(node->allocated)
            free(node->value);
        free(node);
    }
}

void new_criterion(Node* node) {
    char* crit = (char*)calloc(100, sizeof(char));
    printf("Напиши критерий по которым твой персонаж отличается от моего:\n");
    scanf("%s", crit);

    char* character = (char*)calloc(100, sizeof(char));
    printf("Напиши название своего персонажа:\n");
    scanf("%s", character);

    node->left = new_node(node);
    node->left->value = node->value;
    node->allocated = true;

    node->right = new_node(node);
    node->right->value = character;
    node->right->allocated = true;

    node->value = crit;
}
