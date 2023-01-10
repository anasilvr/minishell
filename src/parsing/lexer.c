#include "../../include/minishell.h"

static void	find_match(t_data *data, int *i, bool *trigger, char *quote)
{
	while (data->input[*i])
	{
		if (data->input[*i] == *quote)
		{
			*trigger = false;
			*quote = 0;
			break ;
		}
	*i += 1;
	}
}

static int	valid_quotation(t_data *data)
{
	int		i;
	bool	trigger;
	char	quote;

	i = -1;
	trigger = false;
	quote = 0;
	while (data->input[++i])
	{
		if (data->input[i] == '\'' || data->input[i] == '\"')
		{
			quote = data->input[i];
			trigger = true;
			i++;
			find_match(data, &i, &trigger, &quote);
			if (!data->input[i])
				break ;
		}
	}
	if (trigger == true)
		return (1);
	else
		return (0);
}

int	check_syntax(t_tok **list)
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
			if (node->next->type != 1 && \
			!(node->next->type >= 7 && node->next->type <= 10))
				return (1);
		node = node->next;
	}
	return (0);
}

//$? = 1 catchall for g eneral errors and unclosed quotes
//$? = 258 for syntax errors
void	lexer(t_data *data, char *input)
{
	if (!data)
		return ;
	if (!input || !*input)
		return ;
	g_status = valid_quotation(data);
	if (g_status)
	{
		data->syntax_err = 90;
		return ;
	}
	data->token = tokenize(data, input);
	if (!data->token)
		return ;
	g_status = id_tokens(&data->token, data);
	if (g_status)
		return ;
	verify_dollartype(&data->token);
	return ;
}

t_tok	*tokenize(t_data *data, char *str)
{
	t_tok	*lst;

	lst = NULL;
	skip_whitespaces(&str);
	while (*str)
	{
		data->token->toksize = tok_len(str, ft_strlen(str));
		addback_toklist(&lst, \
			new_toklist(ft_substr(str, 0, data->token->toksize)));
		str += data->token->toksize;
		skip_whitespaces(&str);
	}
	free_toklist(data->token);
	return (lst);
}
