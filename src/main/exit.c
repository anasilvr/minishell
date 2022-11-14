#include "../../include/minishell.h"

void	clean_exit(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp_cp[i++])
		xfree(data->envp_cp[i]);
	xfree(data->envp_cp);
	i = 0;
	while (data->path[i++])
		xfree(data->path[i]);
	xfree(data->path);
	xfree(data->input);
/*	xfree(data->cmd_list->ref);
	xfree(data->cmd_list->cmd);
	i = 0;
	while (data->cmd_list->cmd_args[i++])
		xfree(data->cmd_list->cmd_args[i]);
	xfree(data->cmd_list->cmd_args);
	xfree(data->cmd_list);*/
	xfree(data);
}
void	free_cmdlist(t_cmd *lst)
{
	t_cmd	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		xfree(lst);
		lst = tmp->next;
	}
	lst = NULL;
}

void	reset(t_data *data)
{
	xfree(data->input);
	data->input = NULL;
	data->nb_pipes = 0;
	free_toklist(data->token);
	data->token = ft_xcalloc(sizeof(t_tok));
	free_cmdlist(data->cmd_lst);
	data->cmd_lst = ft_xcalloc(sizeof(t_cmd));
//	data->syntax_err = 0;
}
