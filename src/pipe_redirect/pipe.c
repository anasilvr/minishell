/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:01:02 by tchalifo          #+#    #+#             */
/*   Updated: 2022/12/28 16:11:31 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd *job_loop(t_data *prog_data)
{
	int		pipe_fd[2]		= {-2, -2};
	pid_t	fork_pid		= 0;
	int		exit_status;

	while (prog_data->cmd_lst != NULL && prog_data->cmd_lst->io_flag == 1)
	{
		if (prog_data->cmd_lst->next != NULL)
			if (pipe(pipe_fd) == -1)
				exit(errno);
		fork_pid = fork();
		if (fork_pid == -1)
			exit(errno);
		if (fork_pid == 0)
		{
			if (prog_data->cmd_lst->prev == NULL) // Si il sagit de la premiere cmd, verifier si il y a une redir d'input
			{
				if (prog_data->cmd_lst->filefd[0] != -2)
				{
					dup2 (prog_data->cmd_lst->filefd[0], 0);
					close (prog_data->cmd_lst->filefd[0]);
				}
			}
			if (prog_data->cmd_lst->next != NULL)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], 1);
				close(pipe_fd[1]);
			}
			else // // Si il sagit de la dernière cmd, verifier si il y a une redir d'output
			{
				if (prog_data->cmd_lst->filefd[1] != -2)
				{
					dup2 (prog_data->cmd_lst->filefd[1], 1);
					close (prog_data->cmd_lst->filefd[1]);
				}
			}
			execution_time(prog_data);
		}
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		prog_data->cmd_lst = prog_data->cmd_lst->next;
	}
	/* Bash n'attendra que le dernier processus créé, puisque pipe de par sont principe attend
	qu'un signal soit envoyé depuis le processus ou il y a écriture indiquand qu'il n'y a plus
	de données a écrire pour que le processus suivant puis terminer la lecture. Le sigint envoyé
	(^d) n'affectera que le dernier processus) */
	waitpid(fork_pid, &exit_status, WNOHANG);
	return (prog_data->cmd_lst);
}
