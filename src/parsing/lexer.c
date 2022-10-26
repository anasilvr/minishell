#include "../../include/minishell.h"

int	lexer(t_data *data, char *input)
{
	if (!data)
		return (EXIT_FAILURE);
	if (!input || !*input)
		return (EXIT_SUCCESS);
	valid_quotation(data);
	if (data->syntax_err == true)
		return (EXIT_FAILURE);
	data->token = tokenize(data, input);
//	id_tokens(&data->token);
	print_toklist(&data->token);
	return (0);
}
//do i strip quotes BEFORE tokenizing or after?
t_tok	*tokenize(t_data *data, char *str)
{
	t_tok	*lst;

	lst = NULL;
	skip_whitespaces(&str);
	while (*str)
	{
		data->token->toksize = tok_len(str, ft_strlen(str));
		addback_toklist(&lst, new_toklist(ft_substr(str, 0, data->token->toksize)));
		str += data->token->toksize;
		skip_whitespaces(&str);
	}
	return(lst);
}

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

void	valid_quotation(t_data *data)
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
		data->syntax_err = true;
	else
		data->syntax_err = false;
}
