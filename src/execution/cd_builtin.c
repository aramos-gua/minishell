/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:16:30 by aramos            #+#    #+#             */
/*   Updated: 2025/09/13 16:55:46 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//gets previos directory by searching last slash occurrence and trimming it
static char	*get_prev_dir(t_data *all)
{
	char	*cwd;
	char	*last_slash;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (all->return_val = 1, NULL);
	last_slash = ft_strrchr(cwd, '/');
	if (last_slash && last_slash != cwd)
		*last_slash = '\0';
	else if (last_slash == cwd)
		cwd[1] = '\0';
	return (all->return_val = 0, cwd);
}

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
	dprintf(2, "home [%s]\n", home);
	return (home);
}

//gets the home directory and calls chdir to it
static int	go_home(t_data *all, char *old_dir)
{
	chdir(get_home(all, all->c_envp));
	update_env_cd(all, "OLDPWD=", old_dir);
	update_env_cd(all, "PWD=", getcwd(NULL, 0));
	return (all->return_val = 0, 0);
}

//handles change directory command. ..|cd|~|/|relative|absolute arguments
int	ft_cd(t_token *cmd, t_data *all, int nodes)
{
	char	*old_dir;

	if (nodes > 2)
	{
		ft_dprintf(2, "minishell: cd: %s\n", TOO_ARGS);
		return (all->return_val = 1);
	}
	old_dir = getcwd(NULL, 0);
	if (!old_dir)
		return (all->return_val = 1);
	else if (nodes == 1 && !ft_strncmp(cmd->token, "cd\0", 3))
		return (go_home(all, old_dir));
	else if (nodes == 2 && !ft_strncmp(cmd->next->token, "~\0", 2))
		return (go_home(all, old_dir));
	else if (chdir((const char *)cmd->next->token) == -1)
		return (all->return_val = 1, perror("minishell"), 1);
	else if (!strncmp(cmd->next->token, "..\0", 3))
		chdir(get_prev_dir(all));
	else
		chdir(cmd->next->token);
	update_env_cd(all, "OLDPWD=", old_dir);
	update_env_cd(all, "PWD=", getcwd(NULL, 0));
	free(old_dir);
	return (all->return_val = 0);
}
