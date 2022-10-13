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

// MACROS, GLOBAL VARIABLE AND STRUCTS
# define PIPE_READ 0
# define PIPE_WRITE 1
# define WHITESPACE " \n\t\v\r\f"
# define METACHAR "|<> \n\t\v\r\f"

# define ERR_SYNTAX "Syntax error near unexpected token"
# define ERR_CMD ": command not found"
# define ERR_OPEN ": no such file or directory"
# define ERR_ACCESS ": permission denied"

int						g_status;

typedef struct s_data	t_data;
typedef struct s_cmd	t_cmd;
typedef enum e_builtins
{
	E_ECHO = 0,
	E_CD = 1,
	E_PWD = 2,
	E_EXPORT = 3,
	E_UNSET = 4,
	E_ENV = 5,
	E_EXIT = 6
}	t_builtin;

typedef struct s_cmd
{
	t_data		*ref;
	char		*cmd;
	char		**cmd_args;
	pid_t		pid;
	int			fd_src;
	int			fd_dst;
	int			end[2];
	bool		isbuiltin;
	t_builtin	e_builtin;
	t_cmd		*next;
}	t_cmd;

typedef struct s_data
{
	char			*prompt_line;
	char			**envp_cp;
	char			**path;
	size_t			index;
	t_cmd			*cmd_list;
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