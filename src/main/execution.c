#include "../../include/minishell.h"


/* Exemples de chaine d'execution possible
 * file1 > echo | cat > file2 > file3 > cat | cat | cat >> file4
 *
 * sed 's/bib/lol/' file.txt > file2.txt
 *
 * /

/* 1. file1
 * 1.1 setup input to stdin (0)


 */

/* Conclusions :
 * 1. Vérifier si le node est un type autre qu'un exec ou fichier. Si c'est autre execve me retournera un (voir Anna pour parsing)


*/

// Une node de cmd contiendra une commande avec ses param et le type (| < > >> <<OEF) devant la commande si il y en a un
static void	execution_time(t_data *prog_data)
{
	setupio(prog_data);
	builtins_checker(prog_data);
	if (if_buildtin == false)
		execve();
}

void	execution_manager(t_data *prog_data)
{
	while (prog_data->cmd_lst != NULL)
	{
		if (prog_data->cmd_lst->io_flag > 2 && prog_data->cmd_lst->io_flag < 7) // Redirection
		{
			file_opening_manager();
			if (prog_data->cmd_lst->cmdio_fd[1] == -1 || \
			prog_data->cmd_lst->cmdio_fd[0] == -1)
				exit (errno); // NEED A PROPER EXIT CMD (CLOSE FD & CLEAR MEM)
		}
		if (prog_data->cmd_lst->io_flag == PIPE) // Pipe
		{
			pipe_manager(prog_data);
		}
		if (prog_data->cmd_lst->prev != NULL && \
		prog_data->cmd_lst->prev->io_flag == PIPE) // For setup last time input to pipe for the node after the last pipe node.
			setup_pipe_in(prog_data);
		if (prog_data->cmd_lst->cmdline != NULL) // Check if it is an only io_flag node. For this case ex: < cat | cat file1
			execution_time(prog_data);
		prog_data->cmd_lst = prog_data->cmd_lst->next;
		reset_iocpy(prog_data);
	}
}



// // HOLD
// void	exec_chain(t_data *prog_data)
// {
// 	int	file_fd;

// 	while (prog_data->cmd_lst != NULL)
// 	{
// 		if (prog_data->cmd_lst->next->cmdline == '|')
// 		{
// 			setup_pipe_in(prog_data);
// 			if (pipe(prog_data->pipe_fd) == -1)
// 				perror(NULL);
// 			prog_data->cmd_lst->fork_pid = fork();
// 			if (prog_data->cmd_lst->fork_pid == -1)
// 				perror(NULL);
// 			else if (prog_data->cmd_lst->fork_pid == 0) // INTO CHILD PROCESS
// 			{
// 			setup_pipe_out(prog_data);
// 			// if (execve(prog_data->cmds_list->var_data->absolute_path, \
// 			// 	prog_data->cmds_list->var_data->cmd_argument, envp) == -1)
// 			}
// 		}
// 		/* OUTPUT REDIRECT, si le prochain token est une redirection out ouvrir
// 		 * le fichier sur un fd en write mode et executer la commande ensuite. */
// 		else if (prog_data->cmd_lst->next->cmdline == '>')
// 		{
// 			file_fd = open_to_write(prog_data->cmd_lst->next->next->cmdline, 0);
// 		}
// 		else if (prog_data->cmd_lst->cmdline == '<') //INTPUT REDIRECT
// 		{}
// 		else if (prog_data->cmd_lst->cmdline == '>>') // INPUT REDIRECT APPENDING
// 		{}
// 		else if (prog_data->cmd_lst->cmdline == '<<') // HEREDOC
// 		{}
// 		builtins_checker();
// 		prog_data->cmd_lst = prog_data->cmd_lst->next;
// 	}
// }
