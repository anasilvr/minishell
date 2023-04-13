/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:04:53 by jgagnon           #+#    #+#             */
/*   Updated: 2023/04/12 16:30:31 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_env_var(char **env, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		while (env[i][j] == var[j] && var[j] != '\0')
			j++;
		if (var[j] == '\0' && env[i][j] == '=')
			break ;
		j = 0;
		i++;
	}
	if (env[i] == NULL)
		return (-1);
	return (i);
}

void	unset_handler(char **instruct, t_data *data)
{
	int	i;
	int	r_check;

	i = 0;
	if ((ft_strncmp(instruct[i], "unset", 6) == 0) && instruct[i + 1] != NULL)
	{
		data->cmd_lst->is_builtin = true;
		while (instruct[++i] != NULL)
		{
			r_check = check_env_var(data->envp_cp, instruct[i]);
			if (r_check >= 0)
			{
				data->envp_cp[r_check] = xfree(data->envp_cp[r_check]);
				data->envp_cp[r_check] = ft_strdup(instruct[i]);
			}
		}
	}
}
