/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:01:31 by alcarden          #+#    #+#             */
/*   Updated: 2023/04/27 13:01:31 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
	struct s_list	*final;

	if (!*lst)
		*lst = new;
	else
	{
		final = ft_lstlast(*lst);
		final->next = new;
	}
}

/*
lst: el puntero al primer nodo de una lista.
new: el puntero a un nodo que añadir a la lista.

Añade el nodo ’new’ al final de la lista ’lst’.*/