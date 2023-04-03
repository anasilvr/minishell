/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:47:35 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/03 09:26:58 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*heredoc_dollar_conditionner(int *i, char **env, char *line)
{
	char	*r_line;
    char	*r_var;
	
	r_line = NULL;
    r_var = NULL;
	if (line[*i] == '$')
	{
		if (line[++*i] == '$')
			;
		else if (line[*i] == '?')
			r_line = ft_strjoin(r_line, ft_itoa(g_status));
		else if (line[--*i] == '$')
		{
			while (ft_isalnum(line[++*i]) == 1)
				r_var = charjoinfree(r_var, line[*i]);
			r_var = cpy_env_var(env, r_var);
			if (r_line == NULL)
				r_line = ft_strdup(r_var);
			else
				r_line = ft_strjoin_free(r_line, r_var);
			r_var = xfree(r_var);
		}
	}
	else
		r_line = charjoinfree(r_line, line[*i++]);
	return (r_line);
}

char	*heredoc_dollar(char **env, char *line)
{
    int		i;
    char	*r_line;

    i = 0;
    r_line = NULL;
    while (line [i] != '\0')
    {
       r_line = heredoc_dollar_conditionner(&i, env, line);
    }
    return (r_line);
}



// char	*heredoc_dollar(char **env, char *line)
// {
//     int		i;
//     char	*r_line;
//     char	*r_var;

//     i = 0;
//     r_line = NULL;
//     r_var = NULL;
//     while (line [i] != '\0')
//     {
//         if (line[i] == '$')
//         {
//             if (line[++i] == '$')
//                 ;
//             else if (line[i] == '?')
//                 r_line = ft_strjoin(r_line, ft_itoa(g_status));
//             else if (line[--i] == '$')
//             {
//                 while (ft_isalnum(line[++i]) == 1)
//                     r_var = charjoinfree(r_var, line[i]);
//                 r_var = cpy_env_var(env, r_var);
//                 if (r_line == NULL)
//                     r_line = ft_strdup(r_var);
//                 else
//                     r_line = ft_strjoin_free(r_line, r_var);
//                 r_var = xfree(r_var);
//             }
//         }
//         else
//             r_line = charjoinfree(r_line, line[i++]);
//     }
//     return (r_line);
// }

// static char	*heredoc_dollar_condition(int *i, char *line, char *r_line, char **env)
// {
// 	char	*r_var;

// 	r_var = NULL;
// 	if (line[*i] == '$')
// 	{
// 		if (line[++*i] == '$')
// 			;
// 		else if (line[*i] == '?')
// 			r_line = ft_strjoin(r_line, ft_itoa(g_status));
// 		else if (line[--*i] == '$')
// 		{
// 			while (ft_isalnum(line[++*i]) == 1)
// 				r_var = charjoinfree(r_var, line[*i]);
// 			r_var = cpy_env_var(env, r_var);
// 			if (r_line == NULL)
// 				r_line = ft_strdup(r_var);
// 			else
// 				r_line = ft_strjoin_free(r_line, r_var);
// 			r_var = xfree(r_var);
// 		}
// 	}
// 	else
// 		r_line = charjoinfree(r_line, line[*i++]);
// 	return (r_line);
// }

// char	*heredoc_dollar(char **env, char *line)
// {
// 	int		i;
// 	char	*r_line;

// 	i = 0;
// 	r_line = NULL;
// 	while (line[i] != '\0')
// 	{
// 		r_line = heredoc_dollar_condition(&i, line, r_line, env);
// 	}
// 	return (r_line);
// }

char	*trim_delim(const char *delim)
{
	int		i;
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
	return (ft_strdup(delim));
}

void	hd_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 4;
	}	
}
