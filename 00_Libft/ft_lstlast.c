/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:01:40 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/27 13:01:40 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	if (lst->next == NULL)
		return (lst);
	while (lst->next)
    {
		lst = lst->next;
    }
	return (lst);
}


/*Devuelve el último nodo de la lista.*/