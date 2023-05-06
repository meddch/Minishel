/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mechane <mechane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:48:38 by mechane           #+#    #+#             */
/*   Updated: 2023/05/06 17:58:41 by mechane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "../include/minishel.h"

typedef struct s_tree
{
	int	cmd_type;
}				t_tree;

typedef struct s_connector
{
	int	cmd_type;
	t_tree *left;
	t_tree *right;
}				t_connector;

typedef struct s_subsh
{
	int	cmd_type;
	t_tree *subsh;
}				t_subsh;

typedef struct s_cmd
{
	int	cmd_type;
	t_token *list;
}				t_cmd;


t_tree *constract_block(int type, t_tree *left, t_tree *right);

#endif