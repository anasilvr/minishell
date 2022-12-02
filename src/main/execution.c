#include "minishell.h"


/* Exemples de chaine d'execution possible
 * file1 > echo | cat > file2 > file3 > cat | cat | cat >> file4
 *
 * sed 's/bib/lol/' file.txt > file2.txt
 *
 */

static void	external_bin_exec(t_data *prog_data, char *binpath, char **argv, char **envp)
{
	if (prog_data->cmd_lst->fork_pid != 0) // Alredy into a child process because of pipe
	{
		prog_data->cmd_lst->fork_pid = fork();
		if (prog_data->cmd_lst->fork_pid == -1)
			perror(NULL);
		waitpid(0, NULL, 0);
	}
	if (prog_data->cmd_lst->fork_pid == 0)
	{
		if (execve(binpath, argv, envp) == -1)
		{
			perror(NULL);
			ft_putstr_fd(strerror(errno), 2);

		}
	}
}

void	execution_time(t_data *prog_data)
{
	char **splitted_args;

	setupio(prog_data);
	if (prog_data->cmd_lst->it_builtin == false)
	{
		splitted_args = ft_split(prog_data->cmd_lst->cmdline, ' ');
		external_bin_exec \
		(prog_data, splitted_args[0], splitted_args, prog_data->envp_cp);
		if (prog_data->cmd_lst->fork_pid == 0)
		{
			clean_exit(prog_data);
			exit(errno);
		}
	}
	waitpid(0, NULL, 0);
}
// file.txt < cat
void	execution_manager(t_data *prog_data)
{
	while (prog_data->cmd_lst != NULL)
	{
		prog_data->cmd_lst->it_builtin = false;
		// prog_data->cmd_lst->fork_pid = -2;
		if (prog_data->cmd_lst->io_flag > 1 && prog_data->cmd_lst->io_flag < 7) // Redirection
		{
			redirect_manager(prog_data);
			if (prog_data->cmd_lst->cmdio_fd[1] == -1 || \
			(prog_data->cmd_lst->cmdio_fd[0] == -1 && errno == EACCES))
			{
				clean_exit(prog_data);
				exit (errno);
			}

		}
		if (prog_data->cmd_lst->io_flag == PIPE) // Pipe
		{
			pipe_manager(prog_data);
		}
		if (prog_data->cmd_lst != NULL && prog_data->cmd_lst->cmdline != NULL) // Check if it is an only io_flag node. For this case ex: < cat | cat file1
			execution_time(prog_data);
		/* The reset_iocpy function needed becose i dont want garbage if i dont set a fd to a custom one*/
		reset_iocpy(prog_data);
		prog_data->cmd_lst = prog_data->cmd_lst->next;
		/* Next "if" needed for cases where i have a redirect and need to skip the next token,
		 * like cat < file.txt, where i dont need to execute file.txt so i pass the next token*/
		if ((prog_data->cmd_lst != NULL && prog_data->cmd_lst->prev != NULL) && \
		(prog_data->cmd_lst->prev->io_flag >= 4 && prog_data->cmd_lst->prev->io_flag <= 6))
			prog_data->cmd_lst = prog_data->cmd_lst->next;
	}
}

// cat | cat | cat > file1.txt




/* Le heredoc ne doit pas expend la variable
export cmd=echo
$cmd lol
lol */