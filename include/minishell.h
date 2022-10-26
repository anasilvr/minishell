#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
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
# define WTS "\033[1;95m\xF0\x9F\x90\x8CWTS$\033[a \033[0m"
# define PIPE_READ 0
# define PIPE_WRITE 1
# define WHITESPACE " \n\t\v\r\f"
# define METACHAR "|<> \n\t\v\r\f"
# define REDIRCHAR "<>"
# define QUOTES "\'\""

# define ERR_SYNTAX "Syntax error near unexpected token: "
# define ERR_CMD ": command not found"
# define ERR_OPEN ": no such file or directory"
# define ERR_ACCESS ": permission denied"

int							g_status;

typedef struct s_tok		t_tok;
typedef struct s_data		t_data;
typedef struct s_cmd		t_cmd;

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

typedef	enum e_type
{
	BUILTIN,
	CMD,
	FLAG,
	STR,
	ENVVAR,
	PIPE,
	HEREDOC,
	REDIR,
}	t_type;

typedef struct s_cmd
{
	char		*cmd; // input[0]
	char 		**args; // input[1...until pipe or EOL]
	char		*input;
	char		*output;
	int			fd_in; // Default =  STDIN_FILENO
	int			fd_out; // Default = STDOUT_FILENO
	int			err; // do i need it? can i always store on global?
	t_cmd		*prev; // first one = NULL
	t_cmd		*next; // input[first after redir];
}	t_cmd;

typedef	struct s_tok
{
	char		*token;
	t_type		type;
	int			toksize;
	t_tok		*prev;
	t_tok		*next;
}	t_tok;

typedef struct s_data
{
	char		**envp_cp;
	char		**path;
	char		*input; // return of rl_gets;
	t_tok		*token;
	int			nb_toks;
	char		*errtok; // which token returned an error, might not implement
	t_cmd		*cmd_lst; // linked list where every cmd of input is split on a node with its own arguments and flags
	int			nb_cmds; // size of cmd_lst;
	int			*pipe;
	int			nb_pipes;
	bool		heredoc_f;
	bool		syntax_err;
}	t_data;

// BUILTINS

// ENGINE

// MAIN
// exit.c
void	clean_exit(t_data *data);

// init.c
t_data	*get_data(void);
t_data	*init_data(char **envp, t_data *data);
char	**init_path(t_data *data);

// intro.c
void	print_intro(void);

// main.c
void	wtshell(t_data *data);
char	*rl_gets(void);

// PARSING
char	**backup_env(char **envp);
char	**safesplit(char const *s, char c); // split that conserves all characters, including delimiter
void	skip_whitespaces(char **str);
int		is_set(char s, char *set);

int		lexer(t_data *data, char *input);
void	valid_quotation(t_data *data);
t_tok	*tokenize(t_data *data, char *str);
int		tok_len(char *str, int len);
void	token_redir(t_tok *lst, char **str);

t_tok	*new_toklist(char *tok);
void	addback_toklist(t_tok **toklist, t_tok *new);
t_tok	*get_lasttok(t_tok *node);
int		lenght_til_match(char *str, char c);
void	id_tokens(t_tok **lst);
// SIGNALS
void	handle_signal(int sig);

void	print_toklist(t_tok **list);

#endif