/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 20:59:44 by mtice             #+#    #+#             */
/*   Updated: 2025/08/21 21:40:18 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	void	check_var(t_data *all, t_token *tkn_ptr, char **env_var, int *position)
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
		all->tokens = add_at_pos(all->tokens, new_var, tkn_ptr->process_nbr, (*position)++);
		i++;
		del_pos++;
	}
	del_t_token(all->tokens, *position - del_pos);
}

static	void	expand_var(char **c_envp, char **env_var, int to_expand)
{
	int	i;
	int	j;
	int	k;
	char *temp = NULL;

	if (!to_expand)
		return ;
	i = 0;
	j = 0;
	k = 0;
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
			k = 1;
			*env_var = &c_envp[j][i];
		}
		j++;
	}
	if (k == 0)
		*env_var = ft_strdup("");
	free(temp);
}

//----------------------------------------------------------------------------------
//expansion inside quotes, i.e. there is a $ inside ""
//e.g. "$'HOME"
//TODO: handle this case: export a="cho hello"
//e$a (should give echo: builtin, hello: argument)
//handle heredoc expansions

static void	do_expansion(t_data *all, t_token *tkn_ptr)
{
	int		i;
	int		len;
	int		to_expand;
	char	*prev_env_var;
	char	*env_var;

	i = 0;
	env_var = NULL;
	while (tkn_ptr->token[i] != '\0')
	{
		len = 0;
		to_expand = 0;
		prev_env_var = env_var;
		if (tkn_ptr->token[i] == '$' && tkn_ptr->token[i + 1] == '?')
		{
			printf("UNIMPLEMENTED: return exit code (expansion)\n");
			return ;
		}
		else if (tkn_ptr->token[i] == '$' && tkn_ptr->token[i + 1] == '\'')
		{
			if (tkn_ptr->token[i - 1] != '"')
				i += 2, len++;
			else
			 	i++, len++;
			while (tkn_ptr->token[i] != '\'' && tkn_ptr->token[i] != '\0')
				i++, len++;
		}
		else if (tkn_ptr->token[i] == '$' && tkn_ptr->token[i + 1] == '"')
		{
			i += 2, len++;
			while (tkn_ptr->token[i] != '"' && tkn_ptr->token[i] != '$' && tkn_ptr->token[i] != '\0')
				i++, len++;
		}
		else if (tkn_ptr->token[i] == '$' && (ft_isalpha(tkn_ptr->token[i + 1]) || tkn_ptr->token[i + 1] == '_'))
		{
			i++;
			while (ft_isalpha(tkn_ptr->token[i]) || tkn_ptr->token[i] == '_')
				i++, len++;
			to_expand = 1;
		}
		else if (tkn_ptr->token[i] == '$' && tkn_ptr->token[i + 1] == '\0')
			i++, len++;
		else if (tkn_ptr->token[i] == '\'')
		{
			i++, len++;
			while(tkn_ptr->token[i] != '\'' && tkn_ptr->token[i] != '\0')
				i++, len++;
		}
		else if (tkn_ptr->token[i] == '"')
		{
			i++, len++;
			while (tkn_ptr->token[i] != '$' && tkn_ptr->token[i] != '"' && tkn_ptr->token[i] != '\0')
				i++, len++;
		}
		else if (tkn_ptr->token[i] != '$')
		{
			while (tkn_ptr->token[i] != '$' && tkn_ptr->token[i] != '\0')
				i++, len++;
		}
		env_var = find_token(tkn_ptr->token, i--, len);
		expand_var(all->c_envp, &env_var, to_expand);
		env_var = ft_strjoin(prev_env_var, env_var);
		i++;
	}
	tkn_ptr->token = env_var;
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
	do_expansion(all, tkn_ptr);
	check_var(all, tkn_ptr, &(tkn_ptr->token), position);
}
