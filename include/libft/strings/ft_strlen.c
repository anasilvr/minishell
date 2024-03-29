/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:55:00 by anarodri          #+#    #+#             */
/*   Updated: 2023/03/29 10:23:32 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Return: number of characters that precede the terminating NUL-character.
*/

#include "../libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
