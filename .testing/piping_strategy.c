#include "../include/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
// #include <wait.h>
#include <fcntl.h>

void	pipe_loop(void);
void	pipe_twocmds_demo(char **envp);

int	main(int argc, char **argv, char**envp)
{
	(void) argc;
	(void) argv;

	// fork_basic_demo();
	if (argc <= 3)
		pipe_twocmds_demo(envp);

	return (0);
}

// static void	pipe_insetup(int *pipe_fd)
// {
// 	dup2(pipe_fd[0], 0);
// 	close(pipe_fd[0]);
// }

// static void	pipe_outsetup(int *pipe_fd)
// {
// 	dup2(pipe_fd[1], 1);
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// }
// void	fork_loop(int nb_of_cmds)
// {

// }


void	pipe_twocmds_demo(char **envp)
{
	int		i				= 0;
	char	*cmds_path[]	= {"/bin/ls", "/bin/cat", "\0"};
	char	*cmds_argv1[]	= {"ls"};
	char	*cmds_argv2[]	= {"cat"};
	// char	**cmds_lst[]	= {{"ls"}, {"cat"}};
	char	**cmds_lst[2];
	int		fork_pid		= 0;
	// int		pipe_fd[2]		= {-2, -2};
	// char buf[100001];
	printf("Executing '%s' and '%s' with a pipe between them.\n", cmds_argv1[0], cmds_argv2[0]);
	cmds_lst[0] = cmds_argv1;
	cmds_lst[1] = cmds_argv2;
	printf ("%s, %s, %s, %s\n", cmds_lst[0][0], cmds_lst[1][0], cmds_path[0], cmds_path[1]);
	while (i <= 0)
	{
		// if (i > 0)
		// {
		// 	// read(pipe_fd[0], buf, 100);
		// 	// printf("%s\n", buf);
		// 	pipe_insetup(pipe_fd);
		// }
		// if (pipe(pipe_fd) == -1)
		// 	exit(errno);
		fork_pid = fork();
		if (fork_pid == -1)
			exit(errno);
		if (fork_pid == 0)//Si le pid est celui du processus enfant
		{
			// if (i >= 1)
			// pipe_outsetup(pipe_fd);
			if (execve(cmds_path[i], cmds_lst[i], envp) == -1)
				exit(errno);
		}
		else
			waitpid(0, NULL, 0);
			// close(pipe_fd[1]);
		i++;
	}
}


void	fork_basic_demo(void)
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
