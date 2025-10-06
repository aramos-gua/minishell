/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:16:30 by aramos            #+#    #+#             */
/*   Updated: 2025/09/29 23:54:04 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//looks for HOME defined in the env and if found, returns that path
static char	*get_home(t_data *all, char **arr)
{
	int		i;
	int		len;
	char	*home;

	i = 0;
	while (ft_strncmp(arr[i], "HOME=", 5) != 0)
		i++;
	if (arr[i] == NULL)
	{
		all->return_val = 1;
		return (ft_dprintf(2, "minishell: cd: HOME not set\n"), NULL);
	}
	len = ft_strlen(arr[i]);
	home = ft_substr(arr[i], 5, len);
	return (home);
}

//gets the home directory and calls chdir to it
static int	go_home(t_data *all, char *old_dir)
{
	char	*home;
	char	*current;

	home = get_home(all, all->c_envp);
	chdir(home);
	update_env_cd(all, "OLDPWD=", old_dir);
	current = getcwd(NULL, 0);
	update_env_cd(all, "PWD=", current);
	free(home);
	free(current);
	return (all->return_val = 0, 0);
}

//Checks if the argument contains only '/' and normalizes to root dir
static int	only_slash(char *dir)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (dir[i++])
	{
		if (dir[i] && dir[i] == '/')
			flag = 1;
		else
			flag = 0;
	}
	if (i > 2)
		return (flag);
	return (0);
}

//chdir to root dir
static int	go_root(t_data *all, char *old_dir)
{
	char	*current;

	chdir("/");
	update_env_cd(all, "OLDPWD=", old_dir);
	current = getcwd(NULL, 0);
	update_env_cd(all, "PWD=", current);
	free(current);
	return (all->return_val = 0, 0);
}

//handles change directory command. ..|cd|~|/|relative|absolute arguments
int	ft_cd(t_token *cmd, t_data *all, int nodes)
{
	char	*old_dir;
	char	*new_dir;

	if (nodes > 2)
		return (ft_dprintf(2, "%s\n", TOO_ARGS_C), all->return_val = 1);
	if (all->info->total_proc > 1)
		return (1);
	old_dir = getcwd(NULL, 0);
	if (only_slash(cmd->next->token))
		return (go_root(all, old_dir), free(old_dir), 1);
	else if (nodes == 1 || \
		(nodes == 2 && !ft_strncmp(cmd->next->token, "~", 2)))
		return (go_home(all, old_dir), free(old_dir), 1);
	else if (chdir(cmd->next->token) == -1)
	{
		if (errno == ENOENT)
			all->return_val = 1;
		else if (errno == EACCES)
			all->return_val = 126;
		return (free(old_dir), perror("minishell: cd"), 1);
	}
	new_dir = getcwd(NULL, 0);
	(update_env_cd(all, "OLDPWD=", old_dir), \
		update_env_cd(all, "PWD=", new_dir));
	return (free(new_dir), free(old_dir), all->return_val = 0);
}
