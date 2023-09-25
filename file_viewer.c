#include <stdio.h>        //used libraries
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits.h>

char *stringToBinary(char ch)
{
    char *binary = malloc(9); // allocate space for 8 bits and null terminator
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
    char *file_name = malloc(256); // allocate memory for the file name
    if (file_name == NULL)
    {
        perror("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    char *type = malloc(4); // allocate memory for "hex" or "bin"
    if (type == NULL)
    {
        perror("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    FILE *fp;

    system("clear"); // clear the terminal

    printf("Enter the name of the file you wish to see\n");
    fgets(file_name, 255, stdin); // use 255 to read input

    file_name[strlen(file_name) - 1] = '\0';

    printf("In which format do you want to view the file? [bin|hex|out]\n");
    printf("bin: binary, hex: hexadecimal, out: normal output as string\n");
    scanf("%3s", type); // limit the input to 3 characters to prevent buffer overflow

    fp = fopen(file_name, "rb"); // read binary mode

    if (fp == NULL) // error checking
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    system("clear"); // clear the terminal

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // get terminal size

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

        if (k < page * 16) // pagination
        {

            if (strcmp(type, "bin") == 0)
            {
                char *binary = stringToBinary(ch);
                printf("%s", binary);
                free(binary); // free the memory allocated in stringToBinary
            }
            if (strcmp(type, "hex") == 0)
            {
                printf("%02X ", ch); // whitespace is important for correct hex output
                if (!(++i % 16))
                {
                    putc('\n', stdout);
                }
            }
            if (strcmp(type, "out") == 0)
            {
                // string is a character array
                char str[2];
                str[0] = ch;
                // string always ends with a null character
                str[1] = '\0';
                printf("%s", str);
            }
        }
    }

    fclose(fp);
    putc('\n', stdout);

    // free allocated memory
    free(file_name);
    free(type);

    return 0;
}
