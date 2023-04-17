/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:16:03 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/17 11:50:10 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// static meta_lenght(char*str)
// {
	
// }

int	tok_len(char *str, int len)
{
	int	i;
	char q;

	if (!str)
		return (0);
	i = 0;
	q = '\0';
	while (i < len && str[i])
	{
		//printf("str: %s\n", &str[i]);
		if (i == 0 && is_set(str[i], METACHAR))
		{
			i += (length_til_set(str, WHITESPACE));
			return (i);
		}
		if ((i == 0 && is_set(str[i], "$")))
		{
			i = (length_for_dollar(str));
		}
		if (str[i] && is_set(str[i], QUOTES))
		{
			i++;
			i += (length_til_match(&str[i], str[i - 1]));
			if (str[i] && is_set(str[i], QUOTES))
				i += tok_len(&str[i], (ft_strlen(str) - i));
		}
		if (str[i] == '\0' || is_set(str[i], WHITESPACE) || is_set(str[i], METACHAR))
			break;
		i++;
	}
	return (i);
}

int	length_for_dollar(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 1;
	if (is_set(str[i], QUOTES))
	{
		i = (2 + length_til_match(&str[i], str[i]));
		return (i);
	}
	else
	{
		while (str[i] && (!is_set(str[i], WHITESPACE) && \
			!is_set(str[i], METACHAR) && str[i] != '?'))
		{
			i++;
		}
		if (str[i] && str[i] == '?')
		{
			i++;
			return (i);
		}
	}
	return (i);
}

int	length_til_set(char *str, char *set)
{
	int	i;

	if (!str || !set)
		return (0);
	i = 1;
	while (str[i] && str[i] != '\0')
	{
		if (is_set(str[i], set) || !is_set(str[i], METACHAR))
			break ;
		i++;
	}
	return (i);
}

int	length_til_match(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 1;
	printf("str: %s | c: %c\n", str, c);
	while (str[i])
	{
		if ((str[i]) == c)
			return (i) ;
		i++;
	}
	return (i);
}

int	id_tokens(t_tok **list, t_data *data)
{
	t_tok	*node;

	node = *list;
	while (node)
	{
		node->type = is_redir(node->token);
		if (node->type == HEREDOC)
			data->heredoc = true;
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
