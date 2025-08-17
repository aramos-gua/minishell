/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:05:11 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/10 16:14:54 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	first_command(int i, t_data *all, int **pipes)
{
	int	devnull;

	ft_printf("first command\n");
	if (all->info->in_fd >= 0)
		dup2(all->info->in_fd, STDIN_FILENO);
	else
	{
		devnull = open("/dev/null", O_RDONLY);
		dup2(devnull, STDIN_FILENO);
		close(devnull);
		return (1);
	}
	dup2(pipes[i][1], STDOUT_FILENO);
	return (0);
}

int	last_command(t_data *all, int **pipes)
{
	ft_printf("last command\n");
	if (all->info->out_fd >= 0)
		dup2(all->info->out_fd, STDOUT_FILENO);
	else
	{
		write(2, "minishell: Outfile Error\n", 25);
		close_pipes(all, pipes);
		close(all->info->out_fd);
		close(all->info->in_fd);
		return (1);
	}
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
		full_path = malloc(full_path_len);
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
			return (NULL);
	}
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

//int ft_lstsize(t_token *list)
//{
//  t_token *current;
//  int     i;
//
//  i = 0;
//  current = list;
//  while (current != NULL)
//  {
//    i++;
//    current = current->next;
//    ft_printf("%d\n", i);
//  }
//  return (i);
//}

t_token *get_cmd_node(t_token *list)
{
  t_token *current;

  if (!list)
    return (NULL);
  current = list;
  while (current->type != COMMAND)
    current = current->next;
  return(current);
}

int ft_lstsize(t_token *list)
{
  t_token *current;
  int     i;

  i = 1;
  if (!list)
    return (0);
  current = list;
  while (current->next != list)
  {
    i++;
    current = current->next;
  }
  return (i);
}

char  **array_builder(t_data *all)
{
  t_token *tmp;
  char    **arr;
  int     i;

  i = 0;
	//ft_printf("array builder\n");
  arr = malloc (ft_lstsize(all->tokens) + 1 * sizeof(char *));
  if (!arr)
    return (NULL);
  tmp = all->tokens;
  while (tmp->type != COMMAND)
    tmp = tmp->next;
  arr[i++] = tmp->token;
  tmp = tmp->next;
  ft_printf("[%d][%s]  ", i - 1, arr[i - 1]);
  while (tmp->type != COMMAND)
  {
    arr[i++] = tmp->token;
    tmp = tmp->next;
    ft_printf("[%d][%s]  ", i - 1, arr[i - 1]);
  }
  arr[i] = NULL;
  ft_printf("[%d][%s]\n\n\n", i, "NULL");
  return (arr);
}

int	execute_command(t_data *all)
{
	t_token *cmd;
	char	  *path;
	char    **cmd_arr;

	//ft_printf("execute_command\n");
	cmd = get_cmd_node(all->tokens);
	if (!cmd)
	return (1);
	//ft_printf("%s\n", cmd->token);
	path = get_cmd_path(cmd->token, all->c_envp);
	if (!path)
	{
		perror("execve");
		return (1);
	}
	cmd_arr = array_builder(all);
	if (execve(path, cmd_arr, all->c_envp) == -1)
	{
		perror("execve");
		free(path);
		//free_split(all->tokens->next->token);
	return (1);
	}
	free(path);
	//free_split(&all->tokens->next->token);
	return (0);
}
