#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int control; // arguman sayısına göre programın çalışma yani tekrar sayısını öğreniriz
    if (argc == 6)
    {
        control = atoi(argv[2]);
    }
    else
    {
        control = 1;
    }

    while (control > 0)
    {
        // pid ve ppid değerleri
        int p_id = getpid();
        int pp_id = getppid();

        size_t m = 10;
        char *data = malloc(sizeof(char) * m);
        // kullanıcıdan input alınır
        printf("Enter: ");
        getline(&data, &m, stdin);

        // time bilgileri
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        FILE *file;
        file = fopen(argv[argc - 1], "a"); // yazma işlemi yapabilmek için dosya açılır

        char *asc = asctime(timeinfo); // timeinfo sonunda \n olduğundan dolayı komutu tek satıra indirebilmek için sonundaki \n kaldırılır
        for (int i = 0;; i++)
        {
            if (asc[i] == '\n')
            {
                asc[i] = '\0';
                break;
            }
        }

        if (file != NULL) // eğer file varsa
        {
            // değerler dosyaya yazılır
            fprintf(file, "%s\n", data);
            fprintf(file, "System time: %s / pid: %d / ppid: %d\n", asc, p_id, pp_id);
            fputs("\n", file);
            fclose(file);
        }
        // değerler terminale yazdırılır
        printf("%s\n", data);
        printf("System time: %s / pid: %d / ppid: %d\n", asc, p_id, pp_id);
        free(data);
        control--;
    }

    return 0;
}