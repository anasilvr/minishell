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

t_tok *delnode_toklist(t_tok *token_lst)
{
	if (token_lst)
	{
		free(token_lst->token);
        token_lst->next = NULL;
        token_lst->prev = NULL;
		free(token_lst);
        token_lst = NULL;
	}
    return (token_lst);
}

t_tok *node_cpy(t_tok *cpy)
{
	t_tok *r_tok;

	r_tok = NULL;
	if (cpy == NULL)
		return (r_tok);
	r_tok = malloc(sizeof(t_tok));
	r_tok->token = ft_strdup(cpy->token);
	r_tok->type = cpy->type;
	r_tok->toksize = cpy->toksize;
	r_tok->prev = cpy->prev;
	r_tok->next = cpy->next;
	return (r_tok);

}

t_tok	*delmidnode_toklist(t_tok *node_to_remove)
{
	t_tok	*next_node_cpy;
	t_tok	*prev_node_cpy;
	t_tok	*r_adjacent_node;

	next_node_cpy = node_to_remove->next;
	prev_node_cpy = node_to_remove->prev;
	if (next_node_cpy != NULL)
	{
		r_adjacent_node = next_node_cpy;
		r_adjacent_node->prev = prev_node_cpy;
		if (prev_node_cpy != NULL)
			prev_node_cpy->next = r_adjacent_node;

	}
	else if (prev_node_cpy != NULL)
	{
		r_adjacent_node = prev_node_cpy;
		r_adjacent_node->next = next_node_cpy;

	}
	else
		r_adjacent_node = NULL;
	node_to_remove = delnode_toklist(node_to_remove);
	return (r_adjacent_node);
}