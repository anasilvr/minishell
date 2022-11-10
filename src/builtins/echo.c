#include "../../include/minishell.h"

int check_echo_var(char *instruct, char **env)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (instruct[i] == '$')
    {   
        i++;
        while (env[j] != NULL)
        {
            if (ft_cmp_env(env[j], &instruct[i], (ft_strlen(&instruct[i]))) == 0)
                break ;
            j++;
        }
    }
    else if (instruct[i] != '$')
        return (-1);
    if (env[j] == NULL)
        return (-2);
    return (j);
}

void echo_handler(char **instruct, char **env)
{
    int i;

    i = -1;
    if (ft_cmp_builtin(instruct[++i], "echo", 4) == 0)
    {
        if (check_n(instruct[++i]) == 1)
        {
            while (instruct[i] != NULL)
            {
                ft_echo(instruct, env, i);
                i++;
            }
            write(1, "\n", 1);
        }
        else if (check_n(instruct[i]) == 0)
        {
            while (instruct[++i] != NULL)
                ft_echo(instruct, env, i);
        }
    }
}

void ft_echo(char **arg, char **env, int i)
{
    int     j;
    int     k;
    char    c;

    j = -1;
    k = check_echo_var(arg[i], env);
    if (k >= 0)
    {
        while (env[k][++j] != '=')
            ;
        while (env[k][++j] != '\0')
        {
            c = env[k][j];
            write(1, &c, 1);
        }
    }
    if (k == -1)
    {
        while (arg[i][++j] != '\0')
        {
            c = arg[i][j];
            write(1, &c, 1);
        }

    }
    if (arg[i + 1] != NULL && k >= -1)
        write(1, " ", 1);
}

int check_n(char *instruct)
{
    int i;

    i = -1;
    if (!instruct)
        return(0);
    if (instruct[++i] == '-')
    {
        while (instruct[++i] == 'n')
            ;
        if (instruct[i] == '\0')
            return (0);
    }
    return (1);
}