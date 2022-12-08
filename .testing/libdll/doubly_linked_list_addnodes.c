/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_addnodes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:13:55 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/18 11:13:55 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doubly_linked_list.h"

t_hdoc	*ft_dllst_new(char *str)
{
	t_hdoc	*new_node;

	new_node = malloc(sizeof(t_hdoc));
	if (new_node)
	{
		new_node->the_line = str;
		new_node->next = NULL;
		new_node->previous = NULL;
	}
	return (new_node);
}

t_hdoc	*ft_dllst_add_front(t_hdoc *p_lst, char *str)
{
	t_hdoc	*new_node;

	if (!p_lst)
		return (ft_dllst_new(str));
	new_node = malloc(sizeof(t_hdoc));
	if (new_node)
	{
		new_node->the_line = str;
		new_node->next = p_lst;
		new_node->previous = NULL;
		p_lst->previous = new_node;
		return (new_node);
	}
	return (NULL);
}

t_hdoc	*ft_dllst_add_back(t_hdoc *p_lst, char *str)
{
	t_hdoc	*new_node;

	if (!p_lst)
		return (ft_dllst_new(str));
	new_node = malloc(sizeof(t_hdoc));
	if (new_node)
	{
		while (p_lst->next != NULL)
			p_lst = p_lst->next;
		new_node->the_line = str;
		new_node->next = NULL;
		new_node->previous = p_lst;
		p_lst->next = new_node;
		while (p_lst->previous != NULL)
			p_lst = p_lst->previous;
		return (p_lst);
	}
	return (NULL);
}
