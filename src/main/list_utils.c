/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:43:12 by jgagnon           #+#    #+#             */
/*   Updated: 2023/04/19 13:01:50 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tok	*new_toklist(char *tok)
{
	t_tok	*new;

	new = ft_xcalloc(1, sizeof(t_tok));
	new->prev = NULL;
	new->token = tok;
	new->next = NULL;
	return (new);
}

void	addback_toklist(t_tok **toklist, t_tok *new)
{
	t_tok	*last;

	if (!new)
		return ;
	if (*toklist)
	{
		last = get_lasttok(*toklist);
		new->prev = last;
		last->next = new;
		new->next = NULL;
	}
	else
		*toklist = new;
}

t_tok	*get_lasttok(t_tok *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

t_tok	*get_first_tok(t_tok *node)
{
	t_tok	*node_ptr;

	node_ptr = node;
	if (!node_ptr)
		return (NULL);
	while (node->prev)
		node = node->prev;
	return (node);
}
