/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgagnon <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:45:03 by jgagnon           #+#    #+#             */
/*   Updated: 2023/03/27 09:45:04 by jgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cmp_builtin(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;

	i = -1;
	if (n == 0)
		return (-1);
	while (++i <= (n - 1) && (str1[i] != '\0'
			&& str2[i] != '\0') && str1[i] == str2[i])
		;
	if (str2[i] == '\0' && str1[i] == '\0')
		return (0);
	return (-1);
}

void	exit_handler(t_data *data, char **instruct)
{
	if (ft_cmp_builtin(instruct[0], "exit", 4) == 0)
	{
		clean_exit(data);
		exit(g_status);
	}
}

static void	tester_check(char **cmd, t_data *data)
{
	if (ft_strcmp(cmd[0], "test") == 0 && cmd[1] == NULL)
		data->tester = true;
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
	help_handler(cmd->args, data);
	man_yoyo_ma(cmd->args, data);
	tester_check(cmd->args, data);
	return (-1);
}
