/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:37:56 by tchalifo          #+#    #+#             */
/*   Updated: 2022/12/15 08:47:47 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

# include <stdlib.h>

typedef enum t_bool
{
	false,
	true
}t_bool;

typedef struct s_hdoc
{
	char			*the_line;
	struct s_hdoc	*next;
	struct s_hdoc	*previous;
}	t_hdoc;

t_hdoc		*ft_dllst_new(char *str);
t_hdoc		*ft_dllst_add_front(t_hdoc *p_lst, char *str);
t_hdoc		*ft_dllst_add_back(t_hdoc *p_lst, char *str);
void		ft_dllst_delone(t_hdoc *p_lst);
void		ft_dllst_clear(t_hdoc *p_lst);
void		ft_dllst_secure_del(t_hdoc *p_lst);
t_bool		ft_dllst_isempty(t_hdoc *p_lst);
int			ft_dllst_size(t_hdoc *p_lst);
void		ft_dllst_print_single_node(t_hdoc *p_lst);
void		ft_dllst_print_lst(t_hdoc *p_lst);
t_hdoc		*ft_dllist_go_to_left(t_hdoc *p_lst);
t_hdoc		*ft_dllist_go_to_right(t_hdoc *p_lst);

#endif
