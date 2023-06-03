/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mechane <mechane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:56:44 by mechane           #+#    #+#             */
/*   Updated: 2023/06/03 22:37:12 by mechane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

# include "builtins.h"
# include "tokenizer.h"
# include "expander.h"
# include "execution.h"
# include "parser.h"
# include "../libft/libft.h"
# include "../gc/gc.h"
# include "../gnl/get_next_line.h"
#include <signal.h>

int g_st;
void	*inter_handler(void);
#endif