/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:38:39 by anarodri          #+#    #+#             */
/*   Updated: 2022/12/15 12:51:09 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_xcalloc(size_t nb, size_t mem_size)

{
	void	*ptr;

	ptr = malloc(nb * mem_size);
	if (!ptr)
	{
		write(STDERR_FILENO, "Memory allocation error: Aborting.", 35);
		exit(EXIT_FAILURE);
	}
	ft_bzero(ptr, (nb * mem_size));
	return (ptr);
}
