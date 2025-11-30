#include "include.h"

#include "tree.h"
#include "read_file.h"
#include "dump.h"
#include "user_io.h"

int main(size_t argc, char* argv[]) {

    if(argc < 3) {
        fprintf(stderr, RED "Too few input args. Please, enter it.\n" RESET);
        return 1;
    }

    else if(argc > 3) {
        fprintf(stderr, RED "Invalid filename or mode. Please, enter it correctly.\n" RESET);
        return 1;
    }
    FILE* in_file = fopen(argv[1], "r+");
    size_t size_buff = 0;
    char* buff = read_file(in_file, &size_buff);

    #ifndef NDEBUG
        printf(YELLO "Buff contents:\n" );
        printf("%s", buff);
        printf(RESET "\n");
    #endif // NDEBUG

    Tree tree = {}; // Тут был Даня Жебряков

    char* pointer = buff;
    tree.root = read_node(tree.root, &pointer, NULL);

    if(!memcmp(argv[2], "akinator", 8)) {
        akinator_mode(&tree);
    }

    else if(!memcmp(argv[2], "comparator", 10)) {
        comparative_mode(&tree);
    }

    fseek(in_file, 0, SEEK_SET);

    tree_dump(&tree, "tree.dot");

    burn_the_tree(tree.root);
    free(buff);

    return 0;
}
