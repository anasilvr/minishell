/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:55:14 by jgagnon           #+#    #+#             */
/*   Updated: 2023/04/24 13:25:34 by tchalifo         ###   ########.fr       */
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
	if (data->cmd_lst->hd_struct)
	{
		ft_dllst_clear(data->cmd_lst->hd_struct);
		data->cmd_lst->hd_struct = NULL;
	}
	reset_io(data);
	reset_stdio(data);
	data->token->type = 0;
	data->heredoc = false;
	data->exit_code = g_status;
	g_status = 0;
}

void	reset_io(t_data *data)
{
	struct stat	*f_info;

	f_info = malloc(sizeof(struct stat));
	if (fstat(data->cmd_lst->filefd[0], f_info) == 0)
		close (data->cmd_lst->filefd[0]);
	if (fstat(data->cmd_lst->filefd[1], f_info) == 0)
		close (data->cmd_lst->filefd[1]);
	if (fstat(data->cmd_lst->pipefd[0], f_info) == 0)
		close (data->cmd_lst->pipefd[0]);
	if (fstat(data->cmd_lst->pipefd[1], f_info) == 0)
		close (data->cmd_lst->pipefd[1]);
	f_info = xfree(f_info);
}
