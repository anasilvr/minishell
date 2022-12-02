#include "../../include/minishell.h"

static int	check_syntax(t_tok **list)
{
	t_tok	*node;
	t_tok	*tail;

	node = *list;
	tail = get_lasttok(node);
	if (is_set(*node->token, "|") || is_set(*tail->token, METACHAR))
		return (1);
	while (node)
	{
		if (node->type >= 2 && node->type <= 6)
			if (node->next->type != 1)
				return (1);
		node = node->next;
	}
	return (0);
}

int	id_tokens(t_tok **list, t_data *data)
{
	t_tok	*node;

	node = *list;
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
	if (check_syntax(list))
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

/*
bash-3.2$ echo $"USER"
	USER // strip $, strip quotes, print literal str (ECHO FUNCTION)
bash-3.2$ echo "$USER"
	anarodri // strip quotes, expands envvar
bash-3.2$ echo $$"USER"
	4619USER // prints PID and literal str -> in our case, prints $$USER cause PID won't be implemented.
bash-3.2$ echo $"$USER"
	anarodri // strip $ and quotes, expands envvar even if it is between quotes. (data.expand = true!)
bash-3.2$ echo $"ana"
	ana // strip $ and quotes, prints literal.
bash-3.2$ echo "$ana"
		// envvar doesn't exist, prints a newline.
bash-3.2$ echo $ LUIZA $"ROD" $"$USER"
	$ LUIZA ROD anarodri // prints literal $ LUIZA, strips $ and quotes, prints literal ROD, strips $ and strips quotes, expand $USER
bash-3.2$ echo $?$USER
	0anarodri // exit code and expands envvar
*/
static void	check_hidden_dollars(t_tok *token)
{
	int		len;

	if (!token->token)
		return ;
	len = length_til_match(token->token, token->token[0]);
	while (len)
	{
		if (token->token[len] == '$')
		{
			token->type = D_EXPAND;
			return ;
		}
		len--;
	}
	token->type = WORD;
}

static void	check_if_return(t_tok *token)
{
	int	len;

	if (!token->token)
		return ;
	len = ft_strlen(token->token);
	if (token->token[len - 1] == '?' && !(len % 2))
	{
		token->type = D_RETURN;
		return ;
	}
	token->type = D_LITERAL;
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
				node->type = D_LITERAL;
			if (ft_strlen(node->token) >= 2)
			{
				if (is_set(node->token[1], QUOTES))
					check_hidden_dollars(node);
				else if (!ft_isalpha(node->token[1]))
					check_if_return(node);
				else
				node->type = D_EXPAND;
			}
		}
		node = node->next;
	}
	return ;
}
