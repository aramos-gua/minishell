/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:37:21 by mtice             #+#    #+#             */
/*   Updated: 2025/09/23 15:57:32 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
//-----------------------------------------------------------------------------
//detects if there are only $ and whitespaces within double quotes
int	only_exp(char *token, int i)
{
	if (!token)
		return (0);
	if (token[i] == '$' && ++i)
	{
		while (ft_isspace(token[i]))
			i++;
	}
	if (token[i] == '\0')
		return (1);
	else if (token[i] == '"' && token[i + 1] == '\0')
		return (1);
	else if (token[i] == '\'' && token[i + 1] == '\0')
		return (1);
	else
		return (0);
}

//-----------------------------------------------------------------------------
//appends a char c to string s, while freeing the intial malloc-ed string
char	*append_char(char *s, char c)
{
	int		len;
	char	*appended;
	int		i;

	len = 0;
	if (s)
		len = ft_strlen(s);
	appended = ft_calloc(sizeof(char), (len + 2));
	if (!appended)
	{
		perror("Malloc error");
		return (free(s), NULL);
	}
	i = 0;
	while (s && s[i] != '\0')
	{
		appended[i] = s[i];
		i++;
	}
	appended[i++] = c;
	appended[i] = '\0';
	return (free(s), appended);
}

//-----------------------------------------------------------------------------
//p: position, n_var: n_var
//splits an environment variable that contains whitespaces into separate tokens
void	word_split(t_token *tkn_ptr, char **env_var)
{
	int		i;
	int		len;
	char	*n_var;
	int		p;

	p = tkn_ptr->pos;
	i = 0;
	while ((*env_var)[i] != '\0')
	{
		len = 0;
		while (ft_isspace((*env_var)[i]) && (*env_var)[i] != '\0')
			i++;
		while (!ft_isspace((*env_var)[i]) && (*env_var)[i] != '\0' && ++i)
			len++;
		if (len)
		{
			n_var = find_token(*env_var, i--, len);
			tkn_ptr->prev
				= add_t_token(tkn_ptr->prev, n_var, tkn_ptr->process_nbr, p++);
			i++;
		}
	}
	tkn_ptr->pos = p;
}

static int	in_quotes(char *token, char *key)
{
	int		ptr1;
	int		ptr2;
	char	*cut_str;
	int		i;

	i = 0;
	ptr1 = 0;
	ptr2 = 0;
	while (token[i] != '"' && token[i] != '\0')
		i++;
	if (token[i] == '"')
	{
		ptr1 = i;
		i++;
	}
	while (token[i] != '"' && token[i] != '\0')
		i++;
	if (token[i] == '"')
		ptr2 = i;
	if (ptr2 == ptr1)
		return (0);
	cut_str = ft_substr(token, ptr1, ptr2 - ptr1 + 1);
	if (ft_strnstr(cut_str, key, ft_strlen(cut_str)))
		return (free(cut_str), 1);
	return (free(cut_str), 0);
}

//-----------------------------------------------------------------------------
//if a variable is found to be an existing environment variable, it is expanded
void	expand_var(t_token *tkn_ptr, char **c_envp, char **env_var)
{
	int		i;
	int		j;
	char	*temp;
	char	*key;

	key = ft_strdup(*env_var);
	temp = *env_var;
	*env_var = ft_strjoin(*env_var, "=");
	(free(temp), temp = *env_var, j = 0);
	while (c_envp[j] != NULL)
	{
		i = 0;
		while (c_envp[j][i] != '=')
			i++;
		if (!ft_strncmp(c_envp[j], *env_var, ++i))
		{
			*env_var = ft_strdup(&c_envp[j][i]);
			if (has_whitespace(*env_var) && !in_quotes(tkn_ptr->token, key))
				tkn_ptr->split = 2;
			return (free(temp), free(key));
		}
		j++;
	}
	if (!c_envp[j])
		(free(temp), free(key), *env_var = ft_strdup(""));
}
