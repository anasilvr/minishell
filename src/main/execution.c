#include "../../include/minishell.h"


/* Exemples de chaine d'execution possible
 * file1 > echo | cat > file2 > file3 > cat | cat | cat >> file4
 *
 * sed 's/bib/lol/' file.txt > file2.txt
 *
 */

static int	external_bin_exec(char *binpath, char **argv, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return ()
	if (execve(binpath, argv, envp) == -1)
	{
		// Need a standard for exit function after error (clear mem, ect..)
		perror(NULL);
		ft_putstr_fd(strerror(errno), 2);
		exit(errno);
	}
}

void	execution_time(t_data *prog_data)
{
	char **splitted_args;

	setupio(prog_data);
	if (prog_data->cmd_lst->fork_pid != 0) // Alredy into a child process because of pipe
	{
		prog_data->cmd_lst->fork_pid = fork();
	}
	builtins_checker(prog_data);
	if (if_buildtin == false)
	{
		splitted_args = ft_split(prog_data->cmd_lst->cmdline, ' ');
		external_bin_exec \
		(prog_data->cmd_lst->path, splitted_args, prog_data->envp_cp);
	}
}

void	execution_manager(t_data *prog_data)
{
	while (prog_data->cmd_lst != NULL)
	{
		if (prog_data->cmd_lst->io_flag > 2 && prog_data->cmd_lst->io_flag < 7) // Redirection
		{
			redirect_manager();
			if (prog_data->cmd_lst->cmdio_fd[1] == -1 || \
			prog_data->cmd_lst->cmdio_fd[0] == -1)
				// Need a standard for exit function after error (clear mem, ect..)
				exit (errno);
		}
		if (prog_data->cmd_lst->io_flag == PIPE) // Pipe
		{
			pipe_manager(prog_data);
		}
		// Already doing this into pipe_manager() line 32-43-44 in pipe.c
		// if (prog_data->cmd_lst->prev != NULL && \
		// prog_data->cmd_lst->prev->io_flag == PIPE) // For setup last time input to pipe for the node after the last pipe node.
		// 	setup_pipe_in(prog_data);
		if (prog_data->cmd_lst->cmdline != NULL) // Check if it is an only io_flag node. For this case ex: < cat | cat file1
			execution_time(prog_data);
		prog_data->cmd_lst = prog_data->cmd_lst->next;
		reset_iocpy(prog_data);
	}
}

cat | cat | cat > file1.txt