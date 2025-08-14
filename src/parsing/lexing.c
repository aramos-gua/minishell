/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:37:41 by mtice             #+#    #+#             */
/*   Updated: 2025/08/10 00:14:14 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//assigns a type to each token
static void	assign_types(t_token *tokens)
{
	t_token	*temp;
	int		i;

	temp = NULL;
	i = -1;
	while (temp != tokens->next)
	{
		if (i == -1)
			temp = tokens->next;
		if (is_builtin(temp->token))
			temp->type = BUILTIN;
		else if (!ft_strncmp(temp->token, "<\0", 2)
				|| !ft_strncmp(temp->token, "<<\0", 3)
				|| !ft_strncmp(temp->token, ">\0", 2)
				|| !ft_strncmp(temp->token, ">>\0", 3))
			temp->type = OPERATOR;
		else if (temp->prev->type == OPERATOR) 
		{
			if (!ft_strncmp(temp->prev->token, "<\0", 2))
				temp->type = RE_IN;
			else if (!ft_strncmp(temp->prev->token, "<<\0", 3))
				temp->type = APPEND;
			else if (!ft_strncmp(temp->prev->token, ">\0", 2))
				temp->type = RE_OUT;
			else if (!ft_strncmp(temp->prev->token, ">>\0", 3))
				temp->type = HERE_DOC;
		}
		else if (temp->process_nbr > i)
			temp->type = COMMAND;
		else
		 	temp->type = ARGUMENT;
		if (temp->process_nbr > i)
			i++;
		temp = temp->next;
	}
}

//TODO: variable expansion
//substitutes pipes back into a string "SUB" becomes "|"
//trims " and '
static void	token_pretty(t_data *all, t_token *tokens)
{
	t_token	*temp;
	int	i;

	(void)all;
	temp = NULL;
	i = -1;
	while (temp != tokens->next)
	{
		if (i++ == -1)
			temp = tokens->next;
		if (ft_strlen(ft_strchr(temp->token, '\'')) > ft_strlen(ft_strchr(temp->token, '"')))
		{
			del_char(temp->token, '\'');
			sub_char(temp->token, 26, '|');
		}
		else if (ft_strlen(ft_strchr(temp->token, '"')) > ft_strlen(ft_strchr(temp->token, '\'')))
		{
			del_char(temp->token, '"');
			sub_char(temp->token, 26, '|');
			if (ft_strchr(temp->token, '$'))
			{
				char *old_token = temp->token;
				temp->token = expansion(all, temp->token);
				free(old_token);
			}
		}
		else if (ft_strchr(temp->token, '$'))
		{
			char	*old_token = temp->token;
			temp->token = expansion(all, temp->token);
			free(old_token);
		}
		temp = temp->next;
	}
}

void	lexing(t_data *all)
{
	token_pretty(all, all->tokens);
	assign_types(all->tokens);
}
