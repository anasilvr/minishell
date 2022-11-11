#include "../../include/minishell.h"

int	id_tokens(t_tok **list, t_data *data)
{
	printf("\tStarting to ID tokens...\n");
	t_tok	*node;
	t_tok	*head;
	t_tok	*tail;

	node = *list;
	head = *list;
	tail = get_lasttok(node);
	while (node)
	{
		node->type = is_redir(node->token);
		if (node->type == PIPE)
			data->nb_pipes++;
		if (node->type == NOTSET)
			node->type = is_valid(node->token);
		if (node->type == INVALID)
		{
			data->syntax_err = 258;
			return (258);
		}
		node = node->next;
	}
	if (is_set(*head->token, "|") || is_set(*tail->token, METACHAR))
	{
		data->syntax_err = 258;
		return (258);
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
