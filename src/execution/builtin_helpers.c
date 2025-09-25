/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:26:01 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/09 20:27:48 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	char	*temp;

	updated_path = ft_strjoin(search, path);
	if (!updated_path)
		return (1);
	i = get_env_index(all->c_envp, search, ft_strlen(search));
	temp = updated_path;
	free(all->c_envp[i]);
	all->c_envp[i] = temp;
	return (all->return_val = 0, 0);
}

int	isnt_number(char *str)
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
	{
		i++;
		while (arg[i] == 'n')
			i++;
		if (arg[i] == '\0')
			return (1);
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
	cmd_node = get_cmd_node(all->tokens->next, proc);
	if (!ft_strncmp(cmd, "echo", len))
		return (ft_echo(all, cmd_node), 1);
	else if (!ft_strncmp(cmd, "cd", len))
		return (ft_cd(cmd_node, all, nodes), 1);
	else if (!ft_strncmp(cmd, "pwd", len))
		return (ft_pwd(all, cmd_node), 1);
	else if (!ft_strncmp(cmd, "export", len))
		return (ft_export(all, proc, cmd_node), 1);
	else if (!ft_strncmp(cmd, "unset", len))
		return (ft_unset(all, cmd_node, proc), 1);
	else if (!ft_strncmp(cmd, "env", len))
		return (print_env(all), 1);
	return (0);
}
