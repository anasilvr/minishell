/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:10:01 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/03 11:11:46 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* La fonction permet de dupliquer les descripteurs de fichier standard du 
 * système pour en garder une copie.
 * 
 * PROTOTYPE	: void	stdio_cpy(t_data *prog_data);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la structure data de notre 
 * programme.
 * 
 * RETOUR	: N/A
 * 
 * DETAILS	: N/A
 */
void	stdio_cpy(t_data *data)
{
	data->stdio[0] = dup(0);
	data->stdio[1] = dup(1);
	data->stdio[2] = dup(2);
}

/* La fonction permet de rétablir les descripteurs de fichier standard 
 * original a notre programme.
 * 
 * PROTOTYPE	: void	reset_stdio(t_data *data);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la structure data de notre 
 * programme.
 * 
 * RETOUR	: N/A
 * 
 * DETAILS	: N/A
 */
void	reset_stdio(t_data *data)
{
	dup2(data->stdio[0], 0);
	dup2(data->stdio[1], 1);
	dup2(data->stdio[2], 2);
}

/* La fonction permet de rétablir d'autres descripteurs de fichier que notre 
 * programme aurait altéré.
 * 
 * PROTOTYPE	: reset_otherio(t_data *data);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la structure data de notre 
 * programme.
 * 
 * RETOUR	: N/A
 * 
 * DETAILS	: Les descripteurs de fichier pour la gestion de l'ouverture de 
 * fichier pour les redirections sont réinitialisés ici.
 */
void	reset_otherio(t_data *data)
{
	if (data->cmd_lst->filefd[0] != -2)
		close(data->cmd_lst->filefd[0]);
	if (data->cmd_lst->filefd[1] != -2)
		close(data->cmd_lst->filefd[1]);
}
