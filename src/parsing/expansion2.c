/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:14:29 by mtice             #+#    #+#             */
/*   Updated: 2025/09/20 12:45:04 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO: include position as a part of each token

static int	only_exp(char *token, int i)
{
	if (!token)
		return (0);
	if (token[i] == '$' && ++i)
	{
		while (isspace(token[i]))
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

static void	word_split2(t_token *tkn_ptr, char **env_var)
{
	int		i;
	int		len;
	char	*new_var;
	int		pos;

	pos = tkn_ptr->pos;
	i = 0;
	while ((*env_var)[i] != '\0')
	{
		len = 0;
		while (ft_isspace((*env_var)[i]) && (*env_var)[i] != '\0')
			i++;
		while (!ft_isspace((*env_var)[i]) && (*env_var)[i] != '\0')
		{
			i++;
			len++;
		}
		if (len)
		{
			new_var = find_token(*env_var, i--, len);
			tkn_ptr->prev = add_t_token(tkn_ptr->prev, new_var, tkn_ptr->process_nbr, pos++);
			i++;
		}
	}
	tkn_ptr->pos = pos;
}

static void	expand_var2(t_token *tkn_ptr, char **c_envp, char **env_var)
{
	int		i;
	int		j;
	char	*temp;

	j = 0;
	temp = *env_var;
	*env_var = ft_strjoin(*env_var, "=");
	free(temp);
	temp = *env_var;
	while (c_envp[j] != NULL)
	{
		i = 0;
		while (c_envp[j][i] != '=')
			i++;
		if (!ft_strncmp(c_envp[j], *env_var, ++i))
		{
			*env_var = ft_strdup(&c_envp[j][i]);
			if (has_whitespace(*env_var) && tkn_ptr->split)
				word_split2(tkn_ptr, env_var);
			else if (has_whitespace(*env_var) && !tkn_ptr->split)
				tkn_ptr->split++;
			break ;
		}
		j++;
	}
	if (!c_envp[j])
		*env_var = ft_strdup("");
	free(temp);
}

char	*valid_expansion2(t_data *all, t_token *tkn_ptr, char *token, int *i)
{
	char	*env_var;
	int		len;

	env_var = NULL;
	len = 0;
	(*i)++;
	if (token[*i] == '0')
		return (ft_strdup("minishell"));
	else if (token[*i] == '?')
		return (ft_itoa(all->return_val));
	else if (ft_isalpha(token[*i]) || token[*i] == '_')
	{
		while (ft_isalnum(token[*i]) || token[*i] == '_')
		{
			(*i)++;
			len++;
		}
		env_var = find_token(token, (*i)--, len);
		return (expand_var2(tkn_ptr, all->c_envp, &env_var), env_var);
	}
	else if (token[*i] == '"' || token[*i] == '\'')
		return (keep_expansion2(all, tkn_ptr, token, i));
	else
		return (ft_strdup(""));
}

char	*keep_expansion2(t_data *all, t_token *tkn_ptr, char *token, int *i)
{
	char	*env_var;
	int		len;
	char	*prev_env_var;
	char	*temp;

	env_var = NULL;
	len = 0;
	prev_env_var = NULL;
	temp = NULL;
	if (token[*i] == '\'')
	{
		skip_to(token, '\'', i, &len);
		env_var = find_token(token, (*i)--, len);
		return (env_var);
	}
	if (token[*i] == '"') //TODO: added flag here
	{
		env_var = append_char(env_var, token[*i]);
		(*i)++;
		len = 1;
	}
	while (token[*i] != '"' && token[*i] != '\0')
	{
		if (token[*i] == '$' && !only_exp(token, *i))
		{
			prev_env_var = env_var;
			temp = valid_expansion2(all, tkn_ptr, token, i);
			env_var = ft_strjoin(prev_env_var, temp);
			if (has_whitespace(env_var) && tkn_ptr->split) //TODO: changed split token conditions
				word_split2(tkn_ptr, &env_var);
			(free(prev_env_var), free(temp));
		}
		else
			env_var = append_char(env_var, token[*i]);
		(*i)++;
	}
	if (len == 1 && token[*i] == '"')
		env_var = append_char(env_var, token[*i]);
	return (env_var);
}

char	*do_expansion(t_data *all, t_token *tkn_ptr, char *token)
{
	int		i;
	char	*env_var;
	char	*prev_env_var;
	char	*temp;

	i = 0;
	env_var = NULL;
	while (token[i] != '\0')
	{
		prev_env_var = env_var;
		if (token[i] == '$' && token[i + 1] == '?' && ++i)
			env_var = ft_itoa(all->return_val);
		else if (token[i] == '$' && token[i + 1] == '\0' && ++i)
			env_var = ft_strdup("$");
		else if (token[i] == '$' && ++(tkn_ptr->split))
			env_var = valid_expansion2(all, tkn_ptr, token, &i);
		else if (token[i] == '\'' || token[i] == '"')
			env_var = keep_expansion2(all, tkn_ptr, token, &i);
		else
			env_var = keep_expansion2(all, tkn_ptr, token, &i);
		temp = env_var;
		env_var = ft_strjoin(prev_env_var, temp);
		(free(prev_env_var), free(temp));
		if (token[i] != '\0')
			i++;
	}
	return (free(token), env_var);
}

void	expansion(t_data *all, t_token *tkn_ptr)
{
	char	*expanded;

	expanded = do_expansion(all, tkn_ptr, tkn_ptr->token);
	tkn_ptr->token = expanded;
}
