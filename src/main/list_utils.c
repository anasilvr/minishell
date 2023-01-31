#include "../../include/minishell.h"

t_tok	*new_toklist(char *tok)
{
	t_tok	*new;

	new = ft_xcalloc(1, sizeof(t_tok));
	new->prev = NULL;
	new->token = tok;
	new->next = NULL;
	return (new);
}

void	addback_toklist(t_tok **toklist, t_tok *new)
{
	t_tok	*last;

	if (!new)
		return ;
	if (*toklist)
	{
		last = get_lasttok(*toklist);
		new->prev = last;
		last->next = new;
		new->next = NULL;
	}
	else
		*toklist = new;
}

t_tok	*get_lasttok(t_tok *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}
