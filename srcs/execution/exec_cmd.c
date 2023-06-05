/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mechane <mechane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:18:15 by mechane           #+#    #+#             */
/*   Updated: 2023/06/05 16:01:12 by mechane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishel.h"

void	apply_exp(t_token **token, t_env *env)
{
	t_token	*tmp;
	t_token *exp;
	
	tmp = *token;
	exp = NULL;
	while(tmp && (tmp->type == WORD))
	{
		add_back_tok(&exp, expand_node(env, tmp->data, (tmp->h_doc == 0)));
		while(tmp->sub)
		{
			add_back_sub(&exp, expand_sub(env, tmp->sub->data, (tmp->sub->h_doc == 0)));
			tmp->sub = tmp->sub->sub;
		}
		tmp = tmp->next;
	}
	(*token) = exp;
}

void 	apply_wc(t_token **token)
{
	t_token	*tmp;
	t_token *exp;
	
	tmp = *token;
	exp = NULL;
	while(tmp && (tmp->type == WORD))
	{
		add_back_tok(&exp, expanand_wc(tmp->data));
		while(tmp->sub)
		{
			add_back_sub(&exp, expanand_wc(tmp->sub->data));
			tmp->sub = tmp->sub->sub;
		}
		tmp = tmp->next;
	}
	(*token) = exp;
}


char	**get_cmdline(t_cmd *tree, t_env *env)
{
	t_token	*cmdlist;
	char	**cmd;
	int		i;
	int		size;
	
	i = 0;
	cmdlist = tree->list;
	apply_exp(&cmdlist, env);
	apply_wc(&cmdlist);
	size = token_size(cmdlist);
	cmd = gc(sizeof(char *)*(size + 1), 0);
	while (cmdlist)
	{
		cmd[i] = ft_strdup(cmdlist->data);
		while (cmdlist->sub)
		{
			cmd[i] = ft_strjoin(cmd[i], cmdlist->sub->data);
			cmdlist->sub = cmdlist->sub->sub;
		}
		cmdlist = cmdlist->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}
void sig_hand(int sig)
{
	if (sig == SIGINT)
	{
		write(1,"",1);
	}
	if (sig == SIGQUIT)
	{
		write(1,"Quit: 3",7);
	}
	exit(120 + sig);
}
char	**switch_env(t_env *myenv)
{
	int		i;
	int		len;
	char	**env;

	i = 0;
	len = ft_envsize(myenv);
	env = gc(sizeof(char *) * (len + 1), 0);
	env[len] = 0;
	while (myenv)
	{
		(env[i++] = ft_strjoin_sp(myenv->var,
					myenv->val, '='));
		myenv = myenv->next;
	}
	return (env);
}

void sig_ch(pid_t pid)
{
	if (pid == 0)
	{
		signal(SIGINT, sig_hand);
		signal(SIGQUIT, sig_hand);
	}
	else
		signal(SIGINT, SIG_IGN);
}

void	exec_cmd(t_cmd *tree, t_env **env)
{
	pid_t pid;
	char	**cmdline;
	char	*cmd;
	int		status;

	cmdline = get_cmdline(tree, *env);
	if (!cmdline || is_builtin(cmdline[0], cmdline, env))
		return ;
	cmd = get_cmd_path(cmdline[0], *env);
	if (!cmd)
		return (exit(1));
	pid = ft_fork();
	sig_ch(pid);
	if (pid == 0)
	{
		execve(cmd, cmdline, switch_env(*env));
		ft_printf_fd(2, " %s : command not found\n", cmdline[0]);
		exit(127);
	}
	if (wait(&status) == pid)
		check_status(status);
	(status == SIGQUIT) && (ft_putendl_fd("Quit: 3", STDOUT_FILENO));
	(status == SIGINT) && (ft_putendl_fd("", STDOUT_FILENO));
}
