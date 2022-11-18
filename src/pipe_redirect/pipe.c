/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:01:02 by tchalifo          #+#    #+#             */
/*   Updated: 2022/11/17 11:12:54 by tchalifo         ###   ########.fr       */
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
		if (prog_data->cmd_lst->prev != NULL || \
		prog_data->cmd_lst->prev->io_flag == PIPE)
			setup_pipe_in(prog_data);
		if (pipe(prog_data->pipe_fd) == -1)
			perror(NULL);
		prog_data->cmd_lst->fork_pid = fork();
		if (prog_data->cmd_lst->fork_pid == -1)
			perror(NULL);
		else if (prog_data->cmd_lst->fork_pid == 0) // INTO CHILD PROCESS
		{
			setup_pipe_out(prog_data);
			if (execve(prog_data->cmds_list->var_data->absolute_path, \
				prog_data->cmds_list->var_data->cmd_argument, envp) == -1)
		}
		waitpid(0, NULL, 0);
		prog_data->cmd_lst = prog_data->cmd_lst->next;
	}
	execution_manager(prog_data); // Retour at exec_manager for complete last cmd after last pipe
}

