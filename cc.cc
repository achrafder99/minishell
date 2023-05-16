#include <stdio.h>
#include <string.h>

void addSpaces(char* str) {
    char temp[strlen(str) * 2];
    int j = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '>' || str[i] == '<' || str[i] == '|' && (str[i + 1] != '>' && str[i + 1] != '<'))
        {
            if (i > 0 && str[i - 1] != ' ')
                temp[j++] = ' ';
            temp[j++] = str[i];

            if (i < strlen(str) - 1 && str[i + 1] != ' ')
                temp[j++] = ' ';
        }
        else
            temp[j++] = str[i];
    }

    temp[j] = '\0';
    strcpy(str, temp);
}

int main() {
    char *str = strdup("ls -la>append.txt<heredoc|pipe>out");
    printf("Before: %s\n", str);

    addSpaces(str);
    printf("After:  %s\n", str);

    return 0;
}