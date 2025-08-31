/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:42:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/26 23:02:24 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(t_data *all)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		dprintf(2, "Error with pwd\n");
	ft_putendl_fd(pwd, all->info->out_fd);
	free(pwd);
	return (all->return_val = 0, 0);
}

int	get_env_index(char **arr, char *to_update, int len)
{
	int	i;

	i = 0;
	while (ft_strncmp(arr[i], to_update, len) != 0)
		i++;
	return (i);
}

int	update_env_cd(t_data *all, char *search, char *path)
{
	int		i;
	char	*updated_path;

	updated_path = ft_strjoin(search, path);
	if (!updated_path)
		return (1);
	i = get_env_index(all->c_envp, search, ft_strlen(search));

	all->c_envp[i] = updated_path;
	return (0);
}

int	ft_cd(t_data *all)
{
	t_token	*cd_node;

	update_env_cd(all, "OLDPWD=", getcwd(NULL, 0));
	cd_node = all->tokens->next;
	while (ft_strncmp(cd_node->token, "cd", 2))
		cd_node = cd_node->next;
	chdir((const char *)cd_node->next->token);
	update_env_cd(all, "PWD=", getcwd(NULL, 0));
	return (all->return_val = 0, 0);
}

static int	isnt_number(char *str)
{
	if (!(*str == '-' || *str == '+' || ft_isdigit(*str)))
		return (1);
	if ((*str == '-' || *str == '+') && !ft_isdigit(str[1]))
		return (1);
	while (*(++str))
	{
		if (!(ft_isdigit(*str)))
			return (1);
	}
	return (0);
}

int	only_n(char *arg)
{
	int	i;

	i = 0;
	if (arg && arg[0] == '-' && arg[i + 1])
		i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo(t_data *all, t_token *cmd_node)
{
	int		line_flag;
	t_token	*arg;

	line_flag = 1;
	arg = cmd_node->next;
	while (arg->token && only_n(arg->token))
	{
		line_flag = 0;
		arg = arg->next;
	}
	while (arg->type == ARGUMENT)
	{
		sh_putstr(arg->token, all->info->out_fd);
		if (arg->next->type == ARGUMENT)
			sh_putstr(" ", all->info->out_fd);
		arg = arg->next;
	}
	if (line_flag)
		sh_putstr("\n", all->info->out_fd);
	return (all->return_val = 0, 0);
}

int	ft_unset(t_data *all, int proc, t_token *cmd_node)
{
	int		i;
	t_token	*arg;

	dprintf(2, "proc: [%d]\n", proc);
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

int	ft_exit(t_data *all, int nodes, t_token *cmd_node)
{
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
			dprintf(2, "bash: exit: %s: numeric argument required. Jamon\n", all->tokens->token);
			exit (all->return_val);
		}
		else if (nodes > 2 && !(isnt_number(cmd_node->next->token)))
		{
			all->return_val = 255;
			sh_putstr("exit\n", STDERR_FILENO);
			sh_putstr("bash: exit: too many arguments. Jamon\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}

int	which_builtin(char *cmd, t_data *all, int proc)
{
	int		len;
	int		nodes;
	t_token	*cmd_node;

	len = ft_strlen(cmd);
	nodes = ft_lstsize(all->tokens, proc);
	cmd_node = get_cmd_node(all->tokens->next, 0);
	if (!ft_strncmp(cmd, "echo\0", len))
		return (ft_echo(all, cmd_node), 1);
	else if (!ft_strncmp(cmd, "cd\0", len))
		return (ft_cd(all), 1);
	else if (!ft_strncmp(cmd, "pwd\0", len))
		return (ft_pwd(all), 1);
	else if (!ft_strncmp(cmd, "export\0", len))
		return (ft_export(all, proc, cmd_node), 1);
	else if (!ft_strncmp(cmd, "unset\0", len))
		return (ft_unset(all, proc, cmd_node), 1);
	else if (!ft_strncmp(cmd, "env\0", 4))
		print_env(all);
	else if (!ft_strncmp(cmd, "exit\0", len))
		return (ft_exit(all, nodes, cmd_node), 1);
	return (0);
}
