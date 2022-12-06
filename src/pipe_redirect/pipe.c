/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:01:02 by tchalifo          #+#    #+#             */
/*   Updated: 2022/12/05 17:08:01 by tchalifo         ###   ########.fr       */
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
	while (prog_data->cmd_lst->io_flag == PIPE)
	{
		if (prog_data->cmd_lst->prev != NULL && \
		prog_data->cmd_lst->prev->io_flag == PIPE)
			setup_pipe_in(prog_data);
		if (pipe(prog_data->pipe_fd) == -1)
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
			waitpid(0, NULL, 0);
		prog_data->cmd_lst = prog_data->cmd_lst->next;
	}
	if (prog_data->cmd_lst->prev != NULL || \
	prog_data->cmd_lst->prev->io_flag == PIPE)
		setup_pipe_in(prog_data);
	if (prog_data->cmd_lst->io_flag == REDIR_OUT)
		redirect_manager(prog_data);
	// execution_manager(prog_data); // Retour at exec_manager for complete last cmd after last pipe
}

// cat | cat | cat > file1.txt
// echo bonjour | cat