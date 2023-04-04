/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:56:16 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/04 16:31:15 by tchalifo         ###   ########.fr       */
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

int	space_handler(char *str, int i)
{
	int	j;

	j = i;
	while (ft_isspace(str[i]) == 0 && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (i - 1);
	return (j);
}

char	*cpy_env_var(char **env, char *var)
{
	int		i;
	int		j;
	int		k;
	char	*r_var;

	i = -1;
	j = -1;
	k = -1;
	r_var = NULL;
	while (env[++i] != NULL)
	{
		if (ft_cmp_env(env[i], var, (ft_strlen(var))) == 0)
			break ;
	}
	if (env[i] != NULL)
	{
		while (env[i][++j] != '=')
			;
		r_var = malloc(sizeof(char) * (ft_strlen(&env[i][j])));
		while (env[i][++j] != '\0')
			r_var[++k] = env[i][j];
		r_var[++k] = '\0';
	}
	xfree(var);
	return (r_var);
}
