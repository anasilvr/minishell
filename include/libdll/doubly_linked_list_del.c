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

#include "doubly_linked_list.h"

void	ft_dllst_delone(t_hdoc *p_lst)
{
	if (p_lst)
	{
		ft_dllst_secure_del(p_lst);
		free(p_lst);
	}
}

void	ft_dllst_clear(t_hdoc *p_lst)
{
	t_hdoc	*tmp;

	tmp = NULL;
	while (p_lst != NULL)
	{
		tmp = p_lst->next;
		ft_dllst_delone(p_lst);
		p_lst = tmp;
	}
}

bool	ft_dllst_isempty(t_hdoc *p_lst)
{
	if (p_lst == NULL)
		return (true);
	return (false);
}
