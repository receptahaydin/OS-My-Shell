#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (strcmp(argv[3], "clear") == 0) // shell ekranı temizlenir
    {
        printf("\033[H\033[J");
    }
    else if (strcmp(argv[3], "ls") == 0) // girilen sayı kadar ls programı çalıştırılır
    {
        for (int i = 0; i < atoi(argv[2]); i++)
        {
            system("/bin/ls");
        }
    }
    else if (strcmp(argv[3], "bash") == 0) // default shell programına yani bash'e geçilir
    {
        system("/bin/bash");
    }
    else if (strcmp(argv[3], "exit") == 0) // programdan çıkış yapılır
    {
        for (int i = 0; i < atoi(argv[2]); i++)
        {
            exit(0);
        }
    }
    else if (strcmp(argv[3], "writef") == 0 && !strcmp(argv[4], "-f") && argv[5] != NULL && argc == 6) // girilen sayı kadar writef programı çalıştırılır
    {
        int f, j;
        f = fork();
        if (f == 0)
        {
            j = execve("writef", argv, NULL);
            exit(0);
            perror("exec failed");
        }
        else
        {
            wait(&j);
        }
    }
    else
    {
        printf("Hatali komut!\n");
    }
}