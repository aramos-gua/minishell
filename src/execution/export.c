/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:25:02 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/26 23:02:23 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	var_len(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '=')
		i++;
	if (str[i] == '=')
		return (i);
	return (-1);
}

int	exist_in_env(char *str, char *saved)
{
	int	len;

	len = var_len(str) + 1;
	if (ft_strncmp(str, saved, len) == 0)
		return (1);
	return (0);
}

int	ft_export(t_data *all, int proc, t_token *cmd_node)
{
	char	**array;
	int		len;
	int		i;

	array = all->c_envp;
	dprintf(2, "[%d]\n", proc);
	len = 1;
	i = 0;
	while (array[len])
	{
		len++;
	}
	array = NULL;
	array = malloc ((len + 2) * sizeof(char *));
	if (!array)
		return (0);
	while (all->c_envp[i])
	{
		array[i] = all->c_envp[i];
		i++;
	}
	array[i++] = cmd_node->next->token;
	array[i] = NULL;
	free(all->c_envp);
	all->c_envp = array;
	return (1);
}
