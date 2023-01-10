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

// void	ft_call_to_execve(char *cmd_path, char **cmd_argv, char **cmd_envp)
// {
// 	(void)cmd_argv;

// 	char *argv[2] = {"ls"};
// 	if (execve(cmd_path, argv, cmd_envp) == -1)
// 	{
// 		printf("damn\n");
// 		// ft_putstr_fd("Command not found : ", 2);
// 		// ft_putstr_fd(cmd_argv[0], 2);
// 	}
// }

void	pipe_multicmd_demo(char **envp)
{
	int		pipe_fd[2][2];
	pid_t	ctrl_child_pid = -2;
	pid_t	exec_child_pid[3] = {-2, -2, -2};
	int		i = 0;
	char	read_buffer[80];
	int		exit_err;

	ctrl_child_pid = fork();
	if (ctrl_child_pid == 0)
	{
		while (i < 3)
		{
			if (pipe(pipe_fd[i]) == -1)
				printf("pipe probleme...\n");
			exec_child_pid[i] = fork();
			if (exec_child_pid[i] == 0)
			{
				// Si nous somme à la premiere iteration
				if (i == 0)
				{
					close(pipe_fd[i][0]);
					write(pipe_fd[i][1], "BONJOUR", 8);
					exit(0);
				}
				// Si nous somme à la derniere iteration
				else if (i == 2)
				{
					close(pipe_fd[i][1]);
					read(pipe_fd[i][0], read_buffer, sizeof(read_buffer));
					printf("%s\n", read_buffer);
					exit(0);
				}
				else
				{
					close(pipe_fd[i-1][1]);
					close(pipe_fd[i][0]);
					dup2(pipe_fd[i-1][0], pipe_fd[i][1]);
				}
			}
			i++;
		}
		while (i > 0)
		{
			waitpid(exec_child_pid[i], &exit_err, 0);
			i--;
		}
	}
}


//OLD again
// void	pipe_multicmd_demo(char **envp)
// {
// 	/* Initialisation de commandes */
// 	char	*cmds_path[]	= {"/bin/cat", "/bin/cat", "/bin/ls"};
// 	char	*cmds_argv1[]	= {"cat", NULL};
// 	char	*cmds_argv2[]	= {"cat", NULL};
// 	char	*cmds_argv3[]	= {"ls", NULL};
// 	char	**cmds_lst[]	= {cmds_argv1, cmds_argv2, cmds_argv3, NULL};

// 	int		pipe_fd[2]		= {-2, -2};
// 	pid_t	fork_pid[3]		= {0, 0, 0};
// 	int		i				= 0; // Équivaut au nombre de commande à executer
// 	int		exit_status;

// 	printf("%s | %s | %s \n\n", cmds_lst[0][0], cmds_lst[1][0], cmds_lst[2][0]);


// 	while (i <= 2)
// 	{
// 		printf("cmd loop %d\n", i);
// 		if (i < 2)
// 			if (pipe(pipe_fd) == -1)
// 				exit(errno);
// 		printf("iiiiiiiiiiiiii = %d\n", i);
// 		fork_pid[i] = fork();
// 		if (fork_pid[i] == -1)
// 			exit(errno);
// 		if (fork_pid[i] == 0)
// 		{
// 			if (i < 2)
// 			{
// 				close(pipe_fd[0]);
// 				dup2(pipe_fd[1], 1);
// 				close(pipe_fd[1]);
// 			}
// 			execve(cmds_path[i], cmds_lst[i], envp);
// 			perror("");
// 		}
// 		close(pipe_fd[1]);
// 		dup2(pipe_fd[0], 0);
// 		close(pipe_fd[0]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i <= 2)
// 	{
// 		printf("iiiiiiiiiiiiiiiiiiiiiiiiiiiii = %d\n", i);
// 		waitpid(fork_pid[i], &exit_status, 0);
// 		i++;
// 	}
// }

// Avec laide de matis
// void	pipe_multicmd_demo(char **envp)
// {
// 	int		i				= 0;
// 	char	*cmds_path[]	= {"/bin/ls", "/bin/cat", "/bin/cat"};
// 	char	*cmds_argv1[]	= {"ls", NULL};
// 	// char	*cmds_argv1[]	= {"ls", "/Users/tchalifo/Documents", NULL};
// 	// char	*cmds_argv2[]	= {"ls", "/Users/tchalifo/Documents/minishell", NULL};
// 	char	*cmds_argv2[]	= {"cat", NULL};
// 	char	*cmds_argv3[]	= {"cat", NULL};
// 	char	**cmds_lst[4];
// 	int		pipe_fd[2]		= {-2, -2};
// 	pid_t		fork_pid = 0;
// 	pid_t		fork_pid2 = 0;// Il pourrait etre meiux de prendre le nombre de commandes comme ref
// 	int		exit_status;
// 	int		stdio[2];

// 	cmds_lst[0] = cmds_argv1;
// 	cmds_lst[1] = cmds_argv2;
// 	cmds_lst[2] = cmds_argv3;
// 	cmds_lst[3] = NULL;
// 	printf("%s | %s | %s \n", cmds_lst[0][0], cmds_lst[1][0], cmds_lst[2][0]);
// 	stdio[0] = dup(0);
// 	stdio[1] = dup(1);
// 	//Opening all child
// 	if (fork_pid2 == -1)
// 			exit(errno);
// 	if (fork_pid == 0)
// 	{
// 		while (i < 2)
// 		{
// 			printf("cmd loop %d\n", i);
// 			if (pipe(pipe_fd) == -1)
// 				exit(errno);
// 			fork_pid = fork();
// 			if (fork_pid == -1)
// 				exit(errno);
// 			if (fork_pid == 0)//Si le pid est celui du processus enfant
// 			{
// 				dup2(pipe_fd[1], 1);
// 				close(pipe_fd[1]);
// 				close(pipe_fd[0]);
// 				execve(cmds_path[i], cmds_lst[i], envp);
// 				perror("");
// 			}
// 			close(pipe_fd[1]);
// 			dup2(pipe_fd[0], 0);
// 			close(pipe_fd[0]);
// 			i++;
// 		}
// 	}
// 	close(pipe_fd[1]);
// 	fork_pid = fork();
// 	if (fork_pid == -1)
// 		exit(errno);
// 	if (fork_pid == 0)//Si le pid est celui du processus enfant
// 	{
// 		dup2(pipe_fd[0], 0);
// 		close(pipe_fd[0]);
// 		printf("Entering in last cmd : i = %d\n", i);
// 		execve(cmds_path[2], cmds_lst[2], envp);
// 		perror("");
// 	}
// 	close(pipe_fd[0]);
// 	waitpid(fork_pid, &exit_status, 0);
// }

//OLD
// void	pipe_multicmd_demo(char **envp)
// {
// 	int		i				= 0;
// 	char	*cmds_path[]	= {"/bin/ls", "/bin/cat", "/bin/cat"};
// 	char	*cmds_argv1[]	= {"ls", "/Users/tchalifo/Documents", NULL};
// 	// char	*cmds_argv2[]	= {"ls", "/Users/tchalifo/Documents/minishell", NULL};
// 	char	*cmds_argv2[]	= {"cat", NULL};
// 	char	*cmds_argv3[]	= {"cat", NULL};
// 	char	**cmds_lst[4];
// 	// int		fork_pid		= 0;
// 	int		pipe_fd[2]		= {-2, -2};
// 	int		fork_pid[100]; // Il pourrait etre meiux de prendre le nombre de commandes comme ref
// 	int		exit_status;
// 	int		stdio[2];

// 	cmds_lst[0] = cmds_argv1;
// 	cmds_lst[1] = cmds_argv2;
// 	cmds_lst[2] = cmds_argv3;
// 	cmds_lst[3] = NULL;
// 	printf("%s | %s | %s \n", cmds_lst[0][0], cmds_lst[1][0], cmds_lst[2][0]);
// 	stdio[0] = dup(0);
// 	stdio[1] = dup(1);
// 	//Opening all child
// 	while (i <= 2)
// 	{
// 		printf("i value at starting loop = %d\n", i);
// 		if (i > 0)
// 		{
// 			printf("test redirect input au : %d\n", i);
// 			pipe_insetup(pipe_fd);
// 		}
// 		if (pipe(pipe_fd) == -1)
// 			exit(errno);
// 		fork_pid[i] = fork();
// 		if (fork_pid[i] == -1)
// 			exit(errno);
// 		if (fork_pid[i] == 0)//Si le pid est celui du processus enfant
// 		{
// 			printf("test entering in child process: %d\n", i);
// 			if (i <= 1)
// 			{
// 				printf("test redirect output au : %d\n", i);
// 				pipe_outsetup(pipe_fd);
// 			}
// 			printf("test de lexec au : %d\n", i);
// 			if (execve(cmds_path[i], cmds_lst[i], envp) == -1)
// 				perror("");
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	dup2(stdio[0], 0);
// 	dup2(stdio[1], 1);
// 	printf("i = %d", i);
// 	while (i <= 2)
// 	{
// 		waitpid(fork_pid[i], &exit_status, 0);
// 		i++;
// 	}
// }

static void	pipe_insetup(int *pipe_fd)
{
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}

static void	pipe_outsetup(int *pipe_fd)
{
	dup2(pipe_fd[1], 1);
	// close(pipe_fd[0]);
	close(pipe_fd[1]);
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
