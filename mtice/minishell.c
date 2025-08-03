/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:30:15 by mtice             #+#    #+#             */
/*   Updated: 2025/07/23 09:38:18 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

static char	*ft_string_in_pointer(char const *s, int i, int len)
{
	char	*p;
	int		j;

	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	j = 0;
	while (len > 0)
	{
		p[j] = s[i - len];
		len --;
		j++;
	}
	p[j] = '\0';
	return (p);
}

char	**find_processes(char *input)
{
	int		i;
	int		j;
	int		k;
	char 	**processes;
	char	*start;

	start = "start";
	i = 0;
	j = 0;
	k = 0;
	int strings = 5;
	processes = malloc(sizeof(char *) * (strings + 1));
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
	  	{
	  		input[i] = processes[j][k];
			i++, k++;
			while (input[i] != '\'' && input[i] != '\0')
			{
		  		input[i] = processes[j][k];
				i++, k++;
			}
			if (input[i] == '\0')
			{
				printf("syntax error: unclosed single quotes\n");
				return (NULL);
			}
			
		}
		else if (input[i] == '\"')
		{
			input[i] = processes[j][k];
			i++, k++;
			while (input[i] != '\"' && input[i] != '\0')
			{
				input[i] = processes[j][k];
				i++,k++;
			}
			if (input[i] == '\0')
			{
				printf("syntax error: unclosed double quotes\n");
				return (NULL);
			}
		}
		else if (input[i] == '|')
		{
			j++, i++;
			k = 0;
			if (input[i] == '|')
				i++;
			if (input[i] == '|')
			{
				while (input[i] == '|')
					i++, k++;
				char *error = malloc(sizeof(char) * (k + 1));
				while (k-- > 0)
					*error++ = input[i - k];
				*error = '\0';
				printf("-bash: syntax error near unexpected token `%s'\n", error);
				return (NULL);
			}
		}
		else {
			input[i] = processes[j][k];
			i++, k++;
		}
		processes[j][k] = '\0';
		return (processes);
		//  	else if (isspace(input[i]))
		// {
		// 	while (isspace(input[i]) && input[i] != '\0')
		// 	{
		// 		intput[i] = processes[j][k];
		// 		i++, k++;
		// 	}
		// 	if (input[i] == '\0')
		// 	{
		// 		processes[j][k] = '\0';
		// 		return(processes);
		// 	}
		// }
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	char **processes;

	if (argc != 2)
	{
		printf("Only two argc allowed!\n");
		return (1);
	}
	else {
		processes = find_processes(argv[1]);
	}
}
