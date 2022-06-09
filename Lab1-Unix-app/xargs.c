#include "kernel/types.h"
#include "user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    int i, j, new_i, k;
    char *str[MAXARG], word[MAXARG], new_str[MAXARG];
    for (i = 0; i < argc - 1; i++)
    {
        str[i] = argv[i + 1];
    }
    while(read(0, word, sizeof(word)) > 0)
    {
        new_i = i;
        k = 0;
        for (j = 0; j < strlen(word); j++)
        {
            if (word[j] == '\n') 
            {
                str[new_i] = (char *)malloc(MAXARG);
                strcpy(str[new_i], new_str);
                memset(new_str, 0, MAXARG);
                k = 0;
                if(fork() == 0) exec(argv[1], str);
                else wait(0);     
            }
            else if (word[j] == ' ') 
            {
                str[new_i] = (char *)malloc(MAXARG);
                strcpy(str[new_i], new_str);
                memset(new_str, 0, MAXARG);
                new_i += 1;
                k = 0;
            }
            else new_str[k++] = word[j]; 
        }  
    }
    exit(0);
}