#include "user_io.h"

#include "include.h"
#include "tree.h"

void dialogue(Tree* tree) {
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
    printf("%s Да[y]\\Нет[n]\n", node->value);//function

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
