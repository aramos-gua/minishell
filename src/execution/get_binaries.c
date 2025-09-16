/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binaries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:52:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/18 15:58:18 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_cmd_arg(t_token *list, int proc)
{
	t_token	*tail;
	t_token	*head;
	int		count;

	count = 1;
	tail = list;
	// dprintf(2, "tail is [%s]\n", tail->token);
	head = tail->next;
	// dprintf(2, "head is [%s]\n", head->token);
	while (head != tail && head->process_nbr != proc)
		head = head->next;
	while (head != tail)
	{
		if (head->type == COMMAND || head->type == ARGUMENT)
			count++;
		head = head->next;
	}
	// dprintf(2, "\n\ncount is [%d]\n\n", count);
	return (count);
}

int	array_builder(t_data *all, int proc)
{
	t_token	*head;
	t_token	*tail;
	char	**array;
	int		i;
	int		len;

	if (all->arr)
		free_double_char(all->arr);
	len = count_cmd_arg(all->tokens, proc);
	// dprintf(2, "len of array will be [%d]\n", len + 1);
	i = 0;
	array = ft_calloc((len + 1), sizeof(char *));
	if (!all->arr)
	{
		dprintf(2, "calloc failed for array builder\n");
		return (all->return_val = 1, 1);
	}
	tail = all->tokens;
	// dprintf(2, "tail is [%s]\n", tail->token);
	head = tail->next;
	// dprintf(2, "head is [%s]\n", head->token);
	while (head->process_nbr != proc || head->type != COMMAND)
		head = head->next;
	array[i] = ft_calloc((ft_strlen(head->token) + 1), sizeof(char));
	array[i++] = ft_strdup(head->token);
	head = head->next;
	while (head->type == ARGUMENT && head->process_nbr == proc)
	{
		array[i] = ft_calloc((ft_strlen(head->token) + 1), sizeof(char));
		array[i++] = ft_strdup(head->token);
		head = head->next;
	}
	array[i] = NULL;
	all->arr = array;
	return (0);
}

char	*build_path(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	int		full_path_len;

	i = 0;
	while (paths[i])
	{
		full_path_len = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
		full_path = ft_calloc(full_path_len, 1);
		full_path[ft_strlen(paths[i])] = '\0';
		if (!full_path)
		{
			i++;
			continue ;
		}
		ft_strlcpy(full_path, paths[i], ft_strlen(paths[i]) + 1);
		ft_strlcat(full_path, "/", full_path_len);
		ft_strlcat(full_path, cmd, full_path_len);
		if (access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*full_path_given(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else
		return (NULL);
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	i = -1;
	path_env = NULL;
	if (ft_strchr(cmd, '/'))
		return (full_path_given(cmd));
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path_env = env[i] + 5;
	if (!path_env)
		return (NULL);
	paths = (ft_split(path_env, ':'));
	if (!paths)
		return (NULL);
	full_path = build_path(cmd, paths);
	if (!full_path)
		return (free_split(paths), NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	return (free_split(paths), NULL);
}
