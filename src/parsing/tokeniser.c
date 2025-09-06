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

//------------------------------------------------------------------------------
//supporting function to tokeniser() function and other functions within my code
//based on a string, and index and a length, it returns a char *
//helps to find a token within the process string
char	*find_token(char *process, int i, int len)
{
	char	*p;
	int		j;

	if (len == 0)
		return (NULL);
	p = ft_calloc(sizeof(char), (len + 1));
	if (!p)
		return (NULL);
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

//-----------------------------------------------------------------------------
//used to help single out tokens
//used within a while loop to skip until a certain delimiter char is found
//used to bypass a condition in a while loop, if it should be ignored
//(e.g. if quotes are found we want to iterate through whitespaces as well)
void	skip_to(char *process, char skip_to, int *i, int *len)
{
	(*i)++;
	(*len)++;
	if ((process[*i - 1] == '<' && process[*i] == '<')
		|| (process[*i - 1] == '>' && process[*i] == '>'))
	{
		(*i)++;
		(*len)++;
	}
	else if ((process[*i - 1] == '<' && process[*i] != '<')
		|| (process[*i - 1] == '>' && process[*i] != '>'))
		return ;
	else
	{
		while (process[*i] != skip_to && process[*i] != '\0')
		{
			(*i)++;
			(*len)++;
		}
		(*i)++;
		(*len)++;
	}
}

//-----------------------------------------------------------------------------
//breaks down the processes stored in t_proc into tokens
//stores the tokens into t_token *tokens struct stored in t_data *all
int	tokeniser(t_data *all)
{
	int		i;
	int		len;
	char	*token;
	t_proc	*temp;

	i = -1;
	temp = NULL;
	while (temp != all->info->next)
	{
		if (i == -1)
			temp = all->info->next;
		i = 0;
		while (temp->proc[i] != '\0')
		{
			len = 0;
			while (ft_isspace(temp->proc[i]) && temp->proc[i] != '\0')
				i++;
			if (temp->proc[i] == '<' || temp->proc[i] == '>')
				skip_to(temp->proc, temp->proc[i], &i, &len);
			else if (!ft_isspace(temp->proc[i]))
			{
				while (!ft_isspace(temp->proc[i]) && temp->proc[i] != '<'
					&& temp->proc[i] != '>' && temp->proc[i] != '\0')
				{
					if (temp->proc[i] == '"' || temp->proc[i] == '\'' )
						skip_to(temp->proc, temp->proc[i], &i, &len);
					else
					{
						i++;
						len++;
					}
				}
			}
			token = find_token(temp->proc, i--, len);
			all->tokens = add_t_token(all->tokens, token, temp->process_nbr);
			i++;
		}
		temp = temp->next;
	}
	if (!(all->tokens))
		return (1);
	return (0);
}
