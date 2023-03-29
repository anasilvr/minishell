/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgagnon <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:57 by jgagnon           #+#    #+#             */
/*   Updated: 2023/03/29 09:47:58 by jgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd_handler(char **instruct, t_data *data)
{
	int		i;
	int		j;
	char	*pwd;

	i = 0;
	pwd = NULL;
	if (ft_cmp_builtin(instruct[i], "pwd", 3) == 0)
	{
		data->cmd_lst->is_builtin = true;
		j = -1;
		pwd = getcwd(pwd, ft_free_strlen(getcwd(NULL, 0)));
		while (pwd[++j] != '\0')
			write(1, &pwd[j], 1);
		write(1, "\n", 1);
		xfree(pwd);
		if (data->fork_pid == 0)
		{
			clean_exit(data);
			exit(g_status);
		}
	}
}
