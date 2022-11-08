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

	i = 0;
	trigger = false;
	quote = 0;
	while (data->input[i])
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
	i++;
	}
	if (trigger == true)
		return (90);
	else
		return (0);
}

int	lexer(t_data *data, char *input)
{
	if (!data)
		return (EXIT_FAILURE); //$? = 1 catchall for general errors
	if (!input || !*input || *input == '\n')
		return (EXIT_SUCCESS);
	g_status = valid_quotation(data);
	if (g_status)
		return (g_status); // $? = 1 for unclosed quotes
	data->token = tokenize(data, input);
	g_status = id_tokens(&data->token);
	if (g_status)
		return (g_status); // $? = 258 for syntax errors
	verify_dollartype(&data->token);
	print_toklist(&data->token);
	return (0);
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
	return (lst);
}
