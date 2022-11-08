/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:39:04 by anarodri          #+#    #+#             */
/*   Updated: 2022/11/02 17:39:07 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*xfree(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}
