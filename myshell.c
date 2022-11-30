#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char data[50];
    while (1)
    {
        int f, i;
        printf("\nmyshell>>");
        gets(data); // kullanıcıdan input alınır

        const char *commands[10];
        commands[0] = strtok(data, " ");

        for (int i = 1; i < 10; i++)
        {
            commands[i] = strtok(NULL, " "); // alınan input " " karakterine göre parçalanır ve saklanır
        }

        int length_commands = 0;
        while (commands[length_commands] != NULL)
        {
            length_commands++; // kullanıcının kaç adet komut girdiği bulunur
        }

        if (!strcmp(commands[0], "exit")) // exit girilirse program sonlanır
        {
            exit(0);
        }
        else if (!strcmp(commands[0], "writef") && !strcmp(commands[1], "-f") && commands[2] != NULL && length_commands == 3) // writef işlemi aldığı dosya parametresinin içine input yazar, yoksa oluşturup yazar
        {
            f = fork();
            if (f == 0)
            {
                i = execve("writef", commands, NULL);
                perror("exec failed");
            }
            else
            {
                wait(&i);
            }
        }
        else if (!strcmp(commands[0], "bash")) // bash çalıştırılır yani default shell programına geçilir
        {
            system("/bin/bash");
        }
        else if (!strcmp(commands[0], "execx") && !strcmp(commands[1], "-t") && commands[2] != NULL && isNumber(commands[2]) == 1 && length_commands >= 4) // execx işlemi girildiği sayı kadar komutları çalıştırır
        {
            f = fork();
            if (f == 0)
            {
                i = execve("execx", commands, NULL);
                perror("exec failed");
            }
            else
            {
                wait(&i);
            }
        }
        else if (!strcmp(commands[0], "cat") && length_commands > 1) // aldığı dosyanın içini okur
        {
            f = fork();
            if (f == 0)
            {
                i = execve("/bin/cat", commands, NULL);
                perror("exec failed");
            }
            else
            {
                wait(&i);
            }
        }
        else if (!strcmp(commands[0], "ls")) // aldığı dosyanın içindeki dosya isimlerini döndürür
        {
            f = fork();
            if (f == 0)
            {
                i = execve("/bin/ls", commands, NULL);
                perror("exec failed");
            }
            else
            {
                wait(&i);
            }
        }
        else if (!strcmp(commands[0], "clear")) // shell içindeki girilen komutları temizler
        {
            printf("\e[1;1H\e[2J");
        }
        else
        {
            printf("Hatali komut!\n");
        }
    }

    return 0;
}

int isNumber(char *n) // gönderilen bir değerin sayı olup olmadığını kontrol eder
{
    int i = strlen(n);
    int isnum = (i > 0);
    while (i-- && isnum)
    {
        if (!(n[i] >= '0' && n[i] <= '9'))
        {
            isnum = 0;
        }
    }
    return isnum;
}