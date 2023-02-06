/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:01:02 by tchalifo          #+#    #+#             */
/*   Updated: 2023/02/06 11:12:58 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	job_set(t_data *data, int pipe_fd[2])
{
	int	hd_pipe_fd[2];

	/* Si il sagit d'un heredoc, Un nouveau pipe est créé. Il sera connecté
	 * du bord écriture à la fonction ft_putstr_fd qui, depuis un processus
	 * enfant au préalablement créé, lira la string de chaque nodes que
	 * comprend le heredoc et l'enverra dans le pipe. Ensuite, le processus
	 * parent, qui n'attendra pas le fin de son processus enfant, connectera
	 * le bord lecture du pipe à l'entrée standard (stdin) du système.
	 */
	if (data->heredoc == true)
	{
		hd_pipe_fd[0] = heredoc_to_pipe(data->hd_struct);
		// close (hd_pipe_fd[1]);
		dup2 (hd_pipe_fd[0], 0);
		close (hd_pipe_fd[0]);
	}
	/* Si il sagit de la premiere cmd, verifier si il y a une redir d'input */
	if (data->cmd_lst->filefd[0] != -2)
	{
		dup2 (data->cmd_lst->filefd[0], 0);
		close (data->cmd_lst->filefd[0]);
	}
	if (data->cmd_lst->next != NULL)
		dup2(pipe_fd[1], 1);
	/* Si il sagit de la dernière cmd, verifier si il y a une redir d'output */
	if (data->cmd_lst->filefd[1] != -2)
	{
		dup2 (data->cmd_lst->filefd[1], 1);
		close (data->cmd_lst->filefd[1]);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execution_time(data);
}

t_cmd *jobs_loop(t_data *data)
{
	int		pipe_fd[2] = {-2, -2};
	int		exit_status;
	int		i;

	i = 0;
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
		}
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		// reset_otherio(data);
		data->cmd_lst = data->cmd_lst->next;
	}
	/* Bash n'attendra que le dernier processus créé, puisque pipe de par sont principe attend
	qu'un signal soit envoyé depuis le processus ou il y a écriture indiquand qu'il n'y a plus
	de données a écrire pour que le processus suivant puis terminer la lecture. Le sigint envoyé
	(^d) n'affectera que le dernier processus) */
	waitpid(data->fork_pid, &exit_status, 0);
	return (data->cmd_lst);
}
