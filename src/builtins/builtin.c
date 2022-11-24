#include "minishell.h"
/*
static int	external_cmds_exec(char **cmd, char **envp)
{
	if (execve(cmd[0], cmd, envp) == -1)
	{
		// Need a standard for exit function after error (clear mem, ect..)
		perror(NULL);
		ft_putstr_fd(strerror(errno), 2);
		// exit(errno);
	}
	return (0);
}*/

int	ft_cmp_builtin(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;

	i = -1;
	if (n == 0)
		return (-1);
	while (++i < (n - 1) && str1[i] == str2[i] &&
        (str1[i] != '\0' && str2[i] != '\0'))
		;
    if (str2[i + 1] == '\0' && str1[i + 1] == '\0')
        return (0);
	return (-1);
}

void	exit_handler(char **instruct)
{
    if (ft_cmp_builtin(instruct[0], "exit", 4) == 0)
		exit(EXIT_SUCCESS);
}

int builtins_checker(t_data *data, t_cmd *cmd)
{
	char 	**instruct;
	int		i;

	instruct = NULL;
	i = -1;
	instruct = ft_split(cmd->cmdline, 0x20);
	echo_handler(instruct, data, cmd->expand);
	pwd_handler(instruct);
	env_handler(instruct, data);
	cd_handler(instruct, data);
	export_handler(instruct, data);
	unset_handler(instruct, data);
	exit_handler(instruct);
	while (instruct[++i] != NULL)
		xfree(instruct[i]);
	xfree(instruct);
	return (-1);
}