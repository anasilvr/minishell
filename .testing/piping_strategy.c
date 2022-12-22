#include "../include/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
// #include <wait.h>
#include <fcntl.h>
#include <string.h>

void	pipe_loop(void);
void	pipe_twocmds_demo(char **envp);
void	ft_call_to_execve(char *cmd_path, char **cmd_argv, char **cmd_envp);
void	pipe_multicmd_demo(char **envp);


int	main(int argc, char **argv, char**envp)
{
	(void) argc;
	(void) argv;

	// fork_basic_demo();
	// if (argc <= 3)
	// pipe_twocmds_demo(envp);
	// ft_call_to_execve("/bin/ls", argv, envp);
	pipe_multicmd_demo(envp);
	return (0);
}

void	ft_call_to_execve(char *cmd_path, char **cmd_argv, char **cmd_envp)
{
	(void)cmd_argv;

	char *argv[2] = {"ls"};
	if (execve(cmd_path, argv, cmd_envp) == -1)
	{
		printf("damn\n");
		// ft_putstr_fd("Command not found : ", 2);
		// ft_putstr_fd(cmd_argv[0], 2);
	}
}

static void	pipe_insetup(int *pipe_fd)
{
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}

static void	pipe_outsetup(int *pipe_fd)
{
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
// void	fork_loop(int nb_of_cmds)
// {

// }

void	pipe_multicmd_demo(char **envp)
{
	int		i				= 0;
	char	*cmds_path[]	= {"/bin/ls", "/bin/cat"};
	char	*cmds_argv1[]	= {"ls", NULL};
	char	*cmds_argv2[]	= {"grep", "make", NULL};
	char	*cmds_argv3[]	= {"cat", NULL};
	char	**cmds_lst[4];
	// int		fork_pid		= 0;
	int		pipe_fd[2]		= {-2, -2};
	int		fork_pid[100]; // Il pourrait etre meiux de prendre le nombre de commandes comme ref
	int		exit_status;

	cmds_lst[0] = cmds_argv1;
	cmds_lst[1] = cmds_argv2;
	cmds_lst[2] = cmds_argv3;
	cmds_lst[3] = NULL;
	printf("%s | %s | %s | %s\n", cmds_lst[0], cmds_lst[1], cmds_lst[2], cmds_lst[3]);
	//Opening all child
	while (i<= 2)
	{
		if (i > 0)
			pipe_insetup(pipe_fd);
		if (pipe(pipe_fd) == -1)
			exit(errno);
		fork_pid[i] = fork();
		if (fork_pid[i] == -1)
			exit(errno);
		if (fork_pid[i] == 0)//Si le pid est celui du processus enfant
		{
			if (i <= 0)
			{
				printf("test\n");
				pipe_outsetup(pipe_fd);
			}
			if (execve(cmds_path[i], cmds_lst[i], envp) == -1)
				perror("");
		}
		i++;
	}
	while (i >= 0)
	{
		waitpid(fork_pid[i], &exit_status, 0);
		i--;
	}
}


void	pipe_twocmds_demo(char **envp)
{
	int		i				= 0;
	char	*cmds_path[]	= {"/bin/ls", "/bin/cat"};
	char	*cmds_argv1[]	= {"ls", NULL};
	char	*cmds_argv2[]	= {"cat", NULL};
	// char	**cmds_lst[]	= {{"ls"}, {"cat"}};
	char	**cmds_lst[3];

	int		fork_pid		= 0;
	int		pipe_fd[2]		= {-2, -2};

	cmds_lst[0] = cmds_argv1;
	cmds_lst[1] = cmds_argv2;
	cmds_lst[2] = NULL;
	while (i <= 1)
	{
		if (i > 0)
		{
			pipe_insetup(pipe_fd);
		}
		if (pipe(pipe_fd) == -1)
			exit(errno);
		fork_pid = fork();
		if (fork_pid == -1)
			exit(errno);
		if (fork_pid == 0)//Si le pid est celui du processus enfant
		{
			if (i <= 0)
			{
				printf("test\n");
				pipe_outsetup(pipe_fd);
			}
			if (execve(cmds_path[i], cmds_lst[i], envp) == -1)
				perror("");
		}
		else
			waitpid(0, NULL, 0);
			close(pipe_fd[1]);
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
