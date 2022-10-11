/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:58:13 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/20 12:06:08 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Function that returns a line read from a file descriptor.
** Returns: the read line. NULL if it reaches the EOF or an error occurs.
*/

#include "get_next_line.h"

/* Fills a buffer based on bytes counted by read.
** Mallocs enough space for a buffer, reads the first line of the file
** and recreates it accordingly by applying ft_strjoin.
** Return: Concatenation of conserved buffer and the new line.
** If an error occurs during read, frees buffer and returns NULL*/
char	*read_to_buffer(int fd, char *buffer)
{
	char	*tmp;
	int		bytes;

	if (buffer == NULL)
		buffer = ft_calloc (1, 1);
	tmp = malloc(BUFFER_SIZE + 1);
	if (tmp == NULL)
		return (NULL);
	bytes = 1;
	while (ft_strchr(buffer, '\n') == NULL && bytes != 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(tmp);
			free(buffer);
			return (NULL);
		}
		tmp[bytes] = '\0';
		buffer = ft_strjoin(buffer, tmp);
	}
	free (tmp);
	return (buffer);
}

/* Creates the line saved inside *buffer.
** Copies buffer up until the next new line, NULL-terminating the string.
** Return: next line to be printed, NULL is allocation fails.*/
char	*make_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc(i + 2);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/* Updates buffer by reseting its start to the character after the next \n.*/
// char	*new_buffer(char *buffer)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	while (buffer[i] != '\0' && buffer[i] != '\n')
// 		i++;
// 	if (buffer[i] == '\0')
// 	{
// 		free(buffer);
// 		return (NULL);
// 	}
// 	str = (char *)malloc(ft_strlen(buffer) - i + 1);
// 	if (str == NULL)
// 		return (NULL);
// 	i += 1;
// 	j = 0;
// 	while (buffer[i] != '\0')
// 		str[j++] = buffer[i++];
// 	str[j] = '\0';
// 	free(buffer);
// 	buffer = NULL;
// 	return (str);
// }

/* Reads the file's text to the variable buffer (read_to_buffer),
** Creates a new line if the buffer is not yet empty (make_line),
** Updates buffer so it points to the beginning of the next line.
** Returns: the line created. */
char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_to_buffer(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = make_line(buffer);
	buffer = new_buffer(buffer);
	return (line);
}
