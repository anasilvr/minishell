/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:27:49 by anarodri          #+#    #+#             */
/*   Updated: 2022/12/15 12:51:09 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Lower case to upper case letter conversion.
Return: If the argument is an lower-case letter,
the function returns the corresponding upper-case letter.
Otherwise, the argument is returned unchanged.
*/

#include "../libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c -= 32);
	return (c);
}
