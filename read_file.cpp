#include "read_file.h"

#include "include.h"

char* read_file(FILE* in_file, size_t* size) {
    int fd = fileno(in_file);
    struct stat input_info;
    fstat(fd, &input_info);

    char* buff = (char*)calloc(input_info.st_size + 1, sizeof(char));

    size_t bytes_read = fread(buff, sizeof(buff[0]), input_info.st_size, in_file);
    assert(bytes_read);

    buff[bytes_read] = '\0';

    *size = bytes_read;

    return buff;
}
