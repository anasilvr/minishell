/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:55:57 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/21 14:38:33 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				if (node->next->next == NULL && node->next->next->type != WORD)
					return (1);
		node = node->next;
	}
	return (0);
}

static char	*clean_empty_quotes(char *input)
{
	char	*tmp;
	int		i;
	char	q;

	tmp = ft_xcalloc(1, 1);
	i = -1;
	q = '\0';
	while (input[++i])
	{
		while (is_set(input[i], QUOTES))
		{
			q = input[i];
			if (input [i + 1] && input [i + 1] == q)
				i += 2 ;
			else
				break ;
		}
		if (!input[i])
			break ;
		tmp = charjoinfree(tmp, input[i]);
	}
	tmp = charjoinfree(tmp, '\0');
	xfree(input);
	return (tmp);
}

int	lexer(t_data *data, char *input)
{
	if (!data || !input || !*input)
		return (0);
	data->syntax_err = valid_quotation(data);
	if (data->syntax_err != 0)
		return (128);
	data->input = clean_empty_quotes(input);
	data->token = tokenize(data, data->input);
	if (!data->token)
		return (129);
	data->syntax_err = id_tokens(&data->token, data);
	if (data->syntax_err)
		return (258);
	verify_dollartype(&data->token);
	treat_line(data);
	if (data->token == NULL)
		return (18);
	return (0);
}
