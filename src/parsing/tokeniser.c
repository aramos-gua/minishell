/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:28:32 by mtice             #+#    #+#             */
/*   Updated: 2025/08/09 22:50:44 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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


void	tokeniser(t_data *all)
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
			if (all->info.procs[j][i] == '"')
			{
				i++, len++;
				while (all->info.procs[j][i] != '"' && all->info.procs[j][i] != '\0')
					i++, len++;
			}
			if (all->info.procs[j][i] == '\'')
			{
				i++, len++;
				while (all->info.procs[j][i] != '\'' && all->info.procs[j][i] != '\0')
					i++, len++;
			}
			else if (all->info.procs[j][i] == '<')
			{
				i++, len++;
				if (all->info.procs[j][i] == '<')
					i++, len++;
			}
			else if (all->info.procs[j][i] == '>')
			{
				i++, len++;
				if (all->info.procs[j][i] == '>')
					i++, len++;
			}
			else if (!ft_isspace(all->info.procs[j][i]))
			{
				while (!ft_isspace(all->info.procs[j][i]) && all->info.procs[j][i] != '>'
						&& all->info.procs[j][i] != '<' && all->info.procs[j][i] != '\0')
					i++, len++;
			}
			token = find_token(all->info.procs[j], i--, len);
			tokens = add_at_end(tokens, token, j);
			i++;
		}
		j++;
	}
	all->tokens = tokens;
}

