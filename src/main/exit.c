/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgagnon <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:38:11 by jgagnon           #+#    #+#             */
/*   Updated: 2023/03/29 10:38:12 by jgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_exit(t_data *data)
{
	int	i;

	i = -1;
	if (data->cmd_lst->path)
		free (data->cmd_lst->path);
	while (data->envp_cp[++i])
		xfree(data->envp_cp[i]);
	xfree(data->envp_cp);
	i = -1;
	xfree(data->pwd);
	xfree(data->input);
	free_toklist(data->token);
	free_cmdlist(data->cmd_lst);
	xfree(data);
	close_fdcpy(data);
}

void	free_cmdlist(t_cmd *lst)
{
	t_cmd	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		xfree(lst->cmdline);
		free_tab(lst->args);
		xfree(lst->hd_delimiter);
		xfree(lst);
		lst = tmp;
	}
}

void	close_fdcpy(t_data *data)
{
	close (data->stdio[0]);
	close (data->stdio[1]);
	close (data->stdio[2]);
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
	}
	reset_io(data);
	reset_stdio(data);
}
