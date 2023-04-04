/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:56:05 by anarodri          #+#    #+#             */
/*   Updated: 2023/04/03 16:05:52 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*temp;
	size_t	index_dst;
	size_t	index_src;

	index_dst = -1;
	index_src = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (temp == 0)
		return (NULL);
	while (s1[++index_dst] != '\0')
		temp[index_dst] = s1[index_dst];
	while (s2[index_src] != '\0')
	{
		temp[index_dst] = s2[index_src];
		index_dst++;
		index_src++;
	}
	temp[index_dst] = '\0';
	if (s1)
		free((void *)s1);
	return (temp);
}
