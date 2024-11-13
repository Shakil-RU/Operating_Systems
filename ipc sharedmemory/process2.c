#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>

int main()
{
    char *pipePath;
    int fd, pipeFlag;
    pipePath = "/home/shakil/Documents/chatPipe";
    if (access(pipePath, F_OK) == 0)
    {
        printf("Pipe already exist\n");
    }
    else
    {
        pipeFlag = mkfifo(pipePath, 0666);
    }
    char buffer[200];
    do
    {
        // read
        fd = open("chatPipe", O_RDONLY);
        int n = read(fd, &buffer, sizeof(buffer) - 1);
        buffer[n] = '\0';
        write(STDOUT_FILENO, buffer, strlen(buffer));
        close(fd);
        // write
        fd = open("chatPipe", O_WRONLY);
        n = read(STDIN_FILENO, &buffer, sizeof(buffer));
        buffer[n] = '\0';
        write(fd, buffer, strlen(buffer)+1);
        fclose(fd);

    }

    while (strcmp(buffer, "bye\n") != 0);
    fclose(fd);
    return 0;
}