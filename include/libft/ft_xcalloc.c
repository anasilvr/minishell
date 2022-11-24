/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:38:39 by anarodri          #+#    #+#             */
/*   Updated: 2022/11/22 16:44:09 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_xcalloc(size_t mem_size)

{
	void	*ptr;

	ptr = malloc(mem_size);
	if (!ptr)
	{
		write(STDERR_FILENO, "Memory allocation error: Aborting.", 35);
		exit(EXIT_FAILURE);
	}
	ft_bzero(ptr, (mem_size));
	return (ptr);
}
