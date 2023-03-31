/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:38:11 by jgagnon           #+#    #+#             */
/*   Updated: 2023/03/31 15:24:49 by tchalifo         ###   ########.fr       */
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

void	readline_exit(t_data *data)
{
	clean_exit(data);
	printf("exit\n");
	exit(0);
}
