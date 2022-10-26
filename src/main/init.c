#include "../../include/minishell.h"

t_data	*get_data(void)
{
	static t_data	*data;

	if (!data)
		data = (t_data *)ft_xcalloc(sizeof(t_data));
	return (data);
}

t_data	*init_data(char **envp, t_data *data)
{
	g_status = 0;
	data = get_data();
	data->envp_cp = backup_env(envp);
	data->path = init_path(data);
	data->input = NULL;
	data->token = ft_xcalloc(sizeof(t_tok));
	data->token->token = NULL;
	data->token->type = 5;
	data->token->toksize = 0;
	data->nb_toks = 0;
	data->errtok = NULL;
	data->cmd_lst = ft_xcalloc(sizeof(t_cmd));
	data->cmd_lst->cmd = NULL;
	data->cmd_lst->args = NULL;
	data->cmd_lst->input = NULL;
	data->cmd_lst->output = NULL;
	data->cmd_lst->fd_in = STDIN_FILENO;
	data->cmd_lst->fd_out = STDOUT_FILENO;
	data->cmd_lst->err = 0;
	data->cmd_lst->prev = NULL;
	data->cmd_lst->next = NULL;
	data->nb_cmds = 0;
	data->nb_pipes = 0;
	data->heredoc_f = false;
	data->syntax_err = false;
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
