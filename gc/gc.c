/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mechane <mechane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:47:40 by mechane           #+#    #+#             */
/*   Updated: 2023/05/05 11:37:40 by mechane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gc.h"

void	*gc(size_t size, int fr_flag)
{
	static t_gc	*gc;
	void		*address;
	
	if (fr_flag)
		free_gc(&gc);
	else
	{
		address = malloc(size);
		if (!address)
		{
			free_gc(&gc);
			return (exit(1), NULL);
		}
		return (address);
	}
	return (NULL);
}

t_gc	*new_gc (void *ptr)
{
	t_gc	*new;

	new = malloc(sizeof(t_gc));
	if (!new)
		return (NULL);
	new->address = ptr;
	new->next = NULL;
	return (new);
}

void	gcadd_front(t_gc **gc, t_gc *new)
{
	if (!*gc)
		return ;
	new->next = *gc;
	*gc = new;
}
void	free_gc(t_gc **gc)
{
	t_gc	*tmp;

	while (*gc)
	{
		tmp = *gc;
		*gc = (*gc)->next;
		free(tmp->address);
		free(tmp);
		tmp = NULL;
	}
	gc = NULL;
}
