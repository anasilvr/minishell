#include "../../include/minishell.h"

t_data	*get_data(void)
{
	static t_data	*data;

	if (!data)
		data = ft_xcalloc(1, sizeof(t_data));
	return (data);
}

t_data	*init_data(char **envp, t_data *data)
{
	data = get_data();
	data->envp_cp = backup_env(envp);
	data->path = init_path(data);
	data->pwd = NULL;
	data->input = NULL;
	data->token = ft_xcalloc(1, sizeof(t_tok));
	data->cmd_lst = ft_xcalloc(1, sizeof(t_cmd));
	data->nb_cmds = 0;
	data->nb_pipes = 0;
	data->syntax_err = false;
	data->stdio[0] = STDIN_FILENO;
	data->stdio[1] = STDOUT_FILENO;
	data->stdio[2] = STDERR_FILENO;
	data->heredoc = false;
	return (data);
}

char	**init_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp_cp[i] && ft_strnstr(data->envp_cp[i], "PATH=", 5) == 0)
		i++;
	if (!data->envp_cp[i])
		return (NULL);
	else
		data->path = ft_split(data->envp_cp[i], ':');
	return (data->path);
}

char	**backup_env(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	copy = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

//maybe init pwd here?