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
	t_tok	*tok_pointer_keeper;
	t_cmd	*cmd_pointer_keeper;

	tok_pointer_keeper = data->token;
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
			tok_pointer_keeper = get_first_tok(data->token);
		}
		if (data->token != NULL)
			data->token = data->token->next;
	}
	data->token = tok_pointer_keeper;
	data->cmd_lst = cmd_pointer_keeper;
}

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
t_hdoc	*write_heredoc(char *delimiter, t_data *data)
{
	char	*line;
	t_hdoc	*hd_struct;

	line = readline("> ");
	hd_struct = NULL;
	while (ft_strcmp(delimiter, line) != 0)
	{
		line = heredoc_dollar(data->envp_cp, line);
		hd_struct = ft_dllst_add_back(hd_struct, line);
		hd_struct = ft_dllst_add_back(hd_struct, "\n");
		if (line)
		{
			xfree(line);
			line = NULL;
		}
		line = readline("> ");
	}
	// print_hd(hd_struct);
	return (hd_struct);
}

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
