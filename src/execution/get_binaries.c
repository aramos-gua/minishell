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

#include "../inc/minishell.h"

char  **array_builder(t_data *all, int proc)
{
  t_token *tmp;
  char    **arr;
  int     i;

  i = 0;
  arr = malloc ((ft_lstsize(all->tokens, proc) + 1) * sizeof(char *));
  if (!arr)
    return (NULL);
  tmp = all->tokens;
  while ((tmp->type != COMMAND || tmp->process_nbr != proc))
    tmp = tmp->next;
  arr[i++] = tmp->token;
  tmp = tmp->next;
  while (tmp->type == ARGUMENT && tmp->process_nbr == proc)
  {
    arr[i++] = tmp->token;
    tmp = tmp->next;
  }
  arr[i] = NULL;
  return (arr);
	i = 0;
	//ft_printf("array builder\n");
	arr = malloc ((ft_lstsize(all->tokens, proc) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	tmp = all->tokens;
	while ((tmp->type != COMMAND || tmp->process_nbr != proc))
		tmp = tmp->next;
	arr[i++] = tmp->token;
	tmp = tmp->next;
	//ft_printf("[%d][%s]  ", i - 1, arr[i - 1]);
	while (tmp->type == ARGUMENT && tmp->process_nbr == proc)
	{
		arr[i++] = tmp->token;
		tmp = tmp->next;
		//ft_printf("[%d][%s]  ", i - 1, arr[i - 1]);
	}
	arr[i] = NULL;
	//ft_printf("[%d][%s]\n\n\n", i, "NULL");
	return (arr);
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

char	*get_cmd_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	i = -1;
	path_env = NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
    {
      perror(cmd);
			return (NULL);
    }
	}
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path_env = env[i] + 5;
	if (!path_env)
		return (NULL);
	paths = (ft_split(path_env, ':'));
	if (!paths)
  {
    //perror(cmd);
		return (NULL);
  }
	full_path = build_path(cmd, paths);
	if (!full_path)
		return (free_split(paths), NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	return (free_split(paths), NULL);
}
