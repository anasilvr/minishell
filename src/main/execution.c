#include "../../include/minishell.h"
/* Les différents possibilitées de traitement des redirections par Bash
 * bonjour > cat == ERROR zsh: command not found: bonjour && open a créé le fichier cat s'il n'existait pas
 * bonjour >> cat == ERROR zsh: command not found: bonjour && open a créé le fichier cat s'il n'existait pas
 * bonjour < cat == ERROR zsh: no such file or directory: cat
 * echo bob > cat == SUCCESS fichier cat créé avec le mot bob à l'intérieur
 * cat < file (file 1 exist)== SUCCESS Content of file are put in stdin of cat and is stdout go to terminal
 * cat < file2 (file2 not exist) == ERROR zsh: no such file or directory: file2
 *
 */

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

// Une node de cmd contiendra une commande avec ses param , le type (| < > >> <<OEF) devant la commande si il y a

void	exec_manager(t_data *prog_data)
{
	while (prog_data->cmd_lst != NULL)
	{

		if (prog_data->cmd_lst->io_flag == 4) //if is an input redirect <
		{
			prog_data->cmd_lst->cmdio_fd[1] = open_to_read \
			(prog_data->cmd_lst->next->cmdline);
		}
		else if (prog_data->cmd_lst->io_flag == 5) //if is an output redirect > (Open file and put the fd into struct in int *cmdio_fd)
		{
			prog_data->cmd_lst->cmdio_fd[1] = open_to_write \
			(prog_data->cmd_lst->next->cmdline, O_TRUNC);
		}
		else if (prog_data->cmd_lst->io_flag == 6) //if is an output redirect in append mode >> (Open file and put the fd into struct in int *cmdio_fd)
		{
			prog_data->cmd_lst->cmdio_fd[1] = open_to_write \
			(prog_data->cmd_lst->next->cmdline, O_APPEND);
		}
		setupio(prog_data);
		}
		exec_time(prog_data);
	}
}

void	exec_time(t_data *prog_data)
{
	builtins_checker(prog_data);
	if (if_buildtin == false)
		execve();
}


// HOLD
void	exec_chain(t_data *prog_data)
{
	int	file_fd;

	while (prog_data->cmd_lst != NULL)
	{
		if (prog_data->cmd_lst->next->cmdline == '|')
		{
			setup_pipe_in(prog_data);
			if (pipe(prog_data->pipe_fd) == -1)
				perror(NULL);
			prog_data->cmd_lst->fork_pid = fork();
			if (prog_data->cmd_lst->fork_pid == -1)
				perror(NULL);
			else if (prog_data->cmd_lst->fork_pid == 0) // INTO CHILD PROCESS
			{
			setup_pipe_out(prog_data);
			// if (execve(prog_data->cmds_list->var_data->absolute_path, \
			// 	prog_data->cmds_list->var_data->cmd_argument, envp) == -1)
			}
		}
		/* OUTPUT REDIRECT, si le prochain token est une redirection out ouvrir
		 * le fichier sur un fd en write mode et executer la commande ensuite. */
		else if (prog_data->cmd_lst->next->cmdline == '>')
		{
			file_fd = open_to_write(prog_data->cmd_lst->next->next->cmdline, 0);
		}
		else if (prog_data->cmd_lst->cmdline == '<') //INTPUT REDIRECT
		{}
		else if (prog_data->cmd_lst->cmdline == '>>') // INPUT REDIRECT APPENDING
		{}
		else if (prog_data->cmd_lst->cmdline == '<<') // HEREDOC
		{}
		builtins_checker();
		prog_data->cmd_lst = prog_data->cmd_lst->next;
	}
}
