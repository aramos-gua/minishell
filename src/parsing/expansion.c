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
	int	j;
	char *temp;

	int k = 0;
	j = 0;
	temp = *env_var;
	while (c_envp[j] != NULL)
	{
		if (!ft_strncmp(c_envp[j], *env_var, ft_strlen(*env_var)))
		{
			k = 1;
			while (*c_envp[j] != '=')
				c_envp[j]++;
			c_envp[j]++;
			//printf("%s\n", c_envp[j]);
			*env_var = c_envp[j];
		}
		j++;
	}
	if (k != 1)
		*env_var = ft_strdup("");
	free(temp);
}

char *expansion(t_data *all, char *token)
{
	int		i;
	int		len;
	char	*env_var;

	i = 0;
	while (token[i] != '\0')
	{
		len = 0;
		if (token[i] == '\'')
		{
			while (token[++i] != '\'')
				i++;
		}
		else if (token[i] == '$')
		{
			i++;
			while (token[i] != ' ' && token[i] != '$' && token[i] != '"' && token[i] != '\0')
			{
				i++;
				len++;
			}
			env_var = find_token(token, i--, len);
			expand(all->c_envp, &env_var);
			//printf("env_var: %s\n", env_var);
		}
		i++;
	}
	return (env_var);
}
