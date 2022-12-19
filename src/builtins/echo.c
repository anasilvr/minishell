#include "../../include/minishell.h"

/*static int check_echo_var(char *instruct, char **env)
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
}*/

void	echo_handler(char **instruct, t_data *data)
{
	int	i;

	i = -1;
	if (ft_cmp_builtin(instruct[++i], "echo", 4) == 0)
	{
		data->cmd_lst->is_builtin = true;
		if (instruct[++i] == NULL)
			write(1, "\n", 1);
		else if (check_n(instruct[i]) == 1)
		{
			ft_echo(&data->cmd_lst->cmdline[(ft_strlen(instruct[0]) + 1)],
				data->envp_cp);
			write(1, "\n", 1);
		}
		else if (check_n(instruct[i]) == 0)
			ft_echo(&data->cmd_lst->cmdline[ft_strlen(instruct[0])
				+ ft_strlen(instruct[1]) + 2], data->envp_cp);
		if (data->cmd_lst->fork_pid == 0)
		{
			clean_exit(data);
			exit(g_status);
		}
	}
}

int	check_n(char *instruct)
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

static	int	space_handler(char *str, int i)
{
    int j;

    j = i;
    while (ft_isspace(str[i]) == 0 && str[i] != '\0')
        i++;
    if (str[i] == '\0')
        return (i - 1);
    return (j);
}

static	int	double_quote_handler(char *cmd, char **env, int j)
{
    int     k;
    char    *val;

    k = 0;
    val = NULL;
    if (cmd[j] != '$' && cmd[j] != '"')
        write(1, &cmd[j], 1);
    else if (cmd[j] == '$')
    {
        j++;
        while (cmd[j + k] != '"' && ft_isspace(cmd[j + k]) != 0 && cmd[j + k] != '\0')
            k++;
        val = ft_substr(cmd, j, k);
        print_env_var(env, val);
        j = j + k;
        j = space_handler(cmd, j);
        xfree(val);
        if (cmd[j] != '\0')
            write(1, " ", 1);
    }
    return (j);
}

static	int	quotes_handler(char *cmd, char **env, int j)
{
    if (cmd[j] == '\'' && cmd[j] != '\0')
    {
        while (cmd[++j] != '\'' && cmd[j] != '\0')
        {
            j = space_handler(cmd, j);
            write(1, &cmd[j], 1);
        }
        if (cmd[j] == '\'' && cmd[j] != '\0')
        {
            j++;
            write(1, " ", 1);
        }
    }
    else if (cmd[j] == '"' && cmd[j] != '\0')
    {
        while (cmd[++j] != '"' && cmd[j] != '\0')
        {
            j = double_quote_handler(cmd, env, j);
            if (cmd[j] == '"')
                break ;
        }
    }
    return (j);
}

void	ft_echo(char *cmd, char **env)
{
    int j;
    int k;
    char *val;

    j = -1;
    while (cmd[++j] != '\0')
    {
        val = NULL;
        k = 0;
        if (cmd[j] == '\'' || cmd[j] == '"')
            j = quotes_handler(cmd, env, j);
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

