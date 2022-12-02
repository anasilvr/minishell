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

void echo_handler(char **instruct, t_data *data, bool exp)
{
    int i;

    i = -1;
    if (ft_cmp_builtin(instruct[++i], "echo", 4) == 0 && instruct[i + 1] != NULL)
    {
        printf("Il y a %d variable a expand\n", exp);
        if (check_n(instruct[++i]) == 1)
        {
            while (instruct[i] != NULL)
            {
                ft_echo(instruct, data->envp_cp, i, exp);
                i++;
            }
            write(1, "\n", 1);
        }
        else if (check_n(instruct[i]) == 0)
        {
            while (instruct[++i] != NULL)
                ft_echo(instruct, data->envp_cp, i, exp);
        }
        free_tab(instruct);
    }
}

void ft_echo(char **arg, char **env, int i, bool exp)
{
    int     j;
    int     k;
    char    c;

    j = -1;
    k = check_echo_var(arg[i], env);
    if (k >= 0 && exp == 1)
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

void    ft_echo2(char *cmd, char **env, int i)
{
    int j;
    int k;
    char *val;

    j = -1;
    val = NULL;
    while (cmd[++j] != '\0')
    {
        k = 1;
        if (cmd[j] == '\'')
        {
            while (cmd[++j] != '\'' && cmd[j] != '\0')
                write(1, &cmd[j], 1);
        }
        else if (cmd[j] == '"')
        {
            k = 1;
            while (cmd[++j] != '"' && cmd[j] != '\0')
            {
                if (cmd[j] == '$')
                {
                    while (cmd[j + k] != '"' && ft_isspace(cmd[j + k]) != 1 && 
                        cmd[j + k] != '\0')
                            k++;
                    val = ft_strncpy()
                }
                else if (cmd[j] != '$')
                    write(1, &cmd[j], 1);
            }
        }
    }
}