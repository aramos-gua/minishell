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

//void	first_command(int i, t_data *all, int **pipes)
//{
////	int	devnull;
////
////	if (all->redirects->in_fd >= 0)
////		dup2(all->redirects->in_fd, STDIN_FILENO);
////	else
////	{
////		devnull = open("/dev/null", O_RDONLY);
////		dup2(devnull, STDIN_FILENO);
////		close(devnull);
////	}
//	dup2(pipes[i][1], STDOUT_FILENO);
//}
//
//void	last_command(t_data *all, int **pipes)
//{
//	if (all->redirects->out_fd >= 0)
//		dup2(all->redirects->out_fd, STDOUT_FILENO);
//	else
//	{
//		write(2, "minishell: Outfile Error\n", 25);
//		exit(1);
//	}
//}

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
    ft_printf("%d\n", i);
  }
  return (i);
}

char  **array_builder(t_data *all)
{
  t_token *tmp;
  char    **arr;
  int     i;

  i = 0;
  arr = malloc (ft_lstsize(all->tokens) * sizeof(char *));
  if (!arr)
    return (NULL);
  tmp = all->tokens->next;
  while (tmp && tmp->type != 0)
    tmp = tmp->next;
  arr[i] = tmp->token;
  while (tmp && tmp->type == 1)
    arr[++i] = tmp->token;
  arr[++i] = NULL;
  i = 0;
  while (arr[i++] != NULL)
    ft_printf(" [%s] ", tmp->token);
  if (arr[i] == NULL)
    ft_printf(" [NULL] ");
  return (arr);
}

void	execute_command(t_data *all)
{
	char	*path;
  char  **cmd_arr;

	path = get_cmd_path(all->tokens->next->token, all->c_envp);
	if (!path)
	{
		perror("execve");
		exit(1);
	}
	ft_printf("%s\n", path);
	ft_printf("execute_command\n");
  cmd_arr = array_builder(all);
	if (execve(path, cmd_arr, all->c_envp) == -1)
	{
		perror("execve");
		free(path);
		//free_split(all->tokens->next->token);
		exit (1);
	}
	free(path);
	//free_split(&all->tokens->next->token);
}
