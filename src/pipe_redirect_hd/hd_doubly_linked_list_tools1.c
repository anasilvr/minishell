/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_tools1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:15:52 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/18 11:15:52 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_dllst_size(t_hdoc *p_lst)
{
	int	count;

	count = 0;
	while (p_lst != NULL)
	{
		count++;
		p_lst = p_lst->next;
	}
	return (count);
}

t_hdoc	*ft_dllist_go_to_left(t_hdoc *p_lst)
{
	while (p_lst->previous != NULL)
		p_lst = p_lst->previous;
	return (p_lst);
}

t_hdoc	*ft_dllist_go_to_right(t_hdoc *p_lst)
{
	while (p_lst->next != NULL)
		p_lst = p_lst->next;
	return (p_lst);
}
