/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:01:02 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/12 09:52:30 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* La fonction permet de dupliquer les descripteurs de fichier ouvert au 
 * préalable (incluant ceux du pipe si il y a) vers les entrée et sortie 
 * standard système. Ainsi, à chaques job, notre programme attribura les bons 
 * fd pour les executions.
 * 
 * PROTOTYPE	: static void	job_set(t_data *data, int pipe_fd[2]);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la structure data de notre 
 * programme ainsi que les fd du pipe ouvert précedememnt dans la focntion 
 * job_loop().
 * 
 * RETOUR	: N/A
 * 
 * DETAILS	: N/A
 */
static void	job_set(t_data *data, int pipe_fd[2])
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
	if (data->cmd_lst->next != NULL)
		dup2(pipe_fd[1], 1);
	if (data->cmd_lst->filefd[1] != -2)
	{
		dup2 (data->cmd_lst->filefd[1], 1);
		close (data->cmd_lst->filefd[1]);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

/* La fonction permet de passer en boucle la liste de commande a executer. 
 * Les commandes sont regroupé en une job qui permettra d'executer les 
 * différentes commandes présentes.
 * 
 * PROTOTYPE	: t_cmd *jobs_loop(t_data *data);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la struct data de notre
 * programme.
 * 
 * RETOUR	: N/A
 * 
 * DETAILS	: N/A
 */
t_cmd	*jobs_loop(t_data *data)
{
	int		pipe_fd[2];
	int		exit_status;

	while (data->cmd_lst != NULL)
	{
		if (data->cmd_lst->next != NULL)
			if (pipe(pipe_fd) == -1)
				exit(errno);
		data->fork_pid = fork();
		if (data->fork_pid == -1)
			exit(errno);
		if (data->fork_pid == 0)
		{
			job_set(data, pipe_fd);
			execution_time(data);
		}
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		reset_otherio(data);
		data->cmd_lst = data->cmd_lst->next;
	}
	waitpid(data->fork_pid, &exit_status, 0);
    g_status = exit_status;
	return (data->cmd_lst);
}
