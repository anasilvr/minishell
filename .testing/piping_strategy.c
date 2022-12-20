#include "../include/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <wait.h>
#include <fcntl.h>

void	pipe_loop(void);
void	pipe_twocmds_demo(char **envp);

int	main(int argc, char **argv, char**envp)
{
	(void) argc;
	(void) argv;

	// pipe_basic_demo();
	printf("Executing '%s' and '%s' with a pipe between them.\n", cmds[0], cmds[1]);
	pipe_twocmds_demo(envp);

	return (0);
}

static void	pipe_iosetup(int fork_pid, int *pipe_fd)
{

	if (fork_pid == 0)
	{
		if (cmds_amount = 0) // Première commande à être executée.
			close(pipe_fd[0]);

		else
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]);
		if (cmds_amount = last)
	}
}

void	fork_loop(int nb_of_cmds)
{

}


void	pipe_twocmds_demo(char **envp)
{
	int		i 				= -2;
	char	*cmds_path[]	= {"/usr/bin/ls", "/usr/bin/cat", "\0"};
	char	*cmds_argv[]	= {"ls", "cat", "\0"};
	int		fork_pid		= -2;
	int		pipe_fd[2]		= {-2, -2};
	int		pipe_old_fdout

	while (i <= 0)
	{
		if (pipe(pipe_fd) == -1)
			exit(errno);
		fork_pid = fork();
		if (fork_pid == -1)
			exit(errno);
		if (fork_pid == 0)//Si le pid est celui du processus enfant
		{
			printf("Hello ! From the child process number %d.\n", i);
			pipe_iosetup(fork_pid, pipe_fd);
			if (execve(cmds_lst[i], cmds_argv, envp) == -1)
				exit(errno);
		}
		else
		{
			waitpid(0, 0, 0);

			printf("Done to wait, The parent process is here now!\n");
		}
		i--;
	}
}


void	pipe_basic_demo(void)
{
	int	fork_pid;

	fork_pid = fork();
	if (fork_pid == -1)
		exit(-1);
	if (fork_pid == 0)//Si le pid est celui du processus enfant
	{
		printf("Hello ! From the child process.\n");
	}
	else
	{
		waitpid(0, 0, 0);
		printf("Done to wait, The parent process is here now!\n");
	}
	if (fork_pid == 0)
	{
		printf("Bye! Say the child process!\n");
		exit(errno); //Terminaison du processus enfant
	}
}
