#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[] = "This is a \"quoted string\" with some spaces.";
    char* token;
    token = strtok_quoted(str, " ");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok_quoted(NULL, " ");
    }
    return 0;
}



