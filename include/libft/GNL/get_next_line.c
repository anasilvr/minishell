/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:58:13 by anarodri          #+#    #+#             */
/*   Updated: 2022/12/15 11:28:30 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Function that returns a line read from a file descriptor.
** Returns: the read line. NULL if it reaches the EOF or an error occurs.
*/

#include "get_next_line.h"

char	*read_to_backup(int fd, char *backup, char *buffer)
{
	char	*tmp;
	int		bytes;
	int		start;

	bytes = 1;
	start = 0;
	while (start == 0 && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			xfree(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		if (!backup)
			backup = ft_strdup("");
		tmp = backup;
		backup = ft_strjoin(backup, buffer);
		xfree(tmp);
		if (ft_strchr(backup, '\n'))
			start = 1;
	}
	free(buffer);
	return (backup);
}

char	*make_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	line = (char *)malloc(i + 2);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, backup, (i + 2));
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*new_backup(char *backup)
{
	int		i;
	char	*str;

	i = 0;
	while (backup[i] != '\0' && backup[i] != '\n')
		i++;
	if (backup[i] == '\0')
	{
		free(backup);
		return (NULL);
	}
	str = (char *)malloc(ft_strlen(backup) - i + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, backup + i + 1, ft_strlen(backup) - i + 1);
	xfree(backup);
	return (str);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buffer;
	static char		*backup;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) + sizeof(char));
	if (!buffer)
	{
		xfree(buffer);
		return (NULL);
	}
	backup = read_to_backup(fd, backup, buffer);
	if (!backup)
		return (NULL);
	line = make_line(backup);
	backup = new_backup(backup);
	return (line);
}
