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

static int	is_redirect(char *token)
{
	if (!ft_strncmp(token, "<\0", 2))
		return (RE_IN);
	else if (!ft_strncmp(token, ">\0", 2))
		return (RE_OUT);
	else if (!ft_strncmp(token, "<<\0", 3))
		return (HERE_DOC);
	else if (!ft_strncmp(token, ">>\0", 3))
		return (APPEND);
	else
		return (0);
}

//assigns a type to each token
static void	assign_types(t_token *tokens)
{
	t_token	*temp;
	int		i;

	temp = NULL;
	i = -1;
	while (temp != tokens->next)
	{
		if (i == -1 && i++)
			temp = tokens->next;
		if (is_redirect(temp->token))
			temp->type = OPERATOR;
		else if (is_redirect(temp->prev->token))
			temp->type = is_redirect(temp->prev->token);
		else if (temp->process_nbr == i)
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

void	delete_quotes(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '"')
		{
			del_char(token, i);
			if (token[i] != '"')
				(skip_to(token, '"', &i, (int []){0})), i--;
			del_char(token, i);
		}
		else if (token[i] == '\'')
		{
			del_char(token, i);
			if (token[i] != '\'')
				(skip_to(token, '\'', &i, (int []){0})), i--;
			del_char(token, --i);
		}
		else
			i++;
	}
}

//reformats tokens
static void	token_pretty(t_data *all)
{
	t_token	*temp;
	int		i;

	temp = NULL;
	i = -1;
	while (temp != all->tokens->next)
	{
		if (i++ == -1)
			temp = all->tokens->next;
		if (ft_strchr(temp->token, '$'))
		{
			i++;
			if (temp->type != HERE_DOC)
				expansion(all, temp, &i);
		}
		if (temp->type != HERE_DOC)
			delete_quotes(temp->token);
		sub_char(temp->token, 26, '|');
		temp = temp->next;
	}
}

//-----------------------------------------------------------------------------
//iterates through the t_token *tokens linked list to redefine tokens
//token_pretty: expansions, resubs pipes into literal strings, removes quotes
//assign_types: assigns a type to each token
//TODO: handle variable expansion in the HERE_DOC case
int	lexing(t_data *all)
{
	assign_types(all->tokens);
	token_pretty(all);
	assign_types(all->tokens);
	return (0);
}
