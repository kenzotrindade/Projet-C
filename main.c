#include <stdio.h>
#include "library.h"

int main() {
    if (file_exist("file.txt") == 0) {
        printf("The file exist.\n");
    } else if (file_exist("file.txt") == 1){
        printf("The file does'nt exist\n");
    }
}