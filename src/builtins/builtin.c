#include "../../include/minishell.h"

int	ft_cmp_builtin(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;

	i = -1;
	if (n == 0)
		return (-1);
	while (++i < (n - 1) && ft_tolower(str1[i]) == str2[i]
		&& (str1[i] != '\0' && str2[i] != '\0'))
		;
	if (str2[i + 1] == '\0' && str1[i + 1] == '\0')
		return (0);
	return (-1);
}

void	exit_handler(t_data *data, char **instruct)
{
	// if (data->cmd_lst->io_flag != PIPE
	// 	|| (data->cmd_lst->prev != NULL
	// 		&& data->cmd_lst->prev->io_flag != PIPE))
	// {
	if (ft_cmp_builtin(instruct[0], "exit", 4) == 0)
	{
		clean_exit(data);
		exit(g_status);
	}
	// }
	// else
	// {
	// 	// execve pour l'exécution des pipes
	// }
	// if (data->cmd_lst->fork_pid == 0)
	// {
	// 	clean_exit(data);
	// 	exit(errno);
	// }
}

int	builtins_checker(t_data *data, t_cmd *cmd)
{
	echo_handler(cmd->args, data);
	pwd_handler(cmd->args, data);
	env_handler(cmd->args, data);
	cd_handler(cmd->args, data);
	export_handler(cmd->args, data);
	unset_handler(cmd->args, data);
	exit_handler(data, cmd->args);
	return (-1);
}
