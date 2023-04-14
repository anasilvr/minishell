/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:55:57 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/13 18:34:21 by anarodri         ###   ########.fr       */
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

int	lexer(t_data *data, char *input)
{
	if (!data || !input || !*input)
		return (0);
	data->syntax_err = valid_quotation(data);
	if (data->syntax_err != 0)
		return (128) ;
	data->token = tokenize(data, data->input);
	if (!data->token)
		return (129);
	data->syntax_err = id_tokens(&data->token, data);
	print_toklist(data->token);
	if (data->syntax_err)
		return (258);
	verify_dollartype(&data->token);
	treat_line(data->token, data->envp_cp, data->exit_code);
	print_toklist(data->token);
	return (0);
}

t_tok   *tokenize(t_data *data, char *str)
{
    t_tok   *lst;
	size_t	len;
	size_t	max;

    lst = NULL;
    len = ft_strlen(str);
	max = 0;
	skip_whitespaces(&str);
    while (*str)
    {
        data->token->toksize = tok_len(str, ft_strlen(str));
        addback_toklist(&lst, \
            new_toklist(ft_substr(str, 0, data->token->toksize)));
		max += data->token->toksize;
		if (max > len)
			str += ft_strlen(str);
		else
        	str += data->token->toksize;
		if (str)
	       	skip_whitespaces(&str);
    }
    free_toklist(data->token);
    return (lst);
}