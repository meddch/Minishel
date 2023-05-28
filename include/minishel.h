/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mechane <mechane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:56:44 by mechane           #+#    #+#             */
/*   Updated: 2023/05/27 19:17:43 by mechane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

# include "tokenizer.h"
# include "../libft/libft.h"
# include "parser.h"
# include "../gc/gc.h"
# include <dirent.h>

int g_es;

typedef struct v_env
{
	char			*val;
	char			*var;
	struct v_env	*next;
	int				*def;
}			t_env;
t_token	*expanand_wc(char *pattern);
#endif