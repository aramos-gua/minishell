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

static int		is_only_quotes(char *token)
{
	int	i;
	int	ret;
	char	c;

	i = 0;
	ret = 0;
	if (token[i] == '\'' || token[i] == '"')
	{
		c = token[i];
		while (token[i] == c && token[i] != '\0')
			i++;
		if (i >= 2)
			ret = 1;
		while (token[i] != '\0' && (token[i] == '\'' || token[i] == '"'))
			i++;
		if (token[i] == '\0' && ret == 1)
			return (1);
		else if (token[i] != '\0' || ret == 0)
			return (0);
	}
	return (0);
}


 //-----------------------------------------------------------------------------
 //determines if a token is a redirection
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

 //-----------------------------------------------------------------------------
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
 		// else if (temp->type == UNDEFINED)
 		// {
 		// 	temp->type = ARGUMENT;
 		// 	if (temp->process_nbr == i && ++i)
 		// 		temp->type = COMMAND;
 		// 	if (temp->type == COMMAND && is_builtin(temp->token))
 		// 		temp->builtin = 1;
 		// }
		else if (temp->process_nbr == i && ++i)
			temp->type = COMMAND;
		else if (temp->type == UNDEFINED)
			temp->type = ARGUMENT;
		if (temp->type == COMMAND && is_builtin(temp->token))
			temp->builtin = 1;
 		if (i < temp->next->process_nbr)
 			i++;
 		temp = temp->next;
 	}
 }

// static void	assign_types(t_token *tokens)
// {
// 	t_token	*temp;
// 	int		i;
//
// 	temp = NULL;
// 	i = -1;
// 	while (temp != tokens->next)
// 	{
// 		if (i == -1 && i++)
// 			temp = tokens->next;
// 		if (temp->process_nbr == i && ++i)
// 			temp->type = COMMAND;
// 		if (temp->type == COMMAND && is_builtin(temp->token))
// 			temp->builtin = 1;
// 		if (temp->type == UNDEFINED && is_redirect(temp->token))
// 			temp->type = OPERATOR;
// 		if (temp->prev->type == OPERATOR)
// 			temp->type = is_redirect(temp->prev->token);
// 		if (temp->type == UNDEFINED)
// 			temp->type = ARGUMENT;
// 		if (i < temp->next->process_nbr)
// 			i++;
// 		// delete_quotes(temp->token);
// 		temp = temp->next;
// 	}
// }


 //-----------------------------------------------------------------------------
 //deletes double quotes or single quotes in the order in which they appear
 void	delete_quotes(char *token)
 {
 	int	i;

 	i = 0;
 	while (token[i] != '\0')
 	{
 		if (token[i] == '"')
 		{
 			del_char(token, i);
 			while (token[i] != '"' && token[i] != '\0')
 				i++;
 			if (token[i] == '"')
 				del_char(token, i);
 		}
 		else if (token[i] == '\'')
 		{
 			del_char(token, i);
 			while (token[i] != '\'' && token[i] != '\0')
 				i++;
 			if (token[i] == '\'')
 				del_char(token, i);
 		}
 		else
 			i++;
 	}
 }

 //-----------------------------------------------------------------------------
 //reformats tokens
 //case 1: if a '$' is present in the token expansion() is called
 //case 2: if quotes are present in the token delete_quotes() is called
 //case 3: if type is HERE_DOC, expansion and quotes are dealt in heredoc.c
 static void	reformat_tokens(t_data *all)
 {
 	t_token	*temp;
 	int		prev;
 	int		i;

 	temp = NULL;
 	i = -1;
 	while (temp != all->tokens->next)
 	{
 		if (i++ == -1)
 			temp = all->tokens->next;
 		temp->pos = i;
 		if (is_only_quotes(temp->token) && temp->type == COMMAND)
 		{
 			temp = temp->next;
 			continue;
 		}
 		else if (ft_strchr(temp->token, '$'))
 		{
 			if (is_redirect(temp->prev->token) != HERE_DOC)
 				expansion(all, temp);
 		}
 		sub_char(temp->token, 26, '|');//, delete_quotes(temp->token));
 		prev = i;
 		i = temp->pos;
 		temp = temp->next;
 		if (i > prev || !ft_strncmp("\0", temp->prev->token, 1))
 		{
 			del_t_token(&(all->tokens), temp->prev->pos);
 			i--;
 		}
 	}
 }

 //-----------------------------------------------------------------------------
 //iterates through the t_token *tokens linked list to redefine tokens
 //reformat_tokens: iterates through tokens and expands and deletes quotes
 //assign_types: assigns a type to each tokens
 //assign_types() must be called twice if env variables have whitespaces in them
 //e.g. export a="cho hello", e$a
 int	lexing(t_data *all)
 {
	t_token	*temp;
	int		i;

	assign_types(all->tokens);
 	reformat_tokens(all);
 	assign_types(all->tokens);
	temp = NULL;
	i = -1;
	while (temp != all->tokens->next)
	{
		if (i++ == -1)
			temp = all->tokens->next;
		delete_quotes(temp->token);
		temp = temp->next;
	}
 	return (0);
 }
