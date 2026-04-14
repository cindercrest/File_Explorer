#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
int ListFile();
int ReadFile();
int WriteFile();
int prompt();
int main(int argc, char *argv[])
{
    prompt();
    printf("Thanks for using %s!!\n",argv[0]);
    return 0;
}
int prompt()
{
    char choice[3];
    int ch;
    do
    {
        // prompting
        printf("-----FILE EXPLORER-----\n\n");
        printf("OPTIONS\n\n");
        printf("1.List the files and directories in current folder\n\n");
        printf("2.Read files content\n\n");
        printf("3.write to the file\n\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            ListFile();
            break;
        case 2:
            ReadFile();
            break;
        case 3:
            WriteFile();
            break;
        default:
            printf("Are you sure you typed correct option?\n");
        }
        // clears the "\n"
        while (getchar() != '\n');

        printf("Do you Want to continue ?(y/n)\n");
        fgets(choice, sizeof(choice), stdin);

    } while (*(choice) == 'Y' || *(choice) == 'y');

    return 0;
}

int ListFile()
{
    // Listing all the files in current directory

    // Note : this also showcase the hidden directories like "." , ".."
    struct dirent *entry = NULL;
    DIR *dir = opendir(".");

    if (dir == NULL)
    {
        printf("Error loading file...\n");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        printf("%s\n", entry->d_name);
    }
    // closing directory
    closedir(dir);

    return 0;
}

int ReadFile()
{
    // reading from a specific file from that directory

    char Filename[255];
    char buffer[1024];

    // gettting the name of the file
    printf("What file you want to read ?");
    while (getchar() != '\n')
        ;
    fgets(Filename, sizeof(Filename), stdin);
    Filename[strcspn(Filename, "\n")] = '\0';

    // opening file
    FILE *pfile = fopen(Filename, "r");

    // NULL check
    if (pfile == NULL)
    {
        printf("Error loading file i am so soo sooory!\n");
        return 1;
    }

    // Listing files & directories
    while (fgets(buffer, sizeof(buffer), pfile) != NULL)
    {
        printf("%s", buffer);
    }

    // closing file
    fclose(pfile);

    return 0;
}

int WriteFile()
{
    // writing file

    // getting file name
    char Filename[255];
    printf("What file you want to write?");
    while (getchar() != '\n')
        ;
    fgets(Filename, sizeof(Filename), stdin);

    // terminating the \n character
    Filename[strcspn(Filename, "\n")] = '\0';

    // opening the desired file

    // IN append the previous data will not be lost
    int choice = 0;
    printf("What write operation you want to perform ?\n\n");
    printf("1. write(overwrite previous data)\n\n");
    printf("2. Append (preserves previous history)\n\n");
    scanf("%d", &choice);
    while (getchar() != '\n')
        ;

    FILE *pfile = fopen(Filename, choice == 1 ? "w" : "a");
    if (pfile == NULL)
    {
        printf("Error Loading file...");
        return 1;
    }
    int n = 0;
    char lines[100];
    printf("How Many Lines you want to write?");
    scanf("%d", &n);
    while (getchar() != '\n')
        ;
    for (int i = 0; i < n; i++)
    {
        printf("Line %d: ", i + 1);
        fgets(lines, sizeof(lines), stdin);
        fputs(lines, pfile);
    }
    fclose(pfile);

    return 0;
}
