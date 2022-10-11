/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:32:52 by anarodri          #+#    #+#             */
/*   Updated: 2022/10/04 12:51:29 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new;

	new = NULL;
	if (!ptr)
		new = malloc(size);
	if (!size && ptr != NULL)
	{
		new = malloc(1);
		free(ptr);
	}
	if (!new)
		return (NULL);
	ft_memcpy(new, ptr, size);
	return (new);
}
