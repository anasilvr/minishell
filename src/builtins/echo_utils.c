#include "../../include/minishell.h"

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
