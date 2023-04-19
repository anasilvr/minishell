/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:38:11 by jgagnon           #+#    #+#             */
/*   Updated: 2023/04/19 08:48:32 by tchalifo         ###   ########.fr       */
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
	close_fdcpy(data);
	xfree(data);
}

void	*free_cmdlist(t_cmd *lst)
{
	t_cmd	*tmp;

	if (!lst)
		return (NULL);
	while (lst)
	{
		tmp = lst->next;
		xfree(lst->cmdline);
		free_tab(lst->args);
		xfree(lst->hd_delimiter);
		xfree(lst);
		lst = tmp;
	}
	return (lst);
}

void	close_fdcpy(t_data *data)
{
	struct stat	*f_info;

	f_info = malloc(sizeof(struct stat));
	if (fstat(data->stdio[0], f_info) == 0)
		close (data->stdio[0]);
	if (fstat(data->stdio[1], f_info) == 0)
		close (data->stdio[1]);
	if (fstat(data->stdio[2], f_info) == 0)
		close (data->stdio[2]);
	f_info = xfree(f_info);
}

void	readline_exit(t_data *data)
{
	clean_exit(data);
	printf("exit\n");
	exit(0);
}
