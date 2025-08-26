/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:37:41 by mtice             #+#    #+#             */
/*   Updated: 2025/08/21 21:40:16 by mtice            ###   ########.fr       */
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
		if (!ft_strncmp(temp->token, "<\0", 2) || !ft_strncmp(temp->token, "<<\0", 3)
				|| !ft_strncmp(temp->token, ">\0", 2) || !ft_strncmp(temp->token, ">>\0", 3))
			temp->type = OPERATOR;
		else if (temp->prev->type == OPERATOR) 
		{
			if (!ft_strncmp(temp->prev->token, "<\0", 2))
				temp->type = RE_IN;
			else if (!ft_strncmp(temp->prev->token, "<<\0", 3))
				temp->type = HERE_DOC;
			else if (!ft_strncmp(temp->prev->token, ">\0", 2))
				temp->type = RE_OUT;
			else if (!ft_strncmp(temp->prev->token, ">>\0", 3))
				temp->type = APPEND;
		}
		else if (temp->process_nbr > i)
		{
			temp->type = COMMAND;
			if (is_builtin(temp->token))
				temp->builtin = 1;
			i++;
		}
		else
		 	temp->type = ARGUMENT;
		temp = temp->next;
	}
}

//reformats tokens
static void	token_pretty(t_data *all)
{
	t_token	*temp;
	int	i;

	temp = NULL;
	i = -1;
	while (temp != all->tokens->next)
	{
		if (i++ == -1)
			temp = all->tokens->next;
		if (ft_strlen(ft_strchr(temp->token, '$')))
		{
			i++;
			if (temp->type != HERE_DOC)
				expansion(all, temp, &i);
		}
		if (ft_strlen(ft_strchr(temp->token, '\'')) > ft_strlen(ft_strchr(temp->token, '"')))
		{
			del_char(temp->token, '\'');
			sub_char(temp->token, 26, '|');
		}
		else if (ft_strlen(ft_strchr(temp->token, '"')) > ft_strlen(ft_strchr(temp->token, '\'')))
		{
			del_char(temp->token, '"');
			sub_char(temp->token, 26, '|');
		}
		temp = temp->next;
	}
}

//----------------------------------------------------------------------------------------------------
//iterates through the t_token *tokens linked list to redefine tokens
//token_pretty: performs expansions, resubs pipes into literal strings, removes quotes
//assign_types: assigns a type to each token
//TODO: handle variable expansion in the HERE_DOC case
int	lexing(t_data *all)
{
	token_pretty(all);
	assign_types(all->tokens);
	return (0);
}
