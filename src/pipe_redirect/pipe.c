/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:01:02 by tchalifo          #+#    #+#             */
/*   Updated: 2022/12/27 15:12:00 by tchalifo         ###   ########.fr       */
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

void	pipe_loop(t_data *prog_data)
{
	/* Initialisation de commandes */
	// char	*cmds_path[]	= {"/bin/ls", "/bin/cat", "/bin/cat"};
	// char	*cmds_argv1[]	= {"ls", NULL};
	// char	*cmds_argv2[]	= {"cat", NULL};
	// char	*cmds_argv3[]	= {"cat", NULL};
	// char	**cmds_lst[]	= {cmds_argv1, cmds_argv2, cmds_argv3, NULL};

	int		pipe_fd[2]		= {-2, -2};
	pid_t	fork_pid		= 0;
	// int		i				= 0; // Équivaut au nombre de commande à executer
	int		exit_status;

	while (prog_data->cmd_lst != NULL)
	{
		if (prog_data->cmd_lst->next != NULL)
			if (pipe(pipe_fd) == -1)
				exit(errno);
		fork_pid = fork();
		if (fork_pid == -1)
			exit(errno);
		if (fork_pid == 0)
		{
			if (prog_data->cmd_lst->next != NULL)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], 1);
				close(pipe_fd[1]);
			}
			execution_time(prog_data);
			// execve(cmds_path[i], cmds_lst[i], envp);
		}
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
	// Bash n'attendra que le dernier processus créé, puisque pipe de par sont principe (attendant qu'un eof soit envoyé depuis l'écriture pour terminer la lecture depuis le programme suivant. Le sigint envoyé ^d n'affectera que le dernier processus)
	waitpid(fork_pid, &exit_status, 0);
}
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
	close(prog_data->cmd_lst->pipefd[WRITE_ENDPIPE]);
	dup2(prog_data->cmd_lst->pipefd[READ_ENDPIPE], 0);
	close(prog_data->cmd_lst->pipefd[READ_ENDPIPE]);
}

void	setup_pipe_out(t_data *prog_data)
{
	if (prog_data->cmd_lst->next != NULL)
	{
		close(prog_data->cmd_lst->pipefd[READ_ENDPIPE]);
		dup2(prog_data->cmd_lst->pipefd[WRITE_ENDPIPE], 1);
		close(prog_data->cmd_lst->pipefd[WRITE_ENDPIPE]);
	}
	else
		close (prog_data->cmd_lst->pipefd[READ_ENDPIPE]);
}

//De cette maniere, pipe executera jusqua la fin les exec dans un child process et comme cela seul dans les child seront modifier les fd (dup2 stdin to pipefd)
// cat | cat | cat > file1.txt
// echo bonjour | cat