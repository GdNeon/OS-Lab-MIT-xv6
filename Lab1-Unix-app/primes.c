#include "kernel/types.h"
#include "user.h"

int a[34];
void trans(int a[], int n)
{
    if (n == 1)
    {
        printf("prime %d\n", a[0]);
        return;
    }
    printf("prime %d\n", a[0]);
    int fd[2] = {0};
    int p = a[0];
    if (pipe(fd) == -1)
    {
        printf("pipe error");
        return;
    }
    int pid = fork();
    if (pid == 0)
    {
        int t, i = 0, j = 0, count = 0;
        close(fd[1]);
        while (i < n)
        {
            read(fd[0], &t, 2);
            if (t % p != 0)
            {
                a[j] = t;
                j++;
                count++;
            }
            i++;
        }
        trans(a, count);
        exit(0);
    }
    else 
    {
        int i;
        close(fd[0]);
        for (i = 0; i < n; i++)
        {
            write(fd[1], a + i, 2);
        }    
    }
    wait(0);
}

int main(int argc, char* argv[])
{
    int i;
    for (i = 0; i < 34; i++)
    {
        a[i] = i + 2;
    }
    trans(a, 34);
    exit(0);
}