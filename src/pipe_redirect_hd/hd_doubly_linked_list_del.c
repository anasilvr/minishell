/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_del.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:14:33 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/18 11:14:33 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_dllst_delone(t_hdoc *p_lst)
{
	if (p_lst)
	{
		ft_dllst_secure_del(p_lst);
		if (p_lst->previous)
			p_lst->previous->next = NULL;
		free(p_lst);
	}
}

void	ft_dllst_clear(t_hdoc *p_lst)
{
	t_hdoc	*tmp;

	while (p_lst->next != NULL)
		p_lst = p_lst->next;
	tmp = NULL;
	while (p_lst != NULL)
	{
		tmp = p_lst->previous;
		ft_dllst_delone(p_lst);
		p_lst = tmp;
	}
}

void	ft_dllst_secure_del(t_hdoc *p_lst)
{
	(void) p_lst;
	if (p_lst->the_line)
	{
		free (p_lst->the_line);
		p_lst->the_line = NULL;
	}
}

bool	ft_dllst_isempty(t_hdoc *p_lst)
{
	if (p_lst == NULL)
		return (true);
	return (false);
}
