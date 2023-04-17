/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:46:08 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/17 12:07:21 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tok	*tokenize(t_data *data, char *str)
{
	t_tok	*lst;
	size_t	len;
	size_t	max;

	lst = NULL;
	max = 0;
	skip_whitespaces(&str);
	while (*str)
	{
		len = ft_strlen(str);
		data->token->toksize = tok_len(str, ft_strlen(str));
		addback_toklist(&lst, \
			new_toklist(ft_substr(str, 0, data->token->toksize)));
		max = data->token->toksize;
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

void	skip_whitespaces(char **str)
{
	if (!*str || !**str)
		return ;
	while (**str && is_set(**str, WHITESPACE))
	{
		if (**str == '\0')
			break ;
		*str += 1;
	}
	return ;
}

void	skip_meta(char **str)
{
	if (!*str || !**str)
		return ;
	while (**str && is_set(**str, METACHAR))
		*str += 1;
	return ;
}

int	is_set(char s, char *set)
{
	int	i;

	if (!s || !set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

bool	is_empty(char *str)
{
	int	i;

	if (!str)
		return (true);
	skip_whitespaces(&str);
	i = ft_strlen(str);
	if (i > 0)
		return (false);
	return (true);
}
