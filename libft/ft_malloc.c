/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mechane <mechane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:55:07 by mechane           #+#    #+#             */
/*   Updated: 2023/05/05 11:57:57 by mechane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "../gc/gc.h"

void	*ft_malloc(size_t size)
{
	return (gc(size, 0));
}