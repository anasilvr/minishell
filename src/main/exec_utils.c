/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgagnon <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:20:40 by jgagnon           #+#    #+#             */
/*   Updated: 2023/03/29 10:20:42 by jgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_set(t_data *data)
{
	int	hd_pipe_out_fd;

	if (data->heredoc == true)
	{
		hd_pipe_out_fd = heredoc_to_pipe(data->hd_struct);
		dup2 (hd_pipe_out_fd, 0);
		close (hd_pipe_out_fd);
	}
	if (data->cmd_lst->filefd[0] != -2)
	{
		dup2 (data->cmd_lst->filefd[0], 0);
		close (data->cmd_lst->filefd[0]);
	}
	if (data->cmd_lst->filefd[1] != -2)
	{
		dup2 (data->cmd_lst->filefd[1], 1);
		close (data->cmd_lst->filefd[1]);
	}
}
