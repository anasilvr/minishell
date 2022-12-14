#include "../../include/minishell.h"


/* Exemples de chaine d'execution possible
 * file1 > echo | cat > file2 > file3 > cat | cat | cat >> file4
 *
 * sed 's/bib/lol/' file.txt > file2.txt
 *
 */

static char	*path_env_var_to_str(char **p_envp)
{
	int		i;

	i = 0;
	if (p_envp)
	{
		while (p_envp[i] != NULL)
		{
			if (strncmp(p_envp[i], "PATH=", 5) == 0)
				return (ft_strtrim(p_envp[i], "PATH="));
			i++;
		}
	}
	return (NULL);
}

static char	*recup_the_bin_path(char *bin_name, char **p_envp)
{
	char	**splitted_path;
	char	*trimmed_path;
	char	*complete_bin_path;
	int		i;

	i = 0;
	complete_bin_path = NULL;
	trimmed_path = path_env_var_to_str(p_envp);
	splitted_path = ft_split(trimmed_path, ':');
	free(trimmed_path);
	while (splitted_path[i])
	{
		complete_bin_path = ft_strjoin(splitted_path[i], "/");
		complete_bin_path = ft_strjoin_free(complete_bin_path, bin_name);
		if (access(complete_bin_path, X_OK) != -1)
		{
			free_tab(splitted_path);
			return (complete_bin_path);
		}
		i++;
		free (complete_bin_path);
	}
	free_tab(splitted_path);
	return (NULL);
}

static void	external_bin_exec(t_data *prog_data, char **argv) // argv peut etre eventuellement remplacer par le split de cmd d ana
{
	if (prog_data->cmd_lst->fork_pid != 0) // Aucun child a ce point, il devra avoir un fork pour les external exec
	{
		printf("external fork\n");
		prog_data->cmd_lst->fork_pid = fork();
		if (prog_data->cmd_lst->fork_pid == -1)
			perror("Minishell");
		else if (prog_data->cmd_lst->fork_pid != 0)
			waitpid(0, NULL, 0);
	}
	if (prog_data->cmd_lst->fork_pid == 0) // Alredy into a child process because of pipe
	{
		if (execve(prog_data->cmd_lst->path, argv, prog_data->envp_cp) == -1)
		{
			// perror("Minishell");
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd("command not found: ", 2);
			ft_putstr_fd(argv[0], 2);
			ft_putstr_fd("\n", 2);
			exit (127); //errno ne sortirait pas le bon int
		}
	}
}

void	execution_time(t_data *prog_data)
{
	char **splitted_args;

	// if () //checkfor asssing fd to good stdin stdout
	builtins_checker(prog_data, prog_data->cmd_lst);
	if (prog_data->cmd_lst->is_builtin == false)
	{
		splitted_args = ft_split(prog_data->cmd_lst->cmdline, ' ');
		prog_data->cmd_lst->path = recup_the_bin_path(splitted_args[0], prog_data->envp_cp);
		external_bin_exec (prog_data, splitted_args);
	}
}

void	execution_manager(t_data *prog_data)
{
	stdio_cpy(prog_data);
	prog_data->cmd_lst->fork_pid = -2;
	prog_data->cmd_lst->is_builtin = false;
	if (prog_data->cmd_lst != NULL)
	{
		redirect_setup(prog_data);
		if (prog_data->nb_cmds == 1)
		{
			execution_time(prog_data);
			prog_data->cmd_lst = prog_data->cmd_lst->next;
		}
		else
			prog_data->cmd_lst = job_loop(prog_data);
		/* Boucle pour les chaine de redirection infile1 > infile2 > infile3... */
		// while (prog_data->cmd_lst != NULL)
		// {
		// 	redir_manader(prog_data);

		// 	prog_data->cmd_lst = prog_data->cmd_lst->next;
		// }
	}
	reset_stdio(prog_data);
}

// OLD
// int	execution_manager(t_data *prog_data)
// {
// 	stdio_cpy(prog_data);
// 	while (prog_data->cmd_lst != NULL)
// 	{
// 		prog_data->cmd_lst->fork_pid = -2;
// 		prog_data->cmd_lst->is_builtin = false;
// 		redir_manader(prog_data);
// 		if (prog_data->cmd_lst->io_flag == PIPE) // Pipe
// 		{
// 			pipe_loop(prog_data);
// 			return (0);
// 		}
// 		else
// 			execution_time(prog_data);
// 		reset_stdio(prog_data);
// 		if (prog_data->cmd_lst != NULL)
// 			prog_data->cmd_lst = prog_data->cmd_lst->next;
// 		/* Next "if" needed for cases where i have a redirect and need to skip the next token,
// 		 * like cat < file.txt, where i dont need to execute file.txt so i pass the next token*/
// 		// if ((prog_data->cmd_lst != NULL && prog_data->cmd_lst->prev != NULL) && \
// 		// (prog_data->cmd_lst->prev->io_flag >= 4 && prog_data->cmd_lst->prev->io_flag <= 6))
// 		// 	prog_data->cmd_lst = prog_data->cmd_lst->next;
// 	}
// }
