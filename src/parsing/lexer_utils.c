#include "../../include/minishell.h"

void	skip_whitespaces(char **str)
{
	if (!str || !*str)
		return ;
	while (**str && is_set(**str, WHITESPACE))
		*str += 1;
	return ;
}

int		is_set(char s, char *set)
{
	int	i;

	if (!s || !set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

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

void	print_toklist(t_tok **list)
{
	t_tok	*node;
	int		i;

	node = *list;
	i = 0;

	while (node)
	{
		if (!node)
			return ;
		printf("token[%d] = %s / type = %u\n", i, node->token, node->type);
		node = node->next;
		i++;
	}
}