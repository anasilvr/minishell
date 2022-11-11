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
# include <stdlib.h>

// MACROS, GLOBAL VARIABLE AND STRUCTS
# define WTS "\033[1;95m\xF0\x9F\x90\x8CWTS$\033[a \033[0m"
# define PIPE_READ 0
# define PIPE_WRITE 1
# define WHITESPACE " \n\t\v\r\f"
# define METACHAR "|<>"
# define QUOTES "\'\""

# define ERR_QUOTES "Error: Unclosed quotes. Try again." // $? = 1
# define ERR_SYNTAX "Syntax error near unexpected token" // $? = 258
# define ERR_CMD ": command not found" // $? = 127
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

typedef enum e_type
{
	NOTSET,
	WORD,
	PIPE,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	DOLLAR,
	D_EMPTY,
	D_PID,
	D_RETURN,
	INVALID,
}	t_type;

typedef struct s_cmd
{
	char		*cmdline; // input[0 - pipe or EOL]
	char		*path;
	int			fd[2]; // Default =  STDIN_FILENO // to be changed depending on token list
	int			err; // do i need it? can i always store on global?
	bool		expand;
	bool		heredoc;
	t_cmd		*prev; // first one = NULL
	t_cmd		*next; // input[first after redir];
}	t_cmd;

typedef struct s_tok
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
	char		*pwd;
	char		*input;
	t_tok		*token;
	char		*err_tok;
	int			nb_toks;
	t_cmd		*cmd_lst; // linked list where every cmd of input is split on a node with its own arguments and flags
	int			nb_cmds; // size of cmd_lst;
	int			nb_pipes;
	int			syntax_err;
}	t_data;

// BUILTINS
enum	e_bultins {echo, cd, pwd, export, unset, env};
void	ft_echo(char **arg, char **env, int i);
void	echo_handler(char **instruct, char **env);
int		print_directory(char **env);
char	**builtins_checker(char **instruct, char **env);
char	**cpy_env(char **envp, int line);
int		ft_cmp_env(char *str1, char *str2, size_t n);
void	print_env(char **env);
void	free_tab(char **old_tab);
int		check_env_var(char **env, char *var);
char	**unset_handler(char **env, char *var);
char	**cpy_unset(char **env, int line);
char	**export_handler(char **instruct, char **env);

// ENGINE

// MAIN
// exit.c
void	clean_exit(t_data *data);
void	reset(t_data *data);

// init.c
t_data	*get_data(void);
t_data	*init_data(char **envp, t_data *data);
char	**init_path(t_data *data);
char	**backup_env(char **envp);

// intro.c
void	print_intro(void);

// list_utils.c
t_tok	*new_toklist(char *tok);
void	addback_toklist(t_tok **toklist, t_tok *new);
t_tok	*get_lasttok(t_tok *node);
void	del_token(t_tok *lst);
void	free_toklist(t_tok *lst);

// main.c
void	wtshell(t_data *data);
char	*rl_gets(void);
void	print_intro(void);

// PARSING

int		ft_cmp_builtin(const char *str1, const char *str2, size_t n);
int		check_n(char *intruct);
int		export_pars(char *n_var, char **env);
int		check_echo_var(char *instruct, char **env);
int		env_dup(char *n_var, char **env);

//lexer_utils.c
void	skip_whitespaces(char **str);
int		is_set(char s, char *set);
void	print_toklist(t_tok **list);

//lexer.c
void	lexer(t_data *data, char *input);
t_tok	*tokenize(t_data *data, char *str);

// parser.c
int		parser(t_data *data);

//token_utils.c
int		tok_len(char *str, int len);
int		lenght_for_dollar(char *str);
int		lenght_til_set(char *str, char *set);
int		lenght_til_match(char *str, char c);

//token_check.c
int		id_tokens(t_tok **list, t_data *data);
int		is_redir(char *tok);
int		is_valid(char *tok);
void	verify_dollartype(t_tok **list);

// SIGNALS
void	handle_signal(int sig);

//extra
char	**safesplit(char const *s, char c); // split that conserves all characters

#endif