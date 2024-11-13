#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    char *pipePath;
    int pipeFlag, fd;
    pipePath = "/home/shakil/Documents/chatPipe";
    if (access(pipePath, F_OK))
    {
        printf("Pipe is already created");
    }
    else
    {
        pipeFlag = mkfifo(pipePath, 0666);
    }
    char buffer[200];

    do
    {
        // write
        fd = open("chatPipe", O_WRONLY);
        int n = read(STDIN_FILENO, &buffer, sizeof(buffer));
        buffer[n] = '\0';
        write(fd, buffer, strlen(buffer) + 1);
        fclose(fd);

        // read

        fd = open("chatPire", O_RDONLY);
        n = read(fd, &buffer, sizeof(buffer));
        buffer[n] = '\n';
        write(STDOUT_FILENO, buffer, strlen(buffer));
        fclose(fd);
    } while (strcmp(buffer, "bye\n") != 0);
    return 0;
}