/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:28:32 by mtice             #+#    #+#             */
/*   Updated: 2025/08/21 21:40:15 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//-------------------------------------------------------------------------------------
//supporting function to tokeniser() function and other functions within my code
//based on a string, and index and a length, it returns a char *
//helps to find a token within the process string
char *find_token(char *process, int i, int len)
{
	char *p;
	int j;

	if (len == 0)
		return (NULL);
    p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (perror("Malloc error"), NULL);
    j = 0;
	if (p == NULL)
        return (NULL);
    while (len > 0) 
	{
        p[j] = process[i - len];
        len--;
        j++;
    }
    p[j] = '\0';
    return (p);
}

//-------------------------------------------------------------------------------------
//based on t_proc struct (which holds the raw input broken down by pipes)
//splits the process strings into tokens
//builds the t_token *tokens linked list
//SUUPPER IMPORTAAANNNTT
int	tokeniser(t_data *all)
{
	int		i;
	int		len;
	char	*token;
	t_token	*tokens = NULL;

	t_proc	*temp = NULL;
	i = -1;
	while (temp != all->info->next)
	{
		if (i == -1)
			temp = all->info->next;
		i = 0;
		while (temp->proc[i] != '\0')
		{
			while(ft_isspace(temp->proc[i]) && temp->proc[i] != '\0')
				i++;
			len = 0;
			if (temp->proc[i] == '"')
			{
				i++, len++;
				while (temp->proc[i] != '"' && temp->proc[i] != '\0')
					i++, len++;
			}
			else if (temp->proc[i] == '\'')
			{
				i++, len++;
				while (temp->proc[i] != '\'' && temp->proc[i] != '\0')
					i++, len++;
			}
			if (temp->proc[i] == '<')
			{
				i++, len++;
				if (temp->proc[i] == '<')
					i++, len++;
			}
			else if (temp->proc[i] == '>')
			{
				i++, len++;
				if (temp->proc[i] == '>')
					i++, len++;
			}
			else if (!ft_isspace(temp->proc[i]))
			{
				while (!ft_isspace(temp->proc[i]) && temp->proc[i] != '>'
						&& temp->proc[i] != '<' && temp->proc[i] != '\0')
					i++, len++;
			}
			token = find_token(temp->proc, i--, len);
			tokens = add_t_token(tokens, token, temp->process_nbr);
			i++;
		}
		temp = temp->next;
	}
	all->tokens = tokens;
	if (tokens)
		return (0);
	return(1);
}

