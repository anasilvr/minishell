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

void	delnode_toklist(t_tok *token_lst)
{
	xfree(token_lst->token);
	xfree(token_lst);
}

t_tok	*delmidnode_toklist(t_tok *node_to_remove)
{
	t_tok	*next_node_cpy;
	t_tok	*prev_node_cpy;
	t_tok	*r_adjacent_node;

	next_node_cpy = node_to_remove->next;
	prev_node_cpy = node_to_remove->prev;
	delnode_toklist(node_to_remove);

	if (next_node_cpy != NULL)
	{
		r_adjacent_node = next_node_cpy;
		r_adjacent_node->prev = prev_node_cpy;
		if (prev_node_cpy != NULL)
			prev_node_cpy->next = next_node_cpy;

	}
	else if (prev_node_cpy != NULL)
	{
		r_adjacent_node = prev_node_cpy;
		r_adjacent_node->next = next_node_cpy;

	}
	else
		r_adjacent_node = NULL;
	return (r_adjacent_node);
}

// void	delmidnode_toklist(t_tok *token_lst)
// {
// 	t_tok	*next_node_ptr;

// 	if (token_lst->next != NULL)
// 		next_node_ptr = token_lst->next;
// 	else if (token_lst->prev != NULL)
// 		next_node_ptr = token_lst->prev;
// 	else
// 		next_node_ptr = NULL;

// 	if (token_lst->next != NULL)
// 		token_lst->next->prev = token_lst->prev;
// 	else // Si il n y a pas de node apres
// 		token_lst->prev->next = NULL;

// 	if (token_lst->prev != NULL)
// 		token_lst->prev->next = token_lst->next;
// 	else // Si il n y a pas de node avant
// 		token_lst->next->prev = NULL;

// 	delnode_toklist(token_lst);
// }

void	free_toklist(t_tok *lst)
{
	t_tok	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		delnode_toklist(lst);
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
		tmp = lst->next;
		xfree(lst->cmdline);
		free_tab(lst->args);
		xfree(lst->hd_delimiter);
		xfree(lst);
		lst = tmp;
	}
}

void	reset(t_data *data)
{
	xfree(data->input);
	data->input = NULL;
	data->nb_cmds = 0;
	data->nb_pipes = 0;
	if (data->token)
	{
		free_toklist(data->token);
		data->token = ft_xcalloc(1, sizeof(t_tok));
	}
	if (data->cmd_lst)
	{
		free_cmdlist(data->cmd_lst);
		data->cmd_lst = ft_xcalloc(1, sizeof(t_cmd));
	}
}
