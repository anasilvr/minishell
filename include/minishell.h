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
# include <stdlib.h>


// BUILTINS
enum    e_bultins {echo, cd, pwd, export, unset, env};
void    ft_echo(char **arg, char **env, int i);
void    echo_handler(char **instruct, char **env);
int     print_directory(char **env);
char    **builtins_checker(char **instruct, char **env);
char    **cpy_env(char **envp, int line);
int     ft_cmp_env(char *str1, char *str2, size_t n);
void    print_env(char **env);
void	free_tab(char **old_tab);
int     check_env_var(char **env, char *var);
char    **unset_handler(char **env, char *var);
char    **cpy_unset(char **env, int line);
char    **export_handler(char **instruct, char **env);

// ENGINE

// MAIN
char	*rl_gets(void);
void	print_intro(void);

// PARSING
int     ft_cmp_builtin(const char *str1, const char *str2, size_t n);
int     check_n(char *intruct);
int     export_pars(char *n_var, char **env);
int     check_echo_var(char *instruct, char **env);
int     env_dup(char *n_var, char **env);


// SIGNALS

#endif