#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <dirent.h>
# include <termios.h>
# include <signal.h>
# include <errno.h>
# include <term.h>

// GLOBAL VARIABLE AND STRUCTS
//int	g_exit_status;

typedef struct s_cmd
{
	char			*cmd;
	char			**argv;
	bool			isbuiltin;
	struct t_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char			*prompt_line;
	char			**envp_cp;
	int				argc;
	size_t			index;
}	t_data;

// BUILTINS

// ENGINE

// MAIN
char	*rl_gets(void);
void	print_intro(void);
char	**backup_env(char **envp);

// PARSING

// SIGNALS

#endif