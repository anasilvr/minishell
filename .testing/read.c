#include <fcntl.h>
#include <stdio.h>
#include "../include/libft/libft.h"

char    *read_user_entry()
{
    char    *line;
    char    buf[100000];
    int     read_len = 100000;
    int     read_ret;

    read_ret = read(0, &buf, read_len);
    line = ft_strdup(buf);
    return (line);
}

int main(void)
{
    printf("%s\n", read_user_entry());
    printf("The end\n");
}