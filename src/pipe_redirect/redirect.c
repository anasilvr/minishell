/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:34:45 by tchalifo          #+#    #+#             */
/*   Updated: 2023/02/14 11:01:12 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* MiniMan of the functions in this file.
 * PROTOTYPE:
 *    int	redirect_parsing(char *line, int **file_fd);
 * The function determines if there is a redirect and if so, which type(s)
 * should be processed for a job node. It's return nothing, but change the
 * value(s) of the pointed value of int **file_fd. Resulting in an attribution
 * of fd to the opened file(s).
 *
 * PROTOTYPE:
 *     static int	open_to_read(char *filepath, int *additional_flag);
 * Simply attribute a file descriptor to open a file in read only mode and
 * return the fd value. If an error occuring, -1 is return and errno is print.
 *
 * PROTOTYPE:
 *     static int open_to_readwrite(char *filepath, int *additional_flag);
 * Simply attribute a file descriptor to open a file in read/write mode and
 * return the fd value. If an error occuring, -1 is return and errno is print.
*/

/* MEMORY ZONE OF THOMAS FISHer
 * Case cmd > file --> Redirect the standard output (stdout) of cmd to a file
 * and replace all the content for the new one.
 * Case cmd >> file --> Append the standard output (stdout) of cmd to a file.
 */

int	open_to_read(char *filepath, int additional_flag)
{
	int	file_fd;

	(void) additional_flag;

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

int	open_to_write(char *filepath, int additional_flag)
{
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

int	open_to_readwrite(char *filepath, int additional_flag)
{
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

// static int	redirect_creation(char *line, int type, int *i)
// {
// 	char	*redirect_filename;
// 	int		filename_len;
// 	int		fd; //0 == fdin, 1 == fdout

// 	filename_len = first_word_len(&line[(*i)]);
// 	redirect_filename = ft_substr(&line[(*i)], 0, filename_len);
// 	fd = -2;
// 	if (type == 0)
// 		fd = open_to_read(redirect_filename, 0);
// 	else if (type == 1)
// 		fd = open_to_readwrite(redirect_filename,O_TRUNC);
// 	else if (type == 2)
// 		fd = open_to_readwrite(redirect_filename, O_APPEND);
// 	(*i) += filename_len;
// 	return (fd);
// }


// void	redirect_parsing(char *line, int *file_fd)
// {
// 	int	i;

// 	i = 0;
// 	while(line[i] != '\0')
// 	{
// 		if (line[i] == '>' && line[i + 1] != '>')
// 		{
// 			if (line[++i] == ' ')
// 				i++;
// 			file_fd[1] = redirect_creation(line, 1, &i);
// 			// A PARTIR DICI JAI PASSE TOUT LA REDIRECTION
// 		}
// 		else if(line[i] == '>' && line[i + 1] == '>')
// 		{
// 			if (line[++i] == ' ')
// 				i++;
// 			file_fd[1] = redirect_creation(line, 2, &i);
// 			// A PARTIR DICI JAI PASSE TOUT LA REDIRECTION
// 		}
// 		else if(line[i] == '<')
// 		{
// 			if (line[++i] == ' ')
// 				i++;
// 			file_fd[0] = redirect_creation(line, 0, &i);
// 			// A PARTIR DICI JAI PASSE TOUT LA REDIRECTION
// 		}
// 		else
// 			i++;
// 	}
// }

//Probleme avec cela, si le heredoc est en plein milieux ca va enlever la suite... cat < infile >> outfile  ..>>infile ne sera plus..
char	*redirect_trim(char *line)
{
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	len = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0')
		{
			if (line[i] == '>' || (line[i] == '>' && line[i + 1] == '>') || line[i] == '<')
			{
				if (line[i] == '>' && line[i + 1] == '>')
					i += 2;
				else
					i++;
				while (line[i] == ' ')
					i++;
				break;
			}
			if (start == 0 && i != 0 && len < 1)
				start = i;
			len++;
			i++;
		}
		while (line[i] != '\0' && line[i++] != ' ')
			;
	}
	return (ft_strtrim(ft_substr(line, start, len), " "));
}
// NEED TO CHECK FOR FREE OLD LINE POINTER






















//OLD
// void	redirect_setup(t_data *prog_data)
// {
// 	int	open_additionals_flags[1];
// 	redirect_parsing(prog_data);

// 	// if (prog_data->cmd_lst->io_flag == 3) //if is a heredoc
// 	// 	prog_data->hd_struct = write_heredoc(char *delimiter); //Need to know where is stored the delimiter

// 	if (prog_data->cmd_lst->io_flag == 4) // input redirect <
// 	{
// 		// Condition pour gerer les redirections semblable.
// 		if (prog_data->cmd_lst->filefd[0] != -2)
// 		{
// 			close (prog_data->cmd_lst->filefd[0]);
// 		}
// 		prog_data->cmd_lst->filefd[0] = open_to_read \
// 		(prog_data->cmd_lst->next->args[0], open_additionals_flags);
// 	}
// 	else if (prog_data->cmd_lst->io_flag == 5) // output redirect >
// 	{
// 		open_additionals_flags[0] = O_TRUNC;
// 		// Condition pour gerer les redirections semblable.
// 		if (prog_data->cmd_lst->filefd[1] != -2)
// 		{
// 			close (prog_data->cmd_lst->filefd[1]);
// 		}
// 		prog_data->cmd_lst->filefd[1] = open_to_readwrite \
// 		(prog_data->cmd_lst->next->args[0], open_additionals_flags);
// 	}
// 	else if (prog_data->cmd_lst->io_flag == 6) // output redirect in append mode >>
// 	{
// 		open_additionals_flags[0] = O_APPEND;
// 		// Condition pour gerer les redirections semblable.
// 		if (prog_data->cmd_lst->filefd[1] != -2)
// 		{
// 			close (prog_data->cmd_lst->filefd[1]);
// 		}
// 		prog_data->cmd_lst->filefd[1] = open_to_readwrite \
// 		(prog_data->cmd_lst->next->args[0], open_additionals_flags);
// 	}
// }

// TENTATIVE DE TPIUT FAIRE A LA MEME PLAC\E...........
// t_cmd *goto_lastnode(t_cmd *cmd_lst)
// {
// 	while (cmd_lst->next != NULL && cmd_lst->next->io_flag == 1) // Temps que je ne suis pas au dernier = node et que ce dernier est une commande.
// 		cmd_lst = cmd_lst->next;
// 	return (cmd_lst);
// }

// t_cmd *goto_firstnode(t_cmd *cmd_lst)
// {
// 	while (cmd_lst->prev != NULL && cmd_lst->next->io_flag == 1) // Temps que je ne suis pas au premier node et que ce premier est une commande.
// 		cmd_lst = cmd_lst->prev;
// 	return (cmd_lst);
// }

// void	input_redirection(t_cmd *cmd_lst)
// {
// 	int	open_additionals_flags[1];

// 	open_additionals_flags[0] = NULL;

// 	cmd_lst->filefd[0] = open_to_read (cmd_lst->args[0], open_additionals_flags);
// 	if (cmd_lst->next == NULL || cmd_lst->next)
// 	{
// 		cmd_lst = goto_firstnode(cmd_lst);
// 		dup2(cmd_lst->next->filefd[0], 0);
// 	}
// 	dup2(cmd_lst->next->filefd[0], 0);
// 	close(cmd_lst->filefd[0]);
// }

// void	redirect_setup(t_data *prog_data)
// {
// 	int	open_additionals_flags[1];
// 	while (prog_data->cmd_lst->next != NULL)
// 	{
// 		if (prog_data->cmd_lst->io_flag == 4) //if is an input redirect <
// 			input_redirection(prog_data->cmd_lst);

// 	}
// 	// if (prog_data->cmd_lst->io_flag == 3) //if is a heredoc
// 	// 	prog_data->hd_struct = write_heredoc(char *delimiter); //Need to know where is stored the delimiter
// 	if (prog_data->cmd_lst->io_flag == 4) //if is an input redirect <
// 		input_redirection(prog_data->cmd_lst);

// 	else if (prog_data->cmd_lst->io_flag == 5) //if is an output redirect > (Open file and put the fd into struct in int *cmdio_fd)
// 	{
// 		open_additionals_flags[0] = O_TRUNC;
// 		prog_data->cmd_lst->filefd[1] = open_to_readwrite (prog_data->cmd_lst->args[0], open_additionals_flags);

// 	}
// 	else if (prog_data->cmd_lst->io_flag == 6) //if is an output redirect in append mode >> (Open file and put the fd into struct in int *cmdio_fd)
// 	{
// 		open_additionals_flags[0] = O_APPEND;
// 		prog_data->cmd_lst->filefd[1] = open_to_readwrite (prog_data->cmd_lst->args[0], open_additionals_flags);

// 	}
// }
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