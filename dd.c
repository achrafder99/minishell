#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int fd[2];
    char buffer[20];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int fd1 = open("a.txt",O_RDWR | O_CREAT,0777);
    int fd2 = open("b.txt",O_RDWR | O_CREAT,0777);

    printf("%d\n",fd1);
    printf("%d\n",fd2);
    pipe(fd);
    fd[0] = fd1;
    fd[1] = fd2;
    printf("%d\n",fd[0]);
    printf("%d\n",fd[1]);
    write(fd[1], "hello", strlen("hello"));
    read(fd[0], buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);
    close(fd[0]);
    close(fd[1]);

    return 0;
}