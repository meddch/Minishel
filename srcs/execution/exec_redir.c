/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.cc                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mechane <mechane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:52:19 by mechane           #+#    #+#             */
/*   Updated: 2023/05/31 12:23:47 by mechane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishel.h"

int	xpand_h_doc(t_env *env, int fd_in)
{
	int		fd[2];
	char	*gnl;

	if (pipe(fd) == -1)
		return (perror("pipe"), exit(1), 0);
	gnl = expansion(env, get_next_line(fd_in));
	while (gnl)
	{
		write(fd[1], gnl, ft_strlen(gnl));
		free(gnl);
		gnl = expansion(env, get_next_line(fd_in));
	}
	return (close(fd[1]), fd[0]);
}

char	**get_filename(t_token *file, t_env *env)
{
	int		i;
	int		size;
	char	**file_name;
	
	i = -1;
	apply_exp(&file, env);
	apply_wc(&file);
	size = token_size(file);
	file_name = gc(sizeof(char *)*(size + 1), 0);
	while (file)
	{
		file_name[i] = ft_strdup(file->data);
		while (file->sub)
		{
			file_name[i] = ft_strjoin(file_name[i], file->sub->data);
			file->sub = file->sub->sub;
		}
		file = file->next;
		i++;
	}
	file_name[i] = NULL;
	return (file_name);
}


bool	dup_to(t_tree *tree, t_env *env)
{
	t_redir	*redir;
	int		fd;
	char	**file_name;
	int		to_dup;
	
	redir = (t_redir *)tree;
	to_dup = STDIN_FILENO;
	((redir->node_type & (ROUT | APPEND))) && (to_dup = STDOUT_FILENO);
	if (redir->node_type & (RIN | ROUT | APPEND))
	{
		file_name = get_filename(redir->file, env);
		if (file_name[1])
			return (printf("ambiguous redirect\n"), false); // use fd_printf and exit(1)
		if (fd = open(*file_name, redir->flags, 0664) == -1 || dup2(fd, to_dup) == -1)
			return (false); // create ft_open to handle error and fd_print error + exit(1)  // create ft-dup to handle error and exit(1)
		close(fd);
		return (true);
	}
	if (redir->file->h_doc && !redir->file->sub)
		fd = xpand_h_doc(env, redir->fd_in);
	dup2(fd, to_dup);// create ft-dup to handle error and exit(1)
	return (true);
}



void	exec_redir(t_tree *tree, t_env *env)
{
	int		status;
	pid_t	pid;
	
	pid = fork(); // fork function that protect fail
	if (pid == 0)
	{
		while (tree && tree->node_type == NODE_REDIR)
			if (dup_to(tree, env) == false)
				break ;
		exec(tree, env);
		exit(0);
	}
	waitpid(pid, &g_st, 0);
}