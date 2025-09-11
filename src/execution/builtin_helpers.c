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

#include "../inc/minishell.h"

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
		i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

int	which_builtin(char *cmd, t_data *all, int proc, int fds_bak[2])
{
	int	len;
	int	nodes;
	t_token	*cmd_node;

  dprintf(2, "my builtins\n");
	len = ft_strlen(cmd);
	nodes = ft_lstsize(all->tokens, proc);
	cmd_node = get_cmd_node(all->tokens->next, 0);
	if (!ft_strncmp(cmd, "echo\0", len))
		return (ft_echo(all, cmd_node), 1);
	else if (!ft_strncmp(cmd, "cd\0", len))
		return (ft_cd(cmd, all), 1);
	else if (!ft_strncmp(cmd, "pwd\0", len))
		return (ft_pwd(all), 1);
	else if (!ft_strncmp(cmd, "export\0", len))
		return (ft_export(all, proc, cmd_node), 1);
	else if (!ft_strncmp(cmd, "unset\0", len))
		return (ft_unset(all, proc, cmd_node), 1);
	else if (!ft_strncmp(cmd, "env\0", len))
		return (print_env(all), 1);
	else if (!ft_strncmp(cmd, "exit\0", len))
		return (ft_exit(all, nodes, cmd_node, fds_bak), 1);
	return (0);
}
