/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:42:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/09 20:31:52 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(t_data *all, t_token *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (all->return_val = 1);
	if (cmd->next != cmd && (cmd->next->token[2] != 'L' && cmd->next->token[2] != 'P'))
	{
		ft_dprintf(2, "minishell: pwd %s: %s\n", cmd->next->token, INV_OPT);
		ft_dprintf(2, "pwd: usage: pwd [-LP]\n");
		return (all->return_val = 2);
	}
	ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
	free(pwd);
	return (all->return_val = 0, 0);
}

int	ft_cd(t_token *cmd, t_data *all, int nodes)
{
	t_token	*cd_node;
	char	*old_dir;

	ft_dprintf(2, "nodes [%d]\n", nodes);
	if (nodes != 1 && nodes != 2)
	{
		ft_dprintf(2, "minishell: %s: %s\n", cmd->token, TOO_ARGS);
		return (all->return_val = 1);
	}
	old_dir = getcwd(NULL, 0);
	if (!old_dir)
		return (all->return_val = 1);
	if (nodes == 1 && !ft_strncmp(cmd->token, "cd\0", 3))
	{
		chdir("~/");
		update_env_cd(all, "PWD=", getcwd(NULL, 0));
		update_env_cd(all, "OLDPWD=", old_dir);
		return (all->return_val = 0);
	}
	cd_node = cmd->next;
	while (ft_strncmp(cd_node->token, "cd\0", 3))
		cd_node = cd_node->next;
	if (chdir((const char *)cd_node->next->token) == -1)
	{
		all->return_val = 1;
		perror("minishell");
		return (1);
	}
	update_env_cd(all, "OLDPWD=", old_dir);
	chdir(cd_node->token);
	update_env_cd(all, "PWD=", getcwd(NULL, 0));
	free(old_dir);
	return (all->return_val = 0);
}

int	ft_echo(t_data *all, t_token *cmd_node)
{
	int		line_flag;
	t_token	*arg;

	line_flag = 1;
	arg = cmd_node->next;
	ft_dprintf(2, "echo will print [%s]\n", arg->token);
	ft_dprintf(2, "echo will print next[%s]\n", arg->next->token);
	while (arg->token && only_n(arg->token))
	{
		line_flag = 0;
		arg = arg->next;
	}
	while (arg->type == ARGUMENT)
	{
		ft_printf("%s", arg->token);
		if (arg->next->type == ARGUMENT)
			ft_printf(" ");
		arg = arg->next;
	}
	if (line_flag)
		ft_printf("\n");
	return (all->return_val = 0, 0);
}

int	ft_unset(t_data *all, int proc, t_token *cmd_node)
{
	(void)proc;
	int		i;
	t_token	*arg;

	if (cmd_node->next->type == ARGUMENT)
		arg = cmd_node->next;
	else
		return (0);
	i = exist_in_arr(arg->token, all->c_envp, false);
	if (i > -1)
		all->c_envp[i][0] = '\0';
	i = exist_in_arr(arg->token, all->c_exp, true);
	if (i > -1)
		all->c_exp[i][0] = '\0';
	return (all->return_val = 0, 0);
}

int	ft_exit(t_data *all, int nodes, t_token *cmd_node, int fds_bak[2])
{
	(void)fds_bak;
	ft_dprintf(2, "total proc: [%d]\n", all->info->total_proc);
	if (all->info->total_proc == 1)
	{
		if (nodes == 1)
		{
			all->return_val = 0;
			exit ((int)all->return_val);
		}
		else if (nodes == 2 && !(isnt_number(all->tokens->token)))
		{
			all->return_val = ft_atoi(all->tokens->token);
			exit (all->return_val);
		}
		else if (nodes >= 2 && isnt_number(cmd_node->next->token))
		{
			all->return_val = 255;
			ft_dprintf(2, "minishell: exit: %s: numeric argument required.", all->tokens->token);
			exit (all->return_val);
		}
		else if (nodes > 2 && !(isnt_number(cmd_node->next->token)))
		{
			all->return_val = 255;
			ft_dprintf(2, "exit\nminishell: exit: too many arguments.");
			return (1);
		}
	}
	return (0);
}
