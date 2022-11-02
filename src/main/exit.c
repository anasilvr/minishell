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

void	reset(t_data *data)
{
	int	i;

	i = 0;
	xfree(data->input);
	free_toklist(&data->token);
}

void	free_toklist(t_tok **lst)
{
	t_tok	*tmp;
	t_tok	*current;

	if (!lst && !*lst)
		return ;
	current = *lst;
	while (current)
	{
		tmp = current->prev;
		tmp->next = current->next;
		(tmp->next)->prev = tmp;
		del_token(current);
		*lst = tmp;
	}
	*lst = NULL;
}

void	del_token(t_tok *lst)
{
	if (!lst)
		return ;
	xfree(lst->token);
	xfree(lst);
}
