#include "../../include/minishell.h"

t_tok *new_toklist(char *tok)
{
	t_tok *new;

	new = (t_tok *)ft_xcalloc(sizeof(*new));
	new->prev = NULL;
	new->next = NULL;
	new->token = tok;
//	free(tok);
	return(new);
}

void	addback_toklist(t_tok **toklist, t_tok *new)
{
	t_tok	*current;
	t_tok	*last;

	if (new)
	{
		if (*toklist)
		{
			current = *toklist;
			last = get_lasttok(*toklist);
			new->prev = last;
			last->next = new;
			new->next = NULL;
		}
		else
			*toklist = new;
	}
}

t_tok	*get_lasttok(t_tok *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}
