#include "../../include/minishell.h"

static void	print_hd(t_hdoc *hd)
{
	while (hd != NULL)
	{
		printf("%s\n", hd->the_line);
		hd = hd->next;
	}
}

/* La fonction permet de trouver un heredoc (<<EOF) et de le traiter depuis la 
 * liste des tokens. Lorsqu'un heredoc est trouvé, la focntion write_heredoc() 
 * est appelée pour que l'utilisateur puissent entrer les données souhaitées.
 * Ensuite, le token en lien avec le heredoc est retiré ainsi que le delimiter.
 * 
 * PROTOTYPE	: void	heredoc_subparsing(t_data *data);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la structure data de notre 
 * programme.
 * 
 * RETOUR	: N/A
 * 
 * DETAILS	: La focntion pasera toutes les token pour s'assurer de traiter 
 * toutes les heredocs advenant la présence de plusieurs heredocs dans la job.
 */
void	heredoc_subparsing(t_data *data)
{
	char	*delimiter;
	// t_hdoc	*hd_data;
	t_tok	*token_ptrcpy;
	t_cmd	*cmd_pointer_keeper;

	token_ptrcpy = data->token;
	cmd_pointer_keeper = data->cmd_lst;
	while (data->token != NULL)
	{
		if (data->token->type == PIPE)
		{
			data->cmd_lst = data->cmd_lst->next;
			data->token = data->token->next;
		}
		if (data->token->type == HEREDOC)
		{
			delimiter = data->token->next->token;
			data->hd_struct = write_heredoc(delimiter, data);
			data->token = delmidnode_toklist(data->token);
			data->token = delmidnode_toklist(data->token);
			token_ptrcpy = get_first_tok(data->token);
		}
		if (data->token != NULL)
			data->token = data->token->next;
	}
	data->token = token_ptrcpy;
	data->cmd_lst = cmd_pointer_keeper;
}

static void	hd_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 4;
	}	
}

// char	*easy_readline(int buf_size)
// {
// 	char    *line;
//     char    buf[buf_size];
//     int     read_ret;

// 	write(1, ">", 1);
// 	if (g_status == 4)
// 	{
// 		xfree(line);
// 		line = NULL;
// 		g_status = 0;
// 	}
// 	else
// 	{
//     	read_ret = read(0, &buf, buf_size);
// 		printf("%d\n", read_ret);
//  		line = ft_strdup(buf);
// 	}
// 	return (line);
// }

/* La fonction permet simplement de créer la liste chainée pour stocker chaque 
 * entrée de l'utilisateur dans un nouveau node jusqu'a ce que le delimiter 
 * soit rencontré.
 * 
 * PROTOTYPE	: int	heredoc_to_pipe(t_hdoc *hd_struct);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la structure principal de 
 * notre programme ainsi que le delimiter souhaité par l'utilisateur.
 * 
 * RETOUR	: La fonction retourne la structure du heredoc remplit.
 * 
 * DETAILS	: Le delimiter, ne sera pas copié dans un node. 
 */
static char *trim_delim(const char *delim)
{
	int 	i;
	int		j;
	char	*r_delim;
	char	quote;

	i = 0;
	j = -1;
	r_delim = NULL;
	if (delim[i] == '"' || delim[i] == '\'')
	{
		quote = delim[i];
		while (delim[++i] != quote)
			;
		r_delim = malloc(sizeof(char) * i);
		i = 0;
		while (delim[++i] != quote)
			r_delim[++j] = delim[i];
		r_delim[j] = '\0';
		return (r_delim);
	}
	return ((char*)delim);
}

t_hdoc	*write_heredoc(char *delimiter, t_data *data)
{
	char	*line;
	t_hdoc	*hd_struct;
	char	*r_trim;

	r_trim = trim_delim(delimiter);
	signal(SIGINT, hd_signal_handler);
	hd_struct = NULL;
<<<<<<< HEAD
	while (g_status != 4 && (line = readline("> ")) != NULL && (ft_strcmp(ft_strtrim(delimiter, "'"), line) != 0 || ft_strcmp(ft_strtrim(delimiter, "\""), line) != 0))
=======
	while (g_status != 4 && (line = readline("> ")) != NULL
		&& ft_strncmp(r_trim, line, ft_strlen(r_trim)) != 0)
>>>>>>> 349db385ad8db91496883f24f28fc3d3776696c2
	{
		if (delimiter[0] != '\'' && delimiter[0] != '"')
			line = heredoc_dollar(data->envp_cp, line);
		hd_struct = ft_dllst_add_back(hd_struct, line);
		hd_struct = ft_dllst_add_back(hd_struct, "\n");
		if (line)
		{
			xfree(line);
			line = NULL;
		}
		// line = easy_readline(100000);
	}
	free(r_trim);
	// print_hd(hd_struct);
	return (hd_struct);
}



// t_hdoc	*write_heredoc(char *delimiter, t_data *data)
// {
// 	char	*line;
// 	t_hdoc	*hd_struct;

// 	signal(SIGINT, hd_signal_handler);
// 	printf("g_status = %d\n", g_status);
// 	if (errno != 4)
// 		line = readline("> ");
// 	printf("Hello\n");
// 	hd_struct = NULL;
// 	if (errno == 4)
// 	{
// 		xfree(line);
// 		line = NULL;
// 	}
// 	while (line != NULL && ft_strcmp(delimiter, line) != 0)
// 	{
// 		printf("%d\n", errno);
// 		if (errno == 4 || !line)
// 		{
// 			xfree(line);
// 			line = NULL;
// 			break;
// 		}
// 		line = heredoc_dollar(data->envp_cp, line);
// 		hd_struct = ft_dllst_add_back(hd_struct, line);
// 		hd_struct = ft_dllst_add_back(hd_struct, "\n");
// 		if (line)
// 		{
// 			xfree(line);
// 			line = NULL;
// 		}
// 		line = readline("> ");
// 	}
// 	// print_hd(hd_struct);
// 	return (hd_struct);
// }

/* La fonction permet, dans l'éventualité qu'un heredoc est été présent dans 
 * la série de commande, de pousser les différents ligne du heredoc dans le 
 * stdin de l'execution lui étant rattachée.
 * 
 * PROTOTYPE	: int	heredoc_to_pipe(t_hdoc *hd_struct);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la structure en liste du 
 * heredoc créé préalablement par la fonction write_heredoc().
 * 
 * RETOUR	: La fonction retourne le file descriptor du pipe pour la lecture.
 * 
 * DETAILS	: N/A
 */
int	heredoc_to_pipe(t_hdoc *hd_struct)

{
	int	hd_pipe_fd[2];
	int	hd_fork_pid;

	if (pipe(hd_pipe_fd) == -1)
		return (errno);
	hd_fork_pid = fork();
	if (hd_fork_pid == -1)
	  return (errno);
	if (hd_fork_pid == 0)
	{
		close(hd_pipe_fd[0]);
		while (hd_struct != NULL)
		{
			// write(hd_pipe_fd[1], hd_struct->the_line, ft_strlen(hd_struct->the_line));
			ft_putstr_fd(hd_struct->the_line, hd_pipe_fd[1]);
			hd_struct = hd_struct->next;
		}
		close(hd_pipe_fd[1]);
		exit(0);
	}
	close(hd_pipe_fd[1]);
	waitpid(hd_fork_pid, NULL, 0);
	return (hd_pipe_fd[0]);
}

char *heredoc_dollar(char **env , char *line)
{
    int i;
    char *r_line;
    char *r_var;

    i = 0;
    r_line = NULL;
    r_var = NULL;
    while (line [i] != '\0')
    {
        if (line[i] == '$')
        {
            if (line[++i] == '$')
                ;
            else if (line[i] == '?')
                r_line = ft_strjoin(r_line, ft_itoa(g_status));
            else if (line[--i] == '$')
            {
                while (ft_isalnum(line[++i]) == 1)
                    r_var = charjoinfree(r_var, line[i]);
                r_var = cpy_env_var(env, r_var);
                if (r_line == NULL)
                    r_line = ft_strdup(r_var);
                else
                    r_line = ft_strjoin_free(r_line, r_var);
                r_var = xfree(r_var);
            }
        }
        else
            r_line = charjoinfree(r_line, line[i++]);
    }
    return (r_line);
}
