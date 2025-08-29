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
#include <term.h>

static void	word_split(t_data *all, t_token *tkn_ptr, char **env_var, int *pos)
{
	int		i;
	int		len;
	int		del_pos;
	char	*new_var;

	i = 0;
	while ((*env_var)[i] != ' ' && (*env_var)[i] != '\0')
		i++;
	if ((*env_var)[i] == '\0')
		return ;
	i = 0;
	del_pos = 0;
	while ((*env_var)[i] != '\0')
	{
		len = 0;
		while (ft_isspace((*env_var)[i]) && (*env_var)[i] != '\0')
			i++;
		while (!ft_isspace((*env_var)[i]) && (*env_var)[i] != '\0')
			i++, len++;
		new_var = find_token(*env_var, i--, len);
		all->tokens = add_at_pos(all->tokens, new_var, tkn_ptr->process_nbr, (*pos)++);
		i++;
		del_pos++;
	}
	del_t_token(all->tokens, *pos - del_pos);
}

static	void	expand_var(char **c_envp, char **env_var)
{
	int	i;
	int	j;
	char *temp;

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
			*env_var = &c_envp[j][i];
			break;
		}
		j++;
	}
	if (!c_envp[j])
		*env_var = ft_strdup("");
}

//----------------------------------------------------------------------------------
//expansion inside quotes, i.e. there is a $ inside ""
//e.g. "$'HOME"
//TODO: handle this case: export a="cho hello"
//e$a (should give echo: builtin, hello: argument)
//handle heredoc expansions

// char	*do_expansion(t_data *all, char *token)
// {
// 	int		i;
// 	int		len;
// 	int		to_expand;
// 	char	*prev_env_var;
// 	char	*env_var;
//
// 	i = 0;
// 	env_var = NULL;
// 	while (token[i] != '\0')
// 	{
// 		len = 0;
// 		to_expand = 0;
// 		prev_env_var = env_var;
// 		if (token[i] == '$' && token[i + 1] == '?')
// 			env_var = ft_itoa(all->return_val);
// 		else if (token[i] == '$' && token[i + 1] == '\'' && printf("CONDITION 2\n"))
// 		{
// 			if (token[i - 1] != '"')
// 				i += 2, len++;
// 			else
// 			 	i++, len++;
// 			while (token[i] != '\'' && token[i] != '\0')
// 				i++, len++;
// 		}
// 		else if (token[i] == '$' && token[i + 1] == '"' && printf("CONDITION 3\n"))
// 		{
// 			i += 2, len++;
// 			while (token[i] != '"' && token[i] != '$' && token[i] != '\0')
// 				i++, len++;
// 		}
// 		else if (token[i] == '$' && (ft_isalpha(token[i + 1]) || token[i + 1] == '_') && printf("CONDITION 4\n"))
// 		{
// 			i++;
// 			while (ft_isalnum(token[i]) || token[i] == '_')
// 				i++, len++;
// 			to_expand = 1;
// 		}
// 		else if (token[i] == '$' && token[i + 1] == '\0' && printf("CONDITION 5\n"))
// 			i++, len++;
// 		else if (token[i] == '\'' && token[i + 1] != '\'' && printf("CONDITION 6\n"))
// 		{
// 			i++, len++;
// 			while(token[i] != '\'' && token[i] != '\0')
// 				i++, len++;
// 		}
// 		else if (token[i] == '"' && printf("CONDITION 7\n"))
// 		{
// 			i++, len++;
// 			while (token[i] != '$' && token[i] != '"' && token[i] != '\0')
// 				i++, len++;
// 			printf("token[i]: %c\n", token[i]);
// 		}
// 		else if (token[i] != '$' && printf("CONDITION 8\n"))
// 		{
// 			while (token[i] != '$' && token[i] != '\0')
// 				i++, len++;
// 		}
// 		env_var = find_token(token, i--, len);
// 		expand_var(all->c_envp, &env_var, to_expand);
// 		env_var = ft_strjoin(prev_env_var, env_var);
// 		i++;
// 	}
// 	return (env_var);
// }

static char	*keep_expansion(char *token, int *i)
{
	int		len;
	char	*env_var;

	len = 1;
	(*i)++;
	if (token[*i - 1] == '\'' && token[*i] != '\0')
	{
		while (token[*i] != '\'' && token[*i] != '\0')
		{
			(*i)++;
			len++;
		}
	}
	else if (token[*i - 1] == '"' && token[*i] != '\0')
	{
		while (token[*i] != '"' && token[*i] != '\0')
		{
			if (token[*i] == '$' && token[*i + 1] != '\'')
				break;
			(*i)++;
			len++;
		}
	}
	env_var = find_token(token, (*i)--, len);
	return(env_var);
}

static char	*valid_expansion(t_data *all, char *token, int *i)
{
	int		len;
	char	*env_var;

	len = 0;
	(*i)++;
	if (ft_isalpha(token[*i]) || token[*i] == '_')
	{
		while (ft_isalnum(token[*i]) || token[*i] == '_')
		{
			(*i)++;
			len++;
		}
	}
	env_var = find_token(token, (*i)--, len);
	expand_var(all->c_envp, &env_var);
	return (env_var);
}

//TODO: remove ugly len part
char *do_expansion(t_data *all, char *token)
{
	int		i;
	char	*env_var;
	char	*prev_env_var;
	
	i = 0;
	env_var = NULL;
	while (token[i] != '\0')
	{
		int len = 0;
		prev_env_var = env_var;
		if (token[i] == '$' && token[i + 1] == '?')
			env_var = ft_strdup(ft_itoa(all->return_val));
		else if (token[i] == '$' && (token[i + 1] == '"' || token[i + 1] == '\0') && i != 0)
			env_var = ft_strdup("$");
		else if (token[i] == '$')
			env_var = valid_expansion(all, token, &i);
		else if (token[i] == '"' || token[i] == '\'')
			env_var = keep_expansion(token, &i);
		else
		{
			while (token[i] != '$' && token[i] != '\0')
				i++, len++;
			env_var = ft_strjoin(prev_env_var, find_token(token, i--, len));
		}
		env_var = ft_strjoin(prev_env_var, env_var);
		i++;
	}
	return (env_var);
}


//---------------------------------------------------------------------------------------------------
//expansion looks for the variable to expand, and constructs the env_var (the expanded environment variable)
//expand_var() is called only when a valid expansion is detected
//check_var() checks the expanded env_var to see if it is necessary to split it into more tokens
//check_var() handles the export case, e.g. export b="cho hello whats up"
//heredoc_expansion() handles the heredoc expansion case, it is dealt with separately from all other expansion cases
//TODO: heredoc expansions
void	expansion(t_data *all, t_token *tkn_ptr, int *position)
{
	(void)position;
	char	*expanded;

	expanded = do_expansion(all, (tkn_ptr->token));
	tkn_ptr->token = expanded;
	if (ft_strchr(expanded, ' '))
		word_split(all, tkn_ptr, &(tkn_ptr->token), position);
}
