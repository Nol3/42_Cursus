/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:01:49 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/27 13:01:49 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

    i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/*lst: el principio de la lista.*/
/*return (La longitud de la lista.)*/

/*Cuenta el número de nodos de una lista.*/