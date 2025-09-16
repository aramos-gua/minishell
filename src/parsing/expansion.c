/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 20:59:44 by mtice             #+#    #+#             */
/*   Updated: 2025/08/28 21:01:42 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//-----------------------------------------------------------------------------
//if a variable has been exported with spaces, it will become multiple tokens
//e.g. export a="cho hello", e$a -> [echo] [hello]
static void	word_split(t_token *tkn_ptr, char **env_var, int *pos)
{
	int		i;
	int		len;
	char	*new_var;

	i = 0;
	while (!ft_isspace((*env_var)[i]) && (*env_var)[i] != '\0')
		i++;
	if ((*env_var)[i] == '\0')
		return ;
	i = 0;
	while ((*env_var)[i] != '\0' && ++(*pos))
	{
		len = 0;
		while (ft_isspace((*env_var)[i]) && (*env_var)[i] != '\0')
			i++;
		while (!ft_isspace((*env_var)[i]) && (*env_var)[i] != '\0' && ++len)
			i++;
		new_var = find_token(*env_var, i--, len);
		tkn_ptr->prev
			= add_t_token(tkn_ptr->prev, new_var, tkn_ptr->process_nbr);
		i++;
	}
}

//-----------------------------------------------------------------------------
//attempts to expand a variable, if it exists in the environment
static	void	expand_var(t_token *tkn_ptr, char **c_envp, char **env_var)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
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
			tkn_ptr->exp = 1;
			break ;
		}
		j++;
	}
	if (!c_envp[j])
		*env_var = ft_strdup("");
	free(temp);
}
//-----------------------------------------------------------------------------
//once a '$' in the token, valid_expansion() checks whether an expansion is 
//valid before calling expand_var()
static char	*valid_expansion(t_data *all, t_token *tkn_ptr, char *token, int *i)
{
	char	*env_var;
	int		len;

	env_var = NULL;
	len = 0;
	(*i)++;
	if (token[*i] == '0')
		return (ft_strdup("minishell"));
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
	else if (token[*i + 1] == '$')
	{
		(*i) += 2;
		return (ft_strdup("$"));
	}
	else
		return (ft_strdup(""));
}

//-----------------------------------------------------------------------------
//keeps what it finds, even if it is not a valid expansions
//happens when an expansion is attempted within quotes, e.g. "hi$HOME"
static char	*keep_expansion(t_data *all, char *token, int *i)
{
	(void)all;
	char	*env_var;
	int		len;

	env_var = NULL;
	len = 1;
	(*i)++;
	if (token[*i - 1] == '$')
		return (NULL);
	else if ((token[*i - 1] == '\'' && token[*i] == '\'')
		|| (token[*i - 1] == '"' && token[*i] == '"'))
		return (NULL);
	else if (token[*i - 1] == '\'' && token[*i] != '\0')
		skip_to(token, '\'', i, &len);
	else
	{
		while (token[*i] != '"' && token[*i] != '\0')
		{
			if (token[*i] == '$' && token[*i + 1] == '$')
				skip_to(token, '\'', i, &len); //TODO: is this correct?
			if (token[*i] == '$' && token[*i + 1] != '"')// || !ft_isspace(token[*i])))
			{
			// 	env_var = find_token(token, (*i)--, len);
			// 	(*i)++;
			// 	env_var = ft_strjoin(env_var, valid_expansion(all, token, i));
			// 	printf("env_var:%s\n", env_var);
			// 	// (*i)++;
			// 	// do_expansion(all, token + *i);
			// 	return (env_var);
				break;
			}
			(*i)++;
			len++;
		}
	}
	env_var = find_token(token, (*i)--, len);
	return (env_var);
}

//-----------------------------------------------------------------------------
//iterates through the token to check at which point valid_expansion()
//and keep_expansion() should be called
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
		else if (token[i] == '$' && token[i + 1] != '\'' && token[i + 1] != '"')
			env_var = valid_expansion(all, tkn_ptr, token, &i);
		else
			env_var = keep_expansion(all, token, &i);
		temp = env_var;
		env_var = ft_strjoin(prev_env_var, temp);
		(free(prev_env_var)), (free(temp));
		i++;
	}
	return (free(token), env_var);
}

//-----------------------------------------------------------------------------
//do_expansion() iterates through the token to for valid_expansions
//word_split() splits an expanded variable into tokens if contains whitespaces
//TODO: heredoc expansions
void	expansion(t_data *all, t_token *tkn_ptr, int *position)
{
	char	*expanded;

	expanded = do_expansion(all, tkn_ptr, tkn_ptr->token);
	tkn_ptr->token = expanded;
	if ((ft_strchr(expanded, ' ') || ft_strchr(expanded, '\t')
		|| ft_strchr(expanded, '\n') || ft_strchr(expanded, '\v')
		|| ft_strchr(expanded, '\f') || ft_strchr(expanded, '\r'))
		&& tkn_ptr->exp)
		word_split(tkn_ptr, &expanded, position);
}
