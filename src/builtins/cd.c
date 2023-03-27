/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgagnon <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:47:01 by jgagnon           #+#    #+#             */
/*   Updated: 2023/03/27 09:47:02 by jgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	update_pwd(char **env)
{
	int		i;
	int		j;
	char	*n_path;

	n_path = NULL;
	i = check_env_var(env, "PWD");
	if (i >= 0)
	{
		j = -1;
		xfree(env[i]);
		n_path = ft_strjoin_free2("PWD=", getcwd(n_path, \
			ft_free_strlen(getcwd(NULL, 0)) + 1));
		env[i] = malloc(sizeof(char) * (ft_strlen(n_path) + 1));
		while (n_path[++j] != '\0')
			env[i][j] = n_path[j];
		env[i][j] = '\0';
	}
	xfree(n_path);
}

static	void	update_oldpwd(char **env)
{
	char	*n_path;
	int		i;
	int		j;

	n_path = NULL;
	i = check_env_var(env, "OLDPWD");
	if (i >= 0)
	{
		j = -1;
		xfree(env[i]);
		n_path = ft_strjoin_free2("OLDPWD=", getcwd(n_path, \
			ft_free_strlen(getcwd(NULL, 0)) + 1));
		env[i] = malloc(sizeof(char) * (ft_strlen(n_path) + 1));
		while (n_path[++j] != '\0')
			env[i][j] = n_path[j];
		env[i][j] = '\0';
	}
	xfree(n_path);
}

void	cd_handler(char **instruct, t_data *data)
{
	int	i;

	i = 0;
	if (ft_cmp_builtin(instruct[i], "cd", 2) == 0)
	{
		data->cmd_lst->is_builtin = true;
		update_oldpwd(data->envp_cp);
		if (instruct[i + 1] != NULL && chdir(instruct[++i]) == 0)
			update_pwd(data->envp_cp);
		else if (instruct[i] == NULL || ft_strcmp(instruct[i], "~") == 0)
		{
			chdir(getenv("HOME"));
			update_pwd(data->envp_cp);
		}
		if (data->fork_pid == 0)
		{
			clean_exit(data);
			exit(g_status);
		}
	}
}
