/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:48:45 by jgagnon           #+#    #+#             */
/*   Updated: 2023/04/12 10:12:30 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(char **cmd, char **env, int i)
{
	int		j;

	j = -1;
	while (cmd[i] != NULL)
	{
		if (ft_strlen(cmd[i]) > 0)
		{
			if (ft_strncmp(cmd[i], "~", ft_strlen(cmd[i])) == 0)
			{
				print_env_var(env, "HOME");
				return ;
			}
			else if (ft_strncmp(cmd[i], "~/", 2) == 0)
			{
				print_env_var(env, "HOME");
				j += 2;
			}
			while (cmd[i][++j] != '\0')
				write(1, &cmd[i][j], 1);
		}
		j = -1;
		i++;
		if (cmd[i] != NULL && ft_strlen(cmd[i - 1]) > 0)
			write(1, " ", 1);
	}
}

void	echo_handler(char **instruct, t_data *data)
{
	int	i;

	i = -1;
	if (ft_strncmp(instruct[++i], "echo", 5) == 0)
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
			while (instruct[i] != NULL && check_n(instruct[i]) == 0)
				i++;
			ft_echo(instruct, data->envp_cp, i);
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
