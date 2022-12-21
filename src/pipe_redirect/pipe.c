/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:01:02 by tchalifo          #+#    #+#             */
/*   Updated: 2022/12/19 14:14:14 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Fonction pour executer deux commande (et deriver leur I/O respectif de
 * manière à connecter la sortie de la comamnde 1 (cmd1) à l'entré de la
 * commande 2 (cmd2).
 * Test lines:
 *     echo bonjour | cat | cat > file.txt
 *     < cat | cat file1
 */
void	pipe_manager(t_data *prog_data)
{
	while (((prog_data->cmd_lst != NULL) && (prog_data->cmd_lst->io_flag == PIPE))
		|| ((prog_data->cmd_lst != NULL && prog_data->cmd_lst->prev != NULL) &&
		prog_data->cmd_lst->prev->io_flag == PIPE))
	{
		if (prog_data->cmd_lst->prev != NULL && \
			prog_data->cmd_lst->prev->io_flag == PIPE)
				setup_pipe_in(prog_data);
		else if (prog_data->cmd_lst->io_flag == REDIR_OUT)
				redirect_setup(prog_data);

		if (pipe(prog_data->cmd_lst->pipefd) == -1)
			perror("Minishell:");

		prog_data->cmd_lst->fork_pid = fork();
		if (prog_data->cmd_lst->fork_pid == -1)
			perror("Minishell:");
		else if (prog_data->cmd_lst->fork_pid == 0) // INTO CHILD PROCESS
		{
			setup_pipe_out(prog_data);
			execution_time(prog_data);
		}
		else
			waitpid(0, NULL, WNOHANG);
		prog_data->cmd_lst = prog_data->cmd_lst->next;
	}
	// if (prog_data->cmd_lst->prev != NULL && \
	// prog_data->cmd_lst->prev->io_flag == PIPE)
	// 	setup_pipe_in(prog_data);
	// if (prog_data->cmd_lst->io_flag == REDIR_OUT)
	// 	redirect_manager(prog_data);
	// execution_manager(prog_data); // Retour at exec_manager for complete last cmd after last pipe
}

void	setup_pipe_in(t_data *prog_data)
{
	close(prog_data->pipe_fd[WRITE_ENDPIPE]);
	dup2(prog_data->pipe_fd[READ_ENDPIPE], 0);
	close(prog_data->pipe_fd[READ_ENDPIPE]);
}

void	setup_pipe_out(t_data *prog_data)
{
	if (prog_data->cmd_lst->next != NULL)
	{
		close(prog_data->pipe_fd[READ_ENDPIPE]);
		dup2(prog_data->pipe_fd[WRITE_ENDPIPE], 1);
		close(prog_data->pipe_fd[WRITE_ENDPIPE]);
	}
	else
		close (prog_data->pipe_fd[READ_ENDPIPE])
}

//De cette maniere, pipe executera jusqua la fin les exec dans un child process et comme cela seul dans les child seront modifier les fd (dup2 stdin to pipefd)
// cat | cat | cat > file1.txt
// echo bonjour | cat