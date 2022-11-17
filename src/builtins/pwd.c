#include "../../include/minishell.h"

void    pwd_handler(char **instruct)
{
    int     i;
    int     j;
    char    *pwd;

    i = 0;
    pwd = NULL;
    if (ft_cmp_builtin(instruct[i], "pwd", 3) == 0)
    {
        j = -1;
        pwd = getcwd(pwd, ft_free_strlen(getcwd(NULL, 0)));
        while (pwd[++j] != '\0')
            write(1 , &pwd[j], 1);
        write(1, "\n", 1);
        xfree(pwd);
    }
}
