#include "minishell.h"

int print_directory(char **env)
{
    int     i;
    int     j;
    char    c;

    i = 0;
    j = -1;
    while (env[i] != NULL && ft_cmp_env(env[i], "PWD", 3) != 0)
        i++;
    if (env[i] == NULL)
        {
            write(1, "\n", 1);
            return (0);
        }
    while (env[i][j] != '=')
        j++;
    while (env[i][++j] != '\0')
    {
        c = env[i][j];
        write(1, &c, 1);
    }
    write(1, "\n", 1);
    return (0);
}