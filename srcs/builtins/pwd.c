/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azari <azari@student.1337.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 05:52:20 by azari             #+#    #+#             */
/*   Updated: 2023/06/04 15:24:56 by azari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"


void	ft_putstrr(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void	pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)))
		ft_putstrr(path);
}
