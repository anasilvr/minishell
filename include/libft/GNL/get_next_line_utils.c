/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:58:17 by anarodri          #+#    #+#             */
/*   Updated: 2023/02/07 13:47:34 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/* read the string until it reaches \0 or the delimiter passed as a int.
** returns a pointer to the delimiter location. */
char	*gnl_strchr(char *str, int c)
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
char	*gnl_strjoin(char *dst, char *src)
{
	char	*tmp;
	size_t	index_dst;
	size_t	index_src;

	if (dst == NULL || src == NULL)
		return (NULL);
	tmp = (char *)malloc((gnl_strlen(dst) + gnl_strlen(src)) + 1);
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

void	gnl_bzero(void *s, size_t n)
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

void	*gnl_calloc(size_t num, size_t size)
{
	void	*ptr;

	ptr = malloc (num * size);
	if (ptr == NULL)
		return (NULL);
	gnl_bzero(ptr, (num * size));
	return (ptr);
}
