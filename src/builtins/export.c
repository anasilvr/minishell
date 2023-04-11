/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgagnon <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:52:34 by jgagnon           #+#    #+#             */
/*   Updated: 2023/03/27 09:52:36 by jgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**add_var(char **env, char *n_var)
{
	int		i;
	int		j;
	char	**r_env;

	j = -1;
	i = -1;
	r_env = cpy_env(env, 1);
	while (r_env[++i] != NULL)
		;
	xfree(r_env[i]);
	r_env[i] = malloc(sizeof(char) * (ft_strlen(n_var) + 1));
	while (n_var[++j] != '\0')
		r_env[i][j] = n_var[j];
	r_env[i][j] = '\0';
	i++;
	r_env[i] = NULL;
	return (r_env);
}

char	*var_trim(char *n_var)
{
	int		i;
	char	*r_var;

	i = -1;
	while (n_var[++i] != '=')
		;
	r_var = malloc(sizeof(char) * (i) + 1);
	i = -1;
	while (n_var[++i] != '=')
		r_var[i] = n_var[i];
	r_var[i] = '\0';
	xfree(n_var);
	return (r_var);
}

int	env_dup(char *n_var, char **env)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (env[j] != NULL)
	{
		while (n_var[++i] != '=' && n_var[i] == env[j][i])
			;
		if (n_var[i] != '=' && env[j][i] != '=')
		{
			i = -1;
			j++;
		}
		else if (n_var[i] == '=' && env[j][i] == '=')
			return (j);
	}
	return (-1);
}

int	export_pars(char *n_var, char **env)
{
	int	i;

	i = 0;
	while (n_var[i] != '=' && n_var[i] != '\0')
		i++;
	if (n_var[i] == '=')
		return (env_dup(n_var, env));
	return (-2);
}

void	export_handler(char **instruct, t_data *data)
{
	int	i;
	int	index;

	i = 0;
	index = -1;
	if (ft_cmp_builtin(instruct[i], "export", 6) == 0 && instruct[i + 1] == NULL)
	{
		data->cmd_lst->is_builtin = true;
		print_env(data->envp_cp);
	}
	else if (ft_cmp_builtin(instruct[i], "export", 6) == 0)
	{
		data->cmd_lst->is_builtin = true;
		while (instruct[++i] != NULL)
		{
			index = export_pars(instruct[i], data->envp_cp);
			if (index == -1)
				data->envp_cp = add_var(data->envp_cp, instruct[i]);
			else if (index >= 0)
			{
				data->envp_cp[index] = xfree(data->envp_cp[index]);
				data->envp_cp[index] = ft_strdup(instruct[i]);
			}
		}
	}
}
