/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:34:45 by tchalifo          #+#    #+#             */
/*   Updated: 2022/11/16 15:32:25 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* MiniMan of the functions in this file.
 * PROTOTYPE:
 *   int	file_opening(char *filepath, int additional_flag)
 * PARAM VALUE:
 *   - (char *filepath) is the path to the file to be open.
 *   - (int additional_flag) is the additional flag needed for an APPEND case ">>".
 * RETURN VALUE:
 * it return the file descriptor of the file opened. If is an error with the
 * opening, it return -1 and set errno.
 *
 *
 */


/* MEMORY ZONE OF THOMAS FISH
 * Case cmd > file --> Redirect the standard output (stdout) of cmd to a file
 * and replace all the content for the new one.
 * Case cmd >> file --> Append the standard output (stdout) of cmd to a file.
 */

int	open_to_read(char *filepath)
{
	int	file_fd;

	if (access(filepath, R_OK) == -1 && errno != ENOENT)
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
			exit(errno);
		}
	}
	return (0);
}

int	open_to_write(char *filepath, int additional_flag)
{
	int	file_fd;

	if (access(filepath, R_OK | W_OK) == -1)
	{
		perror(NULL);
		exit(errno);
	}
	else
		file_fd = open(filepath, O_WRONLY | additional_flag | O_CREAT, \
				S_IWUSR | S_IWGRP | S_IWOTH | S_IRUSR | S_IRGRP | S_IROTH);
	return (file_fd);
}

/* Puisque je trouve tout les infos sur la string retourné par
 * readline dans la struct token, j'ai utilisé les champs de la
 * list chainée Token.
 * La variable type m'indique si je rencontre un chevrons < en autre qui est
 * l'enum de valeur 4.
 * Donc, ici si je rencontre un chevrons, le nom du fichier devrait
 * le précéder.
 */
void	input_setup(t_data *data)
{
	if (data->token->type == REDIR_IN)
	{
		while (data->token->next != '\0')
		{
			if (ft_strcmp(data->token->type, '<') == 0)
				break;
			data->token = data->token->next;
		}
		file_opening(data->token->prev->token, "");
	}
}

/* Puisque je trouve tout les infos sur la string créée par
 * readline dans la struct liste chainée token, j'ai utilisé les champs de
 * celle-ci.
 * La variable type m'indique si je rencontre un chevrons > en autre qui est
 * l'enum de valeur 5.
 * Donc, ici si je rencontre un chevrons, le nom du fichier devrait le suivre.
 */
void	output_setup(t_data *data)
{
	if (data->token->type == REDIR_OUT)
	{
		while (data->token->next != '\0')
		{
			if (ft_strcmp(data->token->type, '>') == 0)
				break;
			data->token = data->token->next;
		}
		file_opening(data->token->next->token, 0);
	if (data->token->type == APPEND)
	{
		while (data->token->next != '\0')
		{
			if (ft_strcmp(data->token->type, '>>') == 0)
				break;
			data->token = data->token->next;
		}
		file_opening(data->token->next->token, APPEND);
	}
	}
}

/* Case cmd << EOL --> Redirect a bunch of lines to the stdin. This is called
 * a here-document.
 * exemple:
 * cmd << EOL
 * line1
 * line2
 * EOL
 */
void	heredoc()
{
	char *content;
	int	readlen;

	readlen = 1;
	while (readlen > 0)
		content = read();

}

/* Case cmd < file --> Redirect the contents of the file to the standard
 * input (stdin) of cmd.
 */
void	redirect_from_file(char *filepath)
{

}
