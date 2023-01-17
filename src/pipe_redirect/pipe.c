/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:01:02 by tchalifo          #+#    #+#             */
/*   Updated: 2023/01/17 15:35:50 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd *job_loop(t_data *data)
{
	int		pipe_fd[2]		= {-2, -2};
	// pid_t	fork_pid		= 0;
	int		exit_status;
	int		i;

	i = 0;
	while (data->cmd_lst != NULL) // && data->cmd_lst->io_flag == 1)
	{
		if (data->cmd_lst->next != NULL)
			if (pipe(pipe_fd) == -1)
				exit(errno);
		data->fork_pid = fork();
		if (data->fork_pid == -1)
			exit(errno);
		if (data->fork_pid == 0)
		{
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
			// printf("Je devrais jamais voir cette ligne\n");
		}
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		data->cmd_lst = data->cmd_lst->next;
	}
	/* Bash n'attendra que le dernier processus créé, puisque pipe de par sont principe attend
	qu'un signal soit envoyé depuis le processus ou il y a écriture indiquand qu'il n'y a plus
	de données a écrire pour que le processus suivant puis terminer la lecture. Le sigint envoyé
	(^d) n'affectera que le dernier processus) */
	waitpid(data->fork_pid, &exit_status, 0);
	return (data->cmd_lst);
}

// OLD
// t_cmd *job_loop(t_data *data)
// {
// 	int		pipe_fd[2]		= {-2, -2};
// 	pid_t	fork_pid		= 0;
// 	int		exit_status;

// 	while (data->cmd_lst != NULL) // && data->cmd_lst->io_flag == 1)
// 	{
// 		if (data->cmd_lst->next != NULL)
// 			if (pipe(pipe_fd) == -1)
// 				exit(errno);
// 		fork_pid = fork();
// 		if (fork_pid == -1)
// 			exit(errno);
// 		if (fork_pid == 0)
// 		{
// 			/* Si il sagit de la premiere cmd, verifier si il y a une redir d'input */
// 			if (data->cmd_lst->prev == NULL && data->cmd_lst->filefd[0] != -2)
// 			{
// 				dup2 (data->cmd_lst->filefd[0], 0);
// 				close (data->cmd_lst->filefd[0]);
// 			}
// 			if (data->cmd_lst->next != NULL)
// 			{
// 				close(pipe_fd[0]);
// 				dup2(pipe_fd[1], 1);
// 				close(pipe_fd[1]);
// 			}
// 			/* Si il sagit de la dernière cmd, verifier si il y a une redir d'output */
// 			else
// 			{
// 				if (data->cmd_lst->filefd[1] != -2)
// 				{
// 					dup2 (data->cmd_lst->filefd[1], 1);
// 					close (data->cmd_lst->filefd[1]);
// 				}
// 			}
// 			execution_time(data);
// 		}
// 		close(pipe_fd[1]);
// 		dup2(pipe_fd[0], 0);
// 		close(pipe_fd[0]);
// 		data->cmd_lst = data->cmd_lst->next;
// 	}
// 	/* Bash n'attendra que le dernier processus créé, puisque pipe de par sont principe attend
// 	qu'un signal soit envoyé depuis le processus ou il y a écriture indiquand qu'il n'y a plus
// 	de données a écrire pour que le processus suivant puis terminer la lecture. Le sigint envoyé
// 	(^d) n'affectera que le dernier processus) */
// 	waitpid(fork_pid, &exit_status, WNOHANG);
// 	return (data->cmd_lst);
// }
