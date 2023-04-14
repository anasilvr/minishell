/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:46:08 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/14 11:12:53 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	skip_whitespaces(char **str)
{
	if (!*str || !**str)
		return ;
	while (**str && is_set(**str, WHITESPACE) && (*str + 1))
		*str += 1;
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
