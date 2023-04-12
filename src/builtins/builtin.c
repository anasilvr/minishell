/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:45:03 by jgagnon           #+#    #+#             */
/*   Updated: 2023/04/12 10:09:16 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_handler(t_data *data, char **instruct)
{
	if (ft_strncmp(instruct[0], "exit", 5) == 0)
	{
		clean_exit(data);
		exit(g_status);
	}
}

static void	tester_check(char **instruct, t_data *data)
{
	if (ft_strncmp(instruct[0], "test", 5) == 0 && instruct[1] == NULL)
	{
		data->tester = true;
		data->cmd_lst->is_builtin = true;
	}
}

void	builtins_checker(t_data *data, t_cmd *cmd)
{
	echo_handler(cmd->args, data);
	pwd_handler(cmd->args, data);
	env_handler(cmd->args, data);
	cd_handler(cmd->args, data);
	export_handler(cmd->args, data);
	unset_handler(cmd->args, data);
	exit_handler(data, cmd->args);
	help_handler(cmd->args, data);
	man_yoyo_ma(cmd->args, data);
	tester_check(cmd->args, data);
	if (data->cmd_lst->is_builtin == true && data->fork_pid == 0)
	{
		clean_exit(data);
		exit(g_status);
	}
}
