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

//$? = 1 catchall for g eneral errors and unclosed quotes
//$? = 258 for syntax errors
void	lexer(t_data *data, char *input)
{
//	printf ("\tStarting lexer...\n");
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
//	print_toklist(data->token);
//	printf ("\tQuiting lexer successfully...\n");
	return ;
}

t_tok	*tokenize(t_data *data, char *str)
{
//	printf("\tStarting tokenization...\n");
	t_tok	*lst;
	char *tok;

	lst = NULL;
	tok = NULL;
	skip_whitespaces(&str);
	while (*str)
	{
		data->token->toksize = tok_len(str, ft_strlen(str));
		tok = ft_substr(str, 0, data->token->toksize);
		addback_toklist(&lst, new_toklist(tok));
		str += data->token->toksize;
		skip_whitespaces(&str);
	}
	xfree(tok);
//	printf("\tTokens created...\n");
	return (lst);
}
