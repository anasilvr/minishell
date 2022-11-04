#include "../../include/minishell.h"

void	skip_whitespaces(char **str)
{
	if (!str || !*str)
		return ;
	while (**str && is_set(**str, WHITESPACE))
		*str += 1;
	return ;
}

int	is_set(char s, char *set)
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
		printf("token[%d] = %s \t\t type = %u\n", i, node->token, node->type);
		node = node->next;
		i++;
	}
}
