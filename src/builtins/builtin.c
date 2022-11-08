
#include "minishell.h"

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

static int	external_cmds_exec(char **cmd, char **envp)
{
	if (execve(cmd[0], cmd, envp) == -1)
	{
		// Need a standard for exit function after error (clear mem, ect..)
		perror(NULL);
		ft_putstr_fd(strerror(errno), 2);
		// exit(errno);
	}
}

char **builtins_checker(char **instruct, char **env)
{
	int i;

	i = 0;
	while (instruct[i] != NULL)
	{
		if (ft_cmp_builtin(instruct[i], "echo", 4) == 0)
		{
			printf("echo détecté\n");
			echo_handler(instruct, env);
            break ;
		}
		else if (ft_cmp_builtin(instruct[i], "pwd", 3) == 0)
		{
			printf("pwd détecté\n");
			print_directory(env);
            break ;
		}
		else if (ft_cmp_builtin(instruct[i], "export", 6) == 0 && instruct[i + 1] != NULL)
		{
			printf("export détecté\n");
			env = export_handler(instruct, env);
			break ;
		}
		else if (ft_cmp_builtin(instruct[i], "env", 3) == 0)
		{
			print_env(env);
			break ;
		}
		else if (ft_cmp_builtin(instruct[i] , "unset", 5) == 0 && instruct[i + 1] != NULL)
		{
			env = unset_handler(env, instruct[++i]);
			break ;
		}
		else if (ft_cmp_builtin(instruct[i], "exit", 4) == 0)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			external_cmds_exec(instruct, env);
		}
		i++;
	}
	return(env);
}
