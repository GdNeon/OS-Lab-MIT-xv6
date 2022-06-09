#include "kernel/types.h"
#include "user.h"

int main(int argc, char* argv[]){
    int fd1[2] = {0}; //用于父进程发送ping给子进程接收
    int fd2[2] = {0}; //用于子进程发送pong给父进程接收
    if(pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        printf("pipe error");
        return 1;
    }
    int pid;
    pid = fork();
    if(pid == -1)
    {
        printf("fork error");
        return 2;
    }
    if(pid == 0)
    /*child*/
    {
        char* msg1 = "xxxx"; //先设置成一个任意值
        char* msg2 = "pong";
        close(fd1[1]);
        close(fd2[0]);
        read(fd1[0], msg1, sizeof(msg1));
        printf("%d: received %s\n", getpid(), msg1);
        write(fd2[1], msg2, sizeof(msg2));
        exit(0);
    }
    else 
    /*parent*/
    {
        char* msg1 = "ping";
        char* msg2 = "xxxx"; //先设置成一个任意值
        close(fd1[0]);
        close(fd2[1]);
        write(fd1[1], msg1, sizeof(msg1));
        read(fd2[0], msg2, sizeof(msg2));
        printf("%d: received %s\n", getpid(), msg2);
    }
    wait(0);
    exit(0);
}