/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:56:16 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/03 14:56:18 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	quotes_len(char *line, int *j, char q)
{
	int	len;

	len = 0;
	while (line[*j] != '\0')
	{
		if (line[*j] == q)
		{
			*j += 1;
			while (line[*j + len] != '\0' && line[*j + len] != q)
				len++;
			break ;
		}
		else if (line[*j] != q)
			*j += 1;
	}
	return (len);
}
