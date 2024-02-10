#include <stdio.h>
#include <stdlib.h>

const char FILENAME[] = "input.txt";
int main()
{
    writeAndRead();
    return 0;
}

int readFile()
{
    int count = 0;
    FILE *fp = fopen("output.txt", "r");
    if (fp == NULL)
    {
        printf("error in opening file, %s\n", FILENAME);
        exit(1);
    }

    while (fgetc(fp) != EOF)
    {
        char ch = fgetc(fp);
        count++;
    }
    printf("Number of characters in %s is %d\n", FILENAME, count);
    fclose(fp);
    return 0;
}

int writeToFile()
{
    char name[30];
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL)
    {
        printf("error in opening file, %s\n", FILENAME);
        exit(1);
    }
    fgets(name, sizeof(name), stdin);
    fprintf(fp, "%s", name);
    fclose(fp);
    return 0;
}

int writeAndRead()
{
    FILE *fp = fopen("input.txt", "w+");
    char name[30], k[30];
    int age, a;
    if (fp == NULL)
    {
        printf("error in opening file, %s\n", FILENAME);
        exit(1);
    }

    printf("Enter your name \t Age \n:");
    // fgets(name, sizeof(name), stdin);
    scanf("%s %d", name, &age);
    fprintf(fp, "%s %d", name, age);
    rewind(fp);

    printf("Name \t Age \n");
    fscanf(fp, "%s %d", k, &a);
    printf("%s \t %d \n", k, a);
    fclose(fp);
    return 0;
}