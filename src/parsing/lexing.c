/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:37:41 by mtice             #+#    #+#             */
/*   Updated: 2025/08/03 20:10:57 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//assigns to each t_token its type, as defined in the enum t_type
//must handle specific cases
//redirect case: when input echo hello > out1, i want the token to be attached to its operator
//i.e. >out1 will be one token, where > defines redirect_out and out1 is the name of the outfile
//string case: an argument may be a string when it is within quotes " " or ' '
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
		else if (temp->token[0] == '<' && temp->token[1] != '<')
			temp->type = RE_IN;
		else if (!ft_strncmp(temp->token, "<<", 2))
			temp->type = HERE_DOC;
		else if (temp->token[0] == '>' && temp->token[1] != '>')
			temp->type = RE_OUT;
		else if (!ft_strncmp(temp->token, ">>", 2))
			temp->type = APPEND;
		else if (temp->process_nbr > i)
			temp->type = COMMAND;
		else
		 	temp->type = ARGUMENT;
		if (temp->process_nbr > i)
			i++;
		temp = temp->next;
	}
}

//TODO: remove do... while loop
static void	token_pretty(t_token *tokens)
{
	t_token	*temp;
	char	*old_token;

	temp = tokens->next;
	do
	{
		if (ft_strchr(temp->token, '\'') || ft_strchr(temp->token, '"'))
		{
			del_char(temp->token, '\'');
			del_char(temp->token, '"');
			sub_char(temp->token, 26, '|');
		}
		else if (temp->token[0] == '<' && temp->token[1] == '\0')
		{
			temp = temp->next;
			del_last(temp->prev);
			old_token = temp->token;
			temp->token = ft_strjoin("<", old_token);
			free(old_token);
		}
		else if (!ft_strncmp(temp->token, ">>\0", 3))
		{
			temp = temp->next;
			del_last(temp->prev);
			old_token = temp->token;
			temp->token = ft_strjoin(">>", old_token);
			free(old_token);
		}
		else if (temp->token[0] == '>' && temp->token[1] == '\0')
		{
			temp = temp->next;
			del_last(temp->prev);
			old_token = temp->token;
			temp->token = ft_strjoin(">", old_token);
			free(old_token);
		}
		temp = temp->next;
	} while (temp != tokens->next);
}

static char *find_token(char *process, int i, int len)
{
	char *p;
	int j;

	if (len == 0)
		return (NULL);
    p = malloc(sizeof(char) * (len + 1));
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


void	lexing(t_data *all)
{
	int		i;
	int		j;
	int		len;
	char	*token;
	t_token	*tokens = NULL;

	j = 0;
	while (all->info.procs[j] != NULL)
	{
		i = 0;
		while (all->info.procs[j][i] != '\0')
		{
			while(ft_isspace(all->info.procs[j][i]) && all->info.procs[j][i] != '\0')
				i++;
			len = 0;
			while(!ft_isspace(all->info.procs[j][i]) && all->info.procs[j][i] != '\0')
			{
				if (all->info.procs[j][i + 1] == '<' || all->info.procs[j][i + 1] == '>')
				{
					i++, len++;
					break;
				}
				else if (all->info.procs[j][i] == '"')
				{
					i++, len++;
					while (all->info.procs[j][i] != '"' && all->info.procs[j][i] != '\0')
						i++, len++;
					i++, len++;
					break;
				}
				else if (all->info.procs[j][i] == '\'')
				{
					i++, len++;
					while (all->info.procs[j][i] != '\'' && all->info.procs[j][i] != '\0')
						i++, len++;
					i++, len++;
					break;
				}
				i++, len++;
			}
			token = find_token(all->info.procs[j], i, len);
			tokens = add_at_end(tokens, token, j);
		}
		j++;
	}
	token_pretty(tokens);
	assign_types(tokens);
	all->tokens = tokens;
}
