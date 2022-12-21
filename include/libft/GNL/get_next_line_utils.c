/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:58:17 by anarodri          #+#    #+#             */
/*   Updated: 2021/11/04 12:05:28 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/* read the string until it reaches \0 or the delimiter passed as a int.
** returns a pointer to the delimiter location. */
char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

/* Concatenate buff (source) to the end of outp string (destination). 
** NUL-terminates the string, frees the old outp, returns new string.
*/
char	*ft_strjoin(char *dst, char *src)
{
	char	*tmp;
	size_t	index_dst;
	size_t	index_src;

	if (dst == NULL || src == NULL)
		return (NULL);
	tmp = (char *)malloc((ft_strlen(dst) + ft_strlen(src)) + 1);
	if (tmp == NULL)
		return (NULL);
	index_dst = 0;
	index_src = 0;
	while (dst[index_dst] != '\0')
	{
		tmp[index_dst] = dst[index_dst];
		index_dst++;
	}
	while (src[index_src] != '\0')
		tmp[index_dst++] = src[index_src++];
	tmp[index_dst] = '\0';
	free(dst);
	dst = NULL;
	return (tmp);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	ptr = malloc (num * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (num * size));
	return (ptr);
}
