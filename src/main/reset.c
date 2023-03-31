/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgagnon <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:55:14 by jgagnon           #+#    #+#             */
/*   Updated: 2023/03/31 16:55:15 by jgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset(t_data *data)
{
	data->input = xfree(data->input);
	data->nb_cmds = 0;
	data->nb_pipes = 0;
	if (data->cmd_lst->path)
		data->cmd_lst->path = xfree(data->cmd_lst->path);
	if (data->token)
		free_toklist(data->token);
	data->token = ft_xcalloc(1, sizeof(t_tok));
	if (data->cmd_lst)
	{
		free_cmdlist(data->cmd_lst);
		data->cmd_lst = ft_xcalloc(1, sizeof(t_cmd));
	}
	if (data->hd_struct)
	{
		ft_dllst_clear(data->hd_struct);
		data->hd_struct = NULL;
	}
	reset_io(data);
	reset_stdio(data);
}

void	reset_io(t_data *data)
{
	if (data->cmd_lst->filefd[0] != -2)
	{
		close (data->cmd_lst->filefd[0]);
		data->cmd_lst->filefd[0] = -2;
	}
	if (data->cmd_lst->filefd[1] != -2)
	{
		close (data->cmd_lst->filefd[1]);
		data->cmd_lst->filefd[1] = -2;
	}
	if (data->cmd_lst->pipefd[0] != -2)
	{
		close (data->cmd_lst->pipefd[0]);
		data->cmd_lst->pipefd[0] = -2;
	}
	if (data->cmd_lst->pipefd[1] != -2)
	{
		close (data->cmd_lst->pipefd[1]);
		data->cmd_lst->pipefd[1] = -2;
	}
}
