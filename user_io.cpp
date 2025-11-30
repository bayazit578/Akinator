#include "user_io.h"

#include "include.h"
#include "tree.h"

void akinator_mode(Tree* tree) {
    printf("Ты хочешь чтобы я отгадал твоего персонажа? Да[y]\\Нет[n]\n");
    bool ans = get_answer();

    while(ans) {
        dialogue_node(tree->root);
        printf("Ты хочешь чтобы я еще раз отгадал твоего персонажа? Да[y]\\Нет[n]\n");
        ans = get_answer();
    }
}

void dialogue_node(Node* node) {
    char answer = 0;
    printf("%s? Да[y]\\Нет[n]\n", node->value);//function

    bool ans = get_answer();

    if(ans) {
        if(node->right) {
            dialogue_node(node->right);
        }

        else {
            printf("Ты: %s!\n", node->value);
        }
    }

    else {
        if(node->left) {
            dialogue_node(node->left);
        }

        else {
            new_criterion(node);
        }
    }
}

bool get_answer() {
    char ch = getchar();

    bool ans = falso;

    if(ch == 'y')
        ans = vera;

    else if(ch == 'n')
        ans = falso;

    else if(isspace(ch))
        ans = get_answer();

    else {
        printf("Неправильный ответ, попробуй еще раз\n"
               "Да[y]\\Нет[n]\n");
        ans = get_answer();
    }

    return ans;
}

void comparative_mode(Tree* tree) {
    printf("Введи первый объект: ");
    stack* path1 = search_node_n_stack_path(tree->root);

    printf("Введи второй объект: ");
    stack* path2 = search_node_n_stack_path(tree->root);

    compare qualities = compare_paths(path1, path2);

    printf("\n");

    printf("Общие черты объектов:\n");
    for(size_t i = 0; qualities.commons[i] != NULL; i++) {
        printf("%s\n", qualities.commons[i]);
    }
    printf("\n");

    printf("Индивидуальные черты первого объекта:\n");
    for(size_t i = 0; qualities.differences1[i] != NULL; i++) {
        printf("%s\n", qualities.differences1[i]);
    }
    printf("\n");

    printf("Индивидуальные черты второго объекта:\n");
    for(size_t i = 0; qualities.differences2[i] != NULL; i++) {
        printf("%s\n", qualities.differences2[i]);
    }
    printf("\n");

    free(path1->data);
    free(path2->data);
    free(path1);
    free(path2);
}

compare compare_paths(stack* path1, stack* path2) {
    compare qualities = {};
    error* err_info = NULL;
    char* quality1 = NULL;
    char* quality2 = NULL;
    size_t counter_commons = 0;
    size_t counter_differences = 0;

    do {
        quality1 = StackPop(&path1, err_info);
        quality2 = StackPop(&path2, err_info);
        // printf("%s %s\n", quality1, quality2);

        if(!(quality1 && quality2)) {
            (qualities.differences1)[counter_differences] = quality1;
            (qualities.differences2)[counter_differences] = quality2;
            // printf("%s %s\n", quality1, quality2);
            counter_differences++;
        }

        else if(!strcmp(quality1, quality2)) {
            (qualities.commons)[counter_commons] = quality1;
            counter_commons++;
        }

        else {
            (qualities.differences1)[counter_differences] = quality1;
            (qualities.differences2)[counter_differences] = quality2;
            // printf("%s %s\n", quality1, quality2);
            counter_differences++;
        }

    } while(quality1 || quality2);

    return qualities;
}

stack* search_node_n_stack_path(Node* root) {
    char* obj = (char*)calloc(100, sizeof(char));

    char ch = 0;
    int counter = 0;
    for(; (ch = fgetc(stdin)) != '\n'; counter++) {
        obj[counter] = ch;
    }
    obj[counter] = '\0';

    Node* target_node = leaf_search(root, obj);

    free(obj);

    stack* path_stk = NULL;

    if(target_node) {
        path_stk = path_to_leaf(target_node);
        return path_stk;
    }

    else {
        printf("Неправильно введен объект, попробуйте еще раз:");
        path_stk = search_node_n_stack_path(root);
    }

    return path_stk;
}
