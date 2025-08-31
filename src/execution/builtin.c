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

int	ft_pwd(char *cmd)
{
	char	*pwd;

	dprintf(2, "running [%s]\n", cmd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		dprintf(2, "Error with pwd\n");
	dprintf(2, "%s\n", pwd);
	free(pwd);
	return (0);
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

int	ft_cd(char *cmd, t_data *all)
{
	t_token	*cd_node;

	dprintf(2, "running [%s]\n", cmd);
	update_env_cd(all, "OLDPWD=", getcwd(NULL, 0));
	cd_node = all->tokens->next;
	dprintf(2, "token in node is [%s]\n", cd_node->token);
	dprintf(2, "env [1] is [%s]\n", all->c_envp[0]);
	while (ft_strncmp(cd_node->token, "cd", 2))
		cd_node = cd_node->next;
	chdir((const char *)cd_node->next->token);
	update_env_cd(all, "PWD=", getcwd(NULL, 0));
	return (0);
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

int	only_n(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] == '-' && str[i + 1])
		i++;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo(char **array)
{
	int	i;
	int	line_flag;

	i = 0;
	line_flag = 1;
	if (!array || !array[i])
		return (0);
	i++;
	while (only_n(array[i]) && line_flag == 0)
		i++;
	while (array[i])
	{
		ft_printf("%s", array[i]);
		if (array[i + 1])
			ft_printf(" ");
		i++;
	}
	if (line_flag)
		ft_printf("\n");
	return (0);
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
	return (0);
}

int	which_builtin(char *cmd, t_data *all, int proc)
{
	int	len;
	int	nodes;
	t_token	*cmd_node;

	len = ft_strlen(cmd);
	nodes = ft_lstsize(all->tokens, proc);
	dprintf(2, "nodes in which builtin [%d]\n", nodes);
	cmd_node = get_cmd_node(all->tokens->next, 0);
	dprintf(2, "which builder\n");
	if (!ft_strncmp(cmd, "echo\0", len))
	{
		char	**args;

		args = array_builder(all, proc);
		ft_echo(args);
		dprintf(2, "My %s \n", cmd);
		return (1);
	}
	else if (!ft_strncmp(cmd, "cd\0", len))
	{
		dprintf(2, "My %s \n", cmd);
		ft_cd(cmd, all);
		return (1);

	}
	else if (!ft_strncmp(cmd, "pwd\0", len))
	{
		dprintf(2, "My %s \n", cmd);
		ft_pwd(cmd);
		return (1);

	}
	else if (!ft_strncmp(cmd, "export\0", len))
	{
		dprintf(2, "my %s\n", cmd);
		ft_export(all, proc, cmd_node);
		return (1);

	}
	else if (!ft_strncmp(cmd, "unset\0", len))
	{
		dprintf(2, "my [%s]\n", cmd);
		ft_unset(all, proc, cmd_node);
		return (1);

	}
	else if (!ft_strncmp(cmd, "exit\0", len))
	{
		dprintf(2, "starting exit cmd\n");
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
				dprintf(2, "return_val: [%d]\n", all->return_val);
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
				dprintf(2, "exit\n");
				dprintf(2, "bash: exit: too many arguments. Jamon\n");
				return (1);
			}
		}
		return (1);

	}
	return (0);
}
