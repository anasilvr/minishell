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

#include "doubly_linked_list.h"

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

void	ft_dllst_print_single_node(t_hdoc *p_lst)
{
	(void) p_lst;
	if (p_lst != NULL)
	{
		// ft_putstr(new_node->the_line);
		// ft_putstr("\n");
	}
}

void	ft_dllst_print_lst(t_hdoc *p_lst)
{
	while (p_lst != NULL)
	{
		ft_dllst_print_single_node(p_lst);
		p_lst = p_lst->next;
	}
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
