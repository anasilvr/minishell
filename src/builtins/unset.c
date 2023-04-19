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

static char	**env_cpy(char **env, int line)
{
	char	**r_env;
	int		i;
	int		j;

	r_env = malloc(sizeof(char *) * check_env_var(env, NULL));
	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (i != line)
		{
			r_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	r_env[j] = NULL;
	return (r_env);
}

int	check_env_var(char **env, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (var == NULL)
	{
		while (env[i] != NULL)
			i++;
		return (i);
	}
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
	int		i;
	int		r_check;
	char	**r_env;
	int		j;

	i = 0;
	if ((ft_strncmp(instruct[i], "unset", 6) == 0) && instruct[i + 1] != NULL)
	{
		data->cmd_lst->is_builtin = true;
		while (instruct[++i] != NULL)
		{
			r_check = check_env_var(data->envp_cp, instruct[i]);
			if (r_check >= 0)
			{
				j = -1;
				r_env = env_cpy(data->envp_cp, r_check);
				while (data->envp_cp[++j] != NULL)
					data->envp_cp[j] = xfree(data->envp_cp[j]);
				data->envp_cp = xfree(data->envp_cp);
				data->envp_cp = r_env;
			}
		}
	}
}
