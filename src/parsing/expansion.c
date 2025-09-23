/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:14:29 by mtice             #+#    #+#             */
/*   Updated: 2025/09/23 15:57:33 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*single_exp(char *token, int *i)
{
	char	*env_var;
	int		len;

	env_var = NULL;
	len = 0;
	if (token[*i] == '\'')
	{
		skip_to(token, '\'', i, &len);
		env_var = find_token(token, (*i)--, len);
	}
	return (env_var);
}

char	*valid_exp(t_data *all, t_token *tkn_ptr, char *token, int *i)
{
	char	*env_var;
	int		len;

	env_var = NULL;
	len = 0;
	if (++(*i) && token[*i] == '0')
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
		return (expand_var(tkn_ptr, all->c_envp, &env_var), env_var);
	}
	else if (token[*i] == '"')
		return (keep_exp(all, tkn_ptr, token, i));
	else if (token[*i] == '\'')
		return (single_exp(token, i));
	else
		return (ft_strdup(""));
}

char	*keep_exp(t_data *all, t_token *tkn_ptr, char *token, int *i)
{
	char	*env_var;
	char	*prev_env_var;
	char	*temp;
	int		dq;

	dq = 0;
	if (token[*i] == '"' && ++dq && ++(*i))
		env_var = append_char(env_var, token[*i - 1]);
	while (token[*i] != '"' && token[*i] != '\0')
	{
		if (token[*i] == '$' && !only_exp(token, *i))
		{
			prev_env_var = env_var;
			temp = valid_exp(all, tkn_ptr, token, i);
			env_var = ft_strjoin(prev_env_var, temp);
			if (has_whitespace(env_var) && tkn_ptr->split)
				word_split(tkn_ptr, &env_var);
			(free(prev_env_var), free(temp));
		}
		else
			env_var = append_char(env_var, token[*i]);
		(*i)++;
	}
	if (token[*i] == '"' && dq)
		return (env_var = append_char(env_var, token[*i]), env_var);
	return ((*i)--, env_var);
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
		else if (token[i] == '$' && token[i + 1] == '\0')
			env_var = ft_strdup("$");
		else if (token[i] == '$' && ++(tkn_ptr->split))
			env_var = valid_exp(all, tkn_ptr, token, &i);
		else if (token[i] == '\'')
			env_var = single_exp(token, &i);
		else
			env_var = keep_exp(all, tkn_ptr, token, &i);
		temp = env_var;
		env_var = ft_strjoin(prev_env_var, temp);
		(free(prev_env_var), free(temp), i++);
	}
	return (free(token), env_var);
}

void	expansion(t_data *all, t_token *tkn_ptr)
{
	char	*expanded;

	expanded = do_expansion(all, tkn_ptr, tkn_ptr->token);
	tkn_ptr->token = expanded;
}
