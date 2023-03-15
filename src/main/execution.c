#include "../../include/minishell.h"

static char	*path_env_var_to_str(char **p_envp)
{
	int		i;

	i = 0;
	if (p_envp)
	{
		while (p_envp[i] != NULL)
		{
			if (strncmp(p_envp[i], "PATH=", 5) == 0)
				return (ft_strtrim_nofree(p_envp[i], "PATH="));
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
	xfree(trimmed_path);
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

/* La fonction permet d'executer des programmes depuis l'appel système
 * execve() en s'assurant de le faire depuis un processus enfant.
 *
 * PROTOTYPE : static void external_bin_exec(t_data *prog_data, char **argv);
 *
 * PARAMÈTRES : La fonction prend en paramètre la struct data de notre
 * programme et un tableau d'argument **argv, ceux du programme à executer.
 *
 * RETOUR : Elle ne retourne rien.
 *
 * DETAILS : Deux possibilitées offertes dans cette fonction. Premièrement, si le
 * processus est déja l'enfant du processus du shell, il passera directement
 * à execve(). Sinon, il créera un nouveau processus. Le processus
 * nouvellement parent l'attendra alors que l'enfant passera à execve().
 */
static void	external_bin_exec(t_data *prog_data, char **argv)
{
	if (prog_data->fork_pid != 0)
	{
		prog_data->fork_pid = fork();
		if (prog_data->fork_pid == -1)
			perror("Minishell");
		else if (prog_data->fork_pid != 0)
			waitpid(prog_data->fork_pid, NULL, 0);
	}
	if (prog_data->fork_pid == 0)
	{
		if (execve(prog_data->cmd_lst->path, argv, prog_data->envp_cp) == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd("command not found: ", 2);
			ft_putstr_fd(argv[0], 2);
			ft_putstr_fd("\n", 2);
			exit (127);
		}
	}
}

void	execution_time(t_data *prog_data)
{
	builtins_checker(prog_data, prog_data->cmd_lst);
	if (prog_data->cmd_lst->is_builtin == false)
	{
		prog_data->cmd_lst->path =
		recup_the_bin_path(prog_data->cmd_lst->args[0], prog_data->envp_cp);
		external_bin_exec (prog_data, prog_data->cmd_lst->args);
	}
}

void	execution_manager(t_data *prog_data)
{
	// stdio_cpy(prog_data);
	prog_data->fork_pid = -2;
	if (prog_data->cmd_lst != NULL)
	{
		prog_data->cmd_lst->is_builtin = false;
		if (prog_data->nb_pipes == 0)
		{
			exec_set(prog_data);
			execution_time(prog_data);
			reset_otherio(prog_data);
			prog_data->cmd_lst = prog_data->cmd_lst->next;
		}
		else
			prog_data->cmd_lst = jobs_loop(prog_data);
	}
	reset_stdio(prog_data);
}
