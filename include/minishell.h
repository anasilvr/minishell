#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./libft/GNL/get_next_line.h"
// # include "./libdll/doubly_linked_list.h"
# include <readline/readline.h>
# include <readline/history.h>
// # include "./readline/readline.h"
// # include "./readline/history.h" 
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
# include <unistd.h>

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

# define READ_ENDPIPE 0
# define WRITE_ENDPIPE 1

extern volatile int	g_status;

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
	D_EXPAND,
	D_LITERAL,
	D_RETURN,
	INVALID,
}	t_type;

typedef struct s_tok	t_tok;
typedef struct s_data	t_data;
typedef struct s_cmd	t_cmd;
typedef struct s_hdoc	t_hdoc;

typedef struct s_cmd
{
	char		*cmdline;
	char		**args;
	char		*path;
	int			cmdiofd[2];
	int			filefd[2];
	int			pipefd[2];
	int			err;
	int			io_flag;
	bool		is_builtin;
	char		*hd_delimiter;
	int			expand;
	t_cmd		*prev;
	t_cmd		*next;
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
	char		*pwd;
	char		*input;
	t_tok		*token;
	t_cmd		*cmd_lst;
	t_hdoc		*hd_struct;
	int			nb_cmds;
	int			nb_pipes;
	int			syntax_err;
	int			stdio[3];
	bool		heredoc;
	int			fork_pid;
	bool		tester;
}	t_data;

typedef struct s_hdoc
{
	char			*the_line;
	struct s_hdoc	*next;
	struct s_hdoc	*previous;
}	t_hdoc;

// FUNCTIONS
// BUILTINS
enum	e_bultins {echo, cd, pwd, export, unset, env};
void	ft_echo(char **cmd, char **env, int i);
void	echo_handler(char **instruct, t_data *data);
void	builtins_checker(t_data *data, t_cmd *cmd);
void	pwd_handler(char **instruct, t_data *data);
void	unset_handler(char **intruct, t_data *data);
void	export_handler(char **instruct, t_data *data);
void	env_handler(char **instruct, t_data *data);
void	cd_handler(char **instruct, t_data *data);
char	**cpy_env(char **envp, int line);
int		ft_cmp_env(char *str1, char *str2, size_t n);
void	free_tab(char **old_tab);
void	print_env_var(char **env, char *var);
void	print_env(char **env);
int		check_env_var(char **env, char *var);
char	**add_var(char **env, char *n_var);
void	help_handler(char **instruct, t_data *data);
void	man_yoyo_ma(char **instruct, t_data *data);

//redirection.c
void	redirect_parsing(char *line, int *file_fd);
int		open_to_read(char *filepath, int additional_flag);
int		open_to_readwrite(char *filepath, int additional_flag);
int		redirect_subparsing(t_data *data);

//redirection_utils.c
int		first_word_len(char *str);
int		*init_itab(int init_value, int init_size);

//heredoc.c
void	heredoc_subparsing(t_data *data);
t_hdoc	*write_heredoc(char *delimiter, t_data *data);
char	*heredoc_dollar(char **env, char *line);
int		heredoc_to_pipe(t_hdoc *hd_struct);
t_hdoc	*ft_dllst_new(char *str);
t_hdoc	*ft_dllst_add_back(t_hdoc *p_lst, char *str);
void	ft_dllst_delone(t_hdoc *p_lst);
void	ft_dllst_clear(t_hdoc *p_lst);
void	ft_dllst_secure_del(t_hdoc *p_lst);
bool	ft_dllst_isempty(t_hdoc *p_lst);
int		ft_dllst_size(t_hdoc *p_lst);
void	ft_dllst_print_single_node(t_hdoc *p_lst);
void	ft_dllst_print_lst(t_hdoc *p_lst);
t_hdoc	*ft_dllist_go_to_left(t_hdoc *p_lst);
t_hdoc	*ft_dllist_go_to_right(t_hdoc *p_lst);

//io.c
void	stdio_cpy(t_data *data);
void	reset_stdio(t_data *data);
void	reset_otherio(t_data *data);

// exec.c
void	execution_manager(t_data *prog_data);
void	execution_time(t_data *prog_data);
t_cmd	*jobs_loop(t_data *data);

// exec_utils.c
void	exec_set(t_data *data);

// MAIN
// exit.c
void	clean_exit(t_data *data);
void	free_cmdlist(t_cmd *lst);
void	reset(t_data *data);
void	delnode_toklist(t_tok *token_lst);
t_tok	*delmidnode_toklist(t_tok *node_to_remove);

// init.c
t_data	*get_data(void);
t_data	*init_data(char **envp, t_data *data);
char	**init_path(t_data *data);
char	**backup_env(char **envp);

// list_utils.c
t_tok	*new_toklist(char *tok);
void	addback_toklist(t_tok **toklist, t_tok *new);
t_tok	*get_lasttok(t_tok *node);
void	del_token(t_tok *lst);
void	free_toklist(t_tok *lst);
t_tok	*get_first_tok(t_tok *node);

// main.c
void	wtshell(t_data *data);
void	readline_exit(t_data *data);
char	*rl_gets(void);

// print_utils.c
void	print_intro(void);
void	print_toklist(t_tok *list);
void	print_cmdlines(t_cmd *list);
void	cmdlist_details(t_cmd *cmdlst);

// PARSING
int		ft_cmp_builtin(const char *str1, const char *str2, size_t n);
int		check_n(char *intruct);
int		export_pars(char *n_var, char **env);
int		env_dup(char *n_var, char **env);
char	*var_trim(char *n_var);
int		ft_free_strlen(char *str);

//lexer.c and lexer_utils.c
void	lexer(t_data *data, char *input);
int		check_syntax(t_tok **list);
t_tok	*tokenize(t_data *data, char *str);
void	skip_whitespaces(char **str);
void	skip_meta(char **str);
int		is_set(char s, char *set);
bool	is_empty(char *str);

// parser.c and parser_utils.c
int		parser(t_data *data);
t_cmd	*create_cmdlist(t_data *data);
t_cmd	*new_cmdline(char *line);
void	addback_cmdline(t_cmd **cmdlist, t_cmd *line);
t_cmd	*get_lastcmd(t_cmd *node);

//token_utils.c
int		tok_len(char *str, int len);
int		length_for_dollar(char *str);
int		length_til_set(char *str, char *set);
int		length_til_match(char *str, char c);

//token_check.c
int		id_tokens(t_tok **list, t_data *data);
int		is_redir(char *tok);
int		is_valid(char *tok);
void	verify_dollartype(t_tok **list);

//extra
char	*ft_strjoin_free2(char const *s1, char const *s2);
char	*charjoinfree(const char *s1, const char c);

//line handler
int		space_handler(char *str, int i);
char	*double_quote_handler(char *line, char **env, int* j);
char	*dollar_handler(char *cmd, char **env, int *j);
char	*cpy_env_var(char **env, char *var);
char	*single_quotes_handler(char *line, int *j);
void	treat_line(t_tok **tok, char **env_cp);
int		quotes_len(char *line, int *j, char q);

//bonus tester
char	*tester(void);
void	man_yoyo_ma(char **instruct, t_data *data);

#endif