#include <stdio.h>        //genutzte Bibliotheken
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits.h>

char *stringToBinary(char ch)
{
    char *binary = malloc(9); // zuweisung für 8 Bits und Abschlusszeichen
    if (binary == NULL)
    {
        perror("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    binary[0] = '\0';

    for (int j = 7; j >= 0; --j)
    {
        if (ch & (1 << j))
        {
            strcat(binary, "1");
        }
        else
        {
            strcat(binary, "0");
        }
    }
    return binary;
}

int main()
{
    char *file_name = malloc(256); // speicherzuweisung für den Dateinamen
    if (file_name == NULL)
    {
        perror("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    char *type = malloc(4); // speicherzuweisung für "hex" oder "bin"
    if (type == NULL)
    {
        perror("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    FILE *fp;

    system("clear"); // macht das Terminal leer

    printf("Enter the name of the file you wish to see\n");
    fgets(file_name, 255, stdin); // 255 nutzen um Input zu lesen

    file_name[strlen(file_name) - 1] = '\0';

    printf("In which format do you want to view the file? [bin|hex|out]\n");
    printf("bin: binary, hex: hexadecimal, out: normal output as string\n");
    scanf("%3s", type); // eingabelimit um buffer overflow zu verhindern

    fp = fopen(file_name, "rb"); // im binär Modus lesen

    if (fp == NULL) // Error bzw Fehler überprüfung 
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    system("clear"); // macht das Terminal leer

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // terminal größe bestimmen um den Text richtig anzuzeigen

    int j;
    for (j = 1; j < (w.ws_col + 1); ++j)
    {
        printf("%s", "█");
    }
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("The contents of %s %s file in %s are :\n", cwd, file_name, type);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }
    for (j = 1; j < (w.ws_col + 1); ++j)
    {
        printf("%s", "█");
    }

    int i;
    int k;
    int ch;
    int page;
    k = 0;
    page = 1;

    while ((ch = fgetc(fp)) != EOF)
    {
        k++;

        if (k < page * 16) // Seitenfunktion, sonst wird das irgendwann unlesbar
        {

            if (strcmp(type, "bin") == 0)
            {
                char *binary = stringToBinary(ch);
                printf("%s", binary);
                free(binary); // speicher aus stringToBinary wieder freigeben
            }
            if (strcmp(type, "hex") == 0)
            {
                printf("%02X ", ch); // whitespace ist für die richtige ausgabe von hex wichtig
                if (!(++i % 16))
                {
                    putc('\n', stdout);
                }
            }
            if (strcmp(type, "out") == 0)
            {
                // string für Zeichenfolge
                char str[2];
                str[0] = ch;
                // string endet immer mit Abschlusszeichen
                str[1] = '\0';
                printf("%s", str);
            }
        }
    }

    fclose(fp);
    putc('\n', stdout);

    // Speicher wieder freigeben 
    free(file_name);
    free(type);

    return 0;
}
