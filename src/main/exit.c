#include "../../include/minishell.h"

void	clean_exit(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp_cp[++i])
		xfree(data->envp_cp[i]);
	xfree(data->envp_cp);
	i = -1;
	while (data->path[++i])
		xfree(data->path[i]);
	xfree(data->path);
	xfree(data->pwd);
	xfree(data->input);
	free_toklist(data->token);
	free_cmdlist(data->cmd_lst);
	xfree(data);
}

void	free_toklist(t_tok *lst)
{
	t_tok	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		xfree(lst->token);
		tmp = lst->next;
		xfree(lst);
		lst = tmp;
	}
}

void	free_cmdlist(t_cmd *lst)
{
	t_cmd	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		xfree(lst->cmdline);
		free_tab(lst->args);
		xfree(lst->hd_delimiter);
		tmp = lst->next;
		xfree(lst);
		lst = tmp;
	}
}

void	reset(t_data *data)
{
	xfree(data->input);
	data->input = (char *) NULL;
	data->nb_cmds = 0;
	data->nb_pipes = 0;
	if (data->token)
	{
		free_toklist(data->token);
		data->token = ft_xcalloc(sizeof(t_tok));
	}
	if (data->cmd_lst)
	{
		free_cmdlist(data->cmd_lst);
		data->cmd_lst = ft_xcalloc(sizeof(t_cmd));
	}
}
