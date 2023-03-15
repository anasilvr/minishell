#include "../../include/minishell.h"

void	ft_echo(char **cmd, char **env, int i)
{
	int		j;
	
	j = -1;
	while (cmd[i] != NULL)
	{
        if (ft_strcmp(cmd[i], "~") == 0)
        {
            print_env_var(env, "HOME");
            return ;
        }
		while (cmd[i][++j] != '\0')
        	write(1, &cmd[i][j], 1);
		j = -1;
		i++;
		if (cmd[i] != NULL)
			write(1, " ", 1);
	}
}

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
			ft_echo(instruct, data->envp_cp, i);
			write(1, "\n", 1);
		}
		if (instruct[i] != NULL && check_n(instruct[i]) == 0)
		{
			while (check_n(instruct[i]) == 0)
				i++;
			ft_echo(instruct, data->envp_cp, i);
		}
		if (data->fork_pid == 0)
		{
			clean_exit(data);
			exit(g_status);
		}
	}
}

int	check_n(char *instruct)
{
	int	i;

	i = -1;
	if (!instruct)
		return (0);
	if (instruct[++i] == '-')
	{
		while (instruct[++i] == 'n')
			;
		if (instruct[i] == '\0')
			return (0);
	}
	return (1);
}
