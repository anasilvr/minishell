/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:34:45 by tchalifo          #+#    #+#             */
/*   Updated: 2023/02/20 14:21:09 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* MEMORY ZONE OF THOMAS FISHer
 * Case cmd > file --> Redirect the standard output (stdout) of cmd to a file
 * and replace all the content for the new one.
 * Case cmd >> file --> Append the standard output (stdout) of cmd to a file.
 */

#include "../../include/minishell.h"


/* La fonction effectue l'ouverture d'un fichier spécifié par un chemin d'accès en mode lecture 
 * seule. Elle prend également un flag additionnel au besoin.
 * 
 * PROTOTYPE	: int	open_to_read(char *filepath, int additional_flag);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre le chemin du fichier à ouvrir et un flag additionnel.
 * 
 * RETOUR	: Si une erreur se produit, -1 est un retour et errno est imprimé.
 * 
 * DETAILS	: Si un flag additionnel est utilisé, commenter la ligne (void) additional_flag.
 */
int	open_to_read(char *filepath, int additional_flag)
{
	(void) additional_flag;
	int	file_fd;

	if (access(filepath, R_OK) == -1) //&& errno != ENOENT)
	{
		perror(NULL);
		return (-1);
	}
	else
	{
		file_fd = open(filepath, O_RDONLY);
		if (file_fd == -1)
		{
			perror(NULL);
			return (-1);
		}
	}
	return (file_fd);
}

/* La fonction effectue l'ouverture d'un fichier spécifié par un chemin d'accès mode écriture 
 * seule. Elle prend également un flag additionnel au besoin.
 * 
 * PROTOTYPE	: int	open_to_write(char *filepath, int additional_flag);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre le chemin du fichier à ouvrir et un flag additionnel.
 * 
 * RETOUR	: Si une erreur se produit, -1 est un retour et errno est imprimé.
 * 
 * DETAILS	: Si un flag additionnel est utilisé, commenter la ligne (void) additional_flag.
 */
int	open_to_write(char *filepath, int additional_flag)
{
	//(void) additional_flag;
	int	file_fd;

	/* In case where the file exist but no have the right on it */
	if (access(filepath, W_OK) == -1 && errno == EACCES)
	{
		perror(NULL);
		return (-1);
	}
	else
		file_fd = open(filepath, O_WRONLY | additional_flag | O_CREAT, \
				S_IWUSR | S_IWGRP | S_IWOTH);
	if (file_fd == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (file_fd);
}

/* La fonction effectue l'ouverture d'un fichier spécifié par un chemin d'accès mode 
 * lecture-écriture. Elle prend également un flag additionnel au besoin.
 * 
 * PROTOTYPE	: int	open_to_readwrite(char *filepath, int additional_flag);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre le chemin du fichier à ouvrir et un flag additionnel.
 * 
 * RETOUR	: Si une erreur se produit, -1 est un retour et errno est imprimé.
 * 
 * DETAILS	: Si un flag additionnel est utilisé, commenter la ligne (void) additional_flag.
 */
int	open_to_readwrite(char *filepath, int additional_flag)
{
	//(void) additional_flag;
	
	int	file_fd;
	/* In case where the file exist but no have the right on it */
	if (access(filepath, R_OK | W_OK) == -1 && errno == EACCES)
	{
		perror(NULL);
		return (-1);
	}
	else
		file_fd = open(filepath, O_RDWR | additional_flag | O_CREAT, \
				S_IWUSR | S_IWGRP | S_IWOTH | S_IRUSR | S_IRGRP | S_IROTH);
	if (file_fd == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (file_fd);
}

int	open_handling(t_data *data)
{
	if (data->token->type == APPEND || data->token->type == REDIR_OUT || data->token->type == REDIR_IN)
	{
		if (data->token->type == APPEND) // >>
		{
			data->cmd_lst->filefd[1] = open_to_readwrite(data->token->next->token, O_APPEND);
			if (data->cmd_lst->filefd[1] == -1)
				return (-1);
		}
		else if (data->token->type == REDIR_OUT) // >
		{
			data->cmd_lst->filefd[1] = open_to_readwrite(data->token->next->token, O_TRUNC);
			if (data->cmd_lst->filefd[1] == -1)
				return (-1);
		}
		else if (data->token->type == REDIR_IN) // <
		{
			data->cmd_lst->filefd[0] = open_to_read(data->token->next->token, 0);
			if (data->cmd_lst->filefd[0] == -1)
				return (-1);
		}
		data->token = delmidnode_toklist(data->token);
		data->token = delmidnode_toklist(data->token);
	}
}

/* La fonction traite les redirections d'input (<) et d'output (>, >>) depuis la liste de tokens.
 * Elle permet l'ouverture des fichiers spécifier pour la redirection en leur attribuant chacun 
 * un file-descriptor. Les fds sont ainsi enregistrés dans les différents noeuds de la liste 
 * cmd_lst. Pour rappel, la liste "cmd_lst" regoupe chaques jobs, une par noeud.
 * La fonction permet aussi de supprimer les éléments de redirections de la liste de tokens. 
 * Ainsi, lors de la création des arguments pour chacunes des jobs de la liste de commandes, 
 * seul les commandes et leurs arguments seront présent.
 * 
 * PROTOTYPE	: void	redirect_subparsing(t_data *data);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la struct data de notre
 * programme.
 * 
 * RETOUR	: N/A
 * 
 * DETAILS	: N/A
 */
int	redirect_subparsing(t_data *data)
{
	t_tok *r_token;
	t_cmd *r_cmd;

	r_cmd = data->cmd_lst;
	while (data->token != NULL)
	{
		if (data->token->type == PIPE)
		{
			data->cmd_lst = data->cmd_lst->next;
			data->token = data->token->next;
		}
		if (open_handling(data) == -1)
		{
			return (-1);
		}
		if (data->token->next == NULL)
		{
			r_token = get_first_tok(data->token);
		}
		data->token = data->token->next;
	}
	data->token = r_token;
	data->cmd_lst = r_cmd;
	return (0);
}

// tchalifo@c2r1p11 minishell % echo salut >> file.txt > toto.sh

// tchalifo@c2r1p11 minishell % cat file.txt
// bob
// salut
// salut

// tchalifo@c2r1p11 minishell % cat toto.sh
// salut

// tchalifo@c2r1p11 minishell % echo salut >> file.txt >> toto.sh

// tchalifo@c2r1p11 minishell % cat toto.sh
// salut
// salut

// tchalifo@c2r1p11 minishell % echo salut >> file.txt > toto.sh

// tchalifo@c2r1p11 minishell % cat toto.sh
// salut

// sed 's/bib/lol/' file.txt > file2.txt