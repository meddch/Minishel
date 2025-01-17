/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mechane <mechane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:54:14 by mechane           #+#    #+#             */
/*   Updated: 2023/06/06 16:21:02 by mechane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishel.h"

void	exec(t_tree *tree, t_env **env)
{
	signal(SIGINT, SIG_IGN);
	if (!tree)
		return ;
	if (tree->node_type == NODE_AND || (tree->node_type == NODE_OR))
		exec_oper(tree, env);
	else if (tree->node_type == NODE_PIPE)
		exec_pipe(tree, env);
	else if (tree->node_type == NODE_SUBSH)
		exec_subsh(tree, env);
	else if (tree->node_type == NODE_REDIR)
		exec_redir(tree, env);
	else if (tree->node_type == NODE_CMD)
		exec_cmd((t_cmd *)tree, env);
}
