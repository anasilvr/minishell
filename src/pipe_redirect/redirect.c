/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:34:45 by tchalifo          #+#    #+#             */
/*   Updated: 2022/11/07 09:44:21 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* Case cmd > file --> Redirect the standard output (stdout) of cmd to a file.
 * Case cmd >> file --> Append stdout of cmd to a file.
 * So i need
 * - A flag for if is stdin (1) or stderr (2).
*/
void	redirect_to_file(char *filepath)
{

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
		content = read()


}

/* Case cmd < file --> Redirect the contents of the file to the standard
 * input (stdin) of cmd.
 */
void	redirect_from_file(char *filepath)
{

}
