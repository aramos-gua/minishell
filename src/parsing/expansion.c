/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 20:59:44 by mtice             #+#    #+#             */
/*   Updated: 2025/08/10 00:14:09 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO: check for more cases
//fix for case echo $HOME$PWD
static	void	expand(char **c_envp, char **env_var)
{
	int	i;
	int	j;
	int	k;
	char *temp;

	i = 0;
	j = 0;
	k = 0;
	temp = *env_var;
	while (c_envp[j] != NULL)
	{
		if (!ft_strncmp(c_envp[j], *env_var, ft_strlen(*env_var)))
		{
			k = 1;
			while (c_envp[j][i] != '=')
				i++;
			i++;
			*env_var = &(c_envp[j][i]);
		}
		j++;
	}
	if (k == 0)
		*env_var = ft_strdup("");
	free(temp);
}

char *expansion(t_data *all, char *token)
{
	int		i;
	int		len;
	char	*env_var = NULL;
	//char	*new_var = NULL;
	char	*temp = NULL;

	i = 0;
	while (token[i] != '\0')
	{
		len = 0;
		// if (token[i] == '\'')
		// {
		// 	while (token[++i] != '\'')
		// 		i++;
		// }
		if (token[i] == '$' && token[i + 1] != '\0')
		{
			i++;
			while (token[i] != ' ' && token[i] != '$' && token[i] != '"' && token[i] != '\0')
				i++, len++;
			temp = env_var;
			env_var = find_token(token, i--, len);	
			expand(all->c_envp, &env_var);
			env_var = ft_strjoin(temp, env_var);
			// if (!env_var)
			// {
			// 	env_var = find_token(token, i--, len);
			// 	expand(all->c_envp, &env_var);
			// }
			// else
			// {
			// 	new_var = find_token(token, i--, len);
			// 	expand(all->c_envp, &new_var);
			// 	env_var = ft_strjoin(env_var, new_var);
			// }
			// if (token[++i] == '$')
			// 	env_var = ft_strjoin(env_var, "$");
		}
		if (token[i] == '$' && token[i + 1] == '\0')
			env_var = ft_strjoin(env_var, "$");
		i++;
	}
	return (env_var);
}
