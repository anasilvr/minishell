#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
int isDir(const char* fileName)
{
    struct stat path;

    stat(fileName, &path);

    return S_ISREG(path.st_mode);
}

int main()
{
    char fileName[16];
    int ret = 0;

    printf("Enter filename: ");
    scanf("%s", fileName);

    ret = isDir(fileName);

    if (ret == 0)
        printf("Given file is a directory\n");
    else
        printf("Given file is not a directory\n");

    return 0;
}