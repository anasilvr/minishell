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

static char	**cpy_unset(char **env, int line)
{
	int		i;
	int		j;
	int		k;
	char	**r_env;

	i = -1;
	k = 0;
	while (env[++i] != NULL)
		;
	r_env = malloc(sizeof(char *) * i);
	i = 0;
	while (env[i] != NULL)
	{
		j = -1;
		if (i != line)
			r_env[k] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		while (env[i][++j] != '\0' && i != line)
			r_env[k][j] = env[i][j];
		if (i != line)
			k++;
		i++;
	}
	r_env[k] = NULL;
	free_tab(env);
	return (r_env);
}

void	unset_handler(char **instruct, t_data *data)
{
	int	i;
	int	r_check;

	i = 0;
	if (ft_cmp_builtin(instruct[i], "unset", 5) == 0
		&& instruct[i + 1] != NULL)
	{
		data->cmd_lst->is_builtin = true;
		while (instruct[++i] != NULL)
		{
			r_check = check_env_var(data->envp_cp, instruct[i]);
			if (r_check >= 0)
				data->envp_cp = cpy_unset(data->envp_cp, r_check);
		}
		if (data->fork_pid == 0)
		{
			clean_exit(data);
			exit(g_status);
		}
	}
}
