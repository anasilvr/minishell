#include "../../include/minishell.h"

int	id_tokens(t_tok **list)
{
	t_tok	*node;

	node = *list;
	while (node)
	{
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

void	verify_dollartype(t_tok **list)
{
	t_tok	*node;

	node = *list;
	while (node)
	{
		if (node->type == DOLLAR)
		{
			if (ft_strlen (node->token) == 1)
				node->type = WORD;
			if (ft_strlen(node->token) >= 2)
			{
				if (node->token[1] == '?')
					node->type = D_RETURN;
				else if (node->token[1] == '$')
					node->type = D_PID;
				else if (is_set(node->token[1], QUOTES) \
					|| is_set(node->token[1], WHITESPACE) \
					|| !ft_isalpha(node->token[1]))
					node->type = WORD;
			}
		}
		node = node->next;
	}
	return ;
}