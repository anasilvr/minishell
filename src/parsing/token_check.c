#include "../../include/minishell.h"

int	id_tokens(t_tok **list)
{
	t_tok	*node;

	node = *list;
	while (node)
	{
		if (is_redir(node->token))
			node->type = is_redir(node->token);
		if (node->type == NOTSET)
			node->type = is_valid(node->token);
		if (node->type == INVALID)
			return (258);
		node = node->next;
	}
	return (0);
}

int	is_redir(char *tok)
{
	if (!ft_strcmp(tok, "|") && ft_strlen(tok) == 1)
		return (PIPE);
	else if (!ft_strcmp(tok, "<<") && ft_strlen(tok) == 2)
		return (HEREDOC);
	else if (!ft_strcmp(tok, ">") && ft_strlen(tok) == 1)
		return (REDIR_OUT);
	else if (!ft_strcmp(tok, "<") && ft_strlen(tok) == 1)
		return (REDIR_IN);
	else if (!ft_strcmp(tok, ">>") && ft_strlen(tok) == 2)
		return (APPEND);
	else
		return (0);
}

int	is_valid(char *tok)
{
	if (is_set(*tok, METACHAR))
		return (INVALID);
	else if (is_set(*tok, "$"))
		return (DOLLAR);
	else
		return (WORD);
}
