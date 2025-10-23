#include <stdio.h>

typedef struct n{
    int id;
    struct n **links;
}Node;

void file_exist();