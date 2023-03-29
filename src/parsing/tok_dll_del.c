#include "../../include/minishell.h"

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