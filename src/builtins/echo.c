#include "../../include/minishell.h"

static int check_echo_var(char *instruct, char **env)
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
    (void)exp;
    if (ft_cmp_builtin(instruct[++i], "echo", 4) == 0 && instruct[i + 1] != NULL)
    {
		data->cmd_lst->is_builtin = true;
        if (check_n(instruct[++i]) == 1)
        {
            ft_echo2(&data->cmd_lst->cmdline[(ft_strlen(instruct[0]) + 1)], 
                data->envp_cp);
            write(1, "\n", 1);
        }
        else if (check_n(instruct[i]) == 0)
            ft_echo2(&data->cmd_lst->cmdline[ft_strlen(instruct[0]) + 
                ft_strlen(instruct[1]) + 2], data->envp_cp);
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

static int space_handler(char *str, int i)
{
    int j;

    j = i;
    while (ft_isspace(str[i]) == 0 && str[i] != '\0')
        i++;
    if (str[i] == '\0')
        return (i);
    return (j);
}

void    ft_echo2(char *cmd, char **env)
{
    int j;
    int k;
    char *val;

    j = -1;
    while (cmd[++j] != '\0')
    {
        val = NULL;
        k = 0;
        if (cmd[j] == '\'')
        {
            while (cmd[++j] != '\'' && cmd[j] != '\0')
            {
                j = space_handler(cmd, j);
                write(1, &cmd[j], 1);
            }
            j++;
        }
        else if (cmd[j] == '"')
        {
            while (cmd[++j] != '\0')
            {
                k = 0;
                if (cmd[j] != '$' && cmd[j] != '"')
                    write(1, &cmd[j], 1);
                else if (cmd[j] == '$')
                {
                    j++;
                    while (cmd[j + k] != '"' && ft_isspace(cmd[j + k]) != 0 && 
                        cmd[j + k] != '\0')
                            k++;
                    val = ft_substr(cmd, j, k);
                    print_env_var(env, val);
                    j = j + k;
                    j = space_handler(cmd, j);
                    xfree(val);
                    if (cmd[j] != '\0')
                        write(1, " ", 1);
                }
                if (cmd[j] == '"')
                {
                    j++;
                    break ;
                }
            }
        }      
        else if (cmd[j] == '$' && ft_isspace(cmd[j + 1]) == 1)
        {
            j++;
            while (ft_isspace(cmd[j + k]) != 0 && cmd[j + k] != '\0')
                k++;
            val = ft_substr(cmd, j, k);
            print_env_var(env, val);
            j = j + k;
        }
        else
        {
            j = space_handler(cmd, j);
            write(1, &cmd[j], 1);
        }
    }
}
