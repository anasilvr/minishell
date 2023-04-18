/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:02:06 by jgagnon           #+#    #+#             */
/*   Updated: 2023/04/14 11:27:35 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*easy_gnl(int fd)
{
	char	*line;
	char	read_ret[2];

	line = NULL;
	read_ret[0] = '\0';
	read_ret[1] = '\0';
	while (read(fd, &read_ret[0], 1) != 0)
	{
		if (read_ret[0] == '\n')
			return (line);
		if (line == NULL)
			line = ft_strdup(read_ret);
		else
			line = ft_strjoin_free(line, read_ret);
	}
	return (line);
}

char	*tester(void)
{
	static int	fd;
	char		*r_gnl;

	r_gnl = NULL;
	if (fd == 0)
		fd = open("test.txt", O_RDONLY);
	sleep(1);
	if (!fd)
		return (r_gnl);
	r_gnl = easy_gnl(fd);
	if (r_gnl == NULL)
		close(fd);
	return (r_gnl);
}

void	man_yoyo_ma(char **instruct, t_data *data)
{
	int		fd;
	char	*r_gnl;

	r_gnl = NULL;
	if (instruct[1] == NULL)
		return ;
	if (ft_strncmp(instruct[0], "man", 4) == 0
		&& ft_strncmp(instruct[1], "yoyoma", 7) == 0)
	{
		data->cmd_lst->is_builtin = true;
		fd = open("yoyo_ma.txt", O_RDONLY);
		if (!fd)
			return ;
		r_gnl = easy_gnl(fd);
		while (r_gnl != NULL)
		{
			printf("%s\n", r_gnl);
			r_gnl = easy_gnl(fd);
		}
	}
}
