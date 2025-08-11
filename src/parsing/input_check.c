/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:57:22 by mtice             #+#    #+#             */
/*   Updated: 2025/08/11 08:52:49 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//after looking for syntax errors
//this function breaks the raw input into a 2d array of processes
//stored in the struct t_proc, a pointer stored in t_data *all
void	find_processes(t_data *all, char *input)
{
	t_proc	info;
	int		j;
	char	*temp;
	j = 0;
	info.procs = ft_split(input, '|'); //think about the case where the pipe is in quotes
	ft_printf("The process found is: %s\n", info.procs[0]);
	while (info.procs[j] != NULL)
	{
		temp = info.procs[j];
		info.procs[j] = ft_strtrim(info.procs[j], " ");
		free(temp);
		j++;	
	}
	info.total_proc = j;
	all->info = info;
}

static void	deal_redirect(char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '\0')
	{
		if (input[*i] == '<' && input[*i - 1] == '>')
			printf("bash: syntax error near unexpected token `<'\n");
		else
			printf("bash: syntax error near unexpected token `newline'\n");
	}
	else if (input[*i] == '>' && input[*i + 1] == '\0')
	{
		if (input[*i] == '>' && input[*i - 1] == ' ')
			printf("bash: syntax error near unexpected token `>'\n");
		else
			printf("bash: syntax error near unexpected token `newline'\n");
	}
}

//deals with expansions
static void	deal_expansion(char *input, int *i, int *len)
{
	(void)len;
	if (input[*i] == '$')
		printf("UNIMPLEMENTED: expand variable based on envp copy here\n");
	//must make copy of envp and take from there
	//must alter input with realloc to add in the expansion
}

//deals with multiple pipes case (order of cases matters)
//case1: pipes at the end of input, bash waits for you to finish your input
//case2: two pipes together ("||") with tokens after cancels the effect of proceding commands
//case3: more than two pipes togeth ("|||") is a syntax error
static void	deal_multiple_pipes(char *input, int *i)
{
	int	j;
	char	*syntax;

	j = 0;
	if (input[*i] == '|')
	{
		while (input[(*i)++] == '|')
			j++;
		if (input[*i + 1] == '\0' && j <= 2)
			printf("UNIMPLEMENTED: wait for the rest of input\n");
		else if (j == 2)
			printf("bash: syntax error near unexpected token `|'\n"); //TODO:bonus (||)
		//ft_bzero((input + *i - (j + 1)), ft_strlen(input + *i));
		else if (j > 2)
		{
			j -= 2;
			syntax = malloc(sizeof(char) * (j + 1));
			syntax[j] = '\0';
			while (j-- > 0)
				syntax[j] = '|';
			printf("bash: syntax error near unexpected token `%s'\n", syntax);
			free(syntax);
		}
	}
}

//deals with unclosed quotes and pipes within quotes
//case 1: echo hi "|" world! this is one process only
//replaces a pipe within quotes by ascii 26
//during the tokenisation the pipe will be put back in the string
static void	deal_quotes(char *input, int *i, int *len)
{
	if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] != '\'' && input[*i] != '\0')
		{
			if (input[*i] == '|')
				input[*i] = 26;
			(*i)++;
		}
		if (input[*i] == '\0')
			printf("bash: syntax error unclosed single quote\n");
	}
	else if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] != '"' && input[*i] != '\0')
		{
			if (input[*i] == '|')
				input[*i] = 26;
			else if (input[*i] == '$')
				deal_expansion(input, i, len);
			(*i)++;
		}
		if (input[*i] == '\0')
			printf("bash: syntax error unclosed double quote\n");
	}
}

//processes the raw input before it can be broken down into processes
//looks for syntax errors associated with quotes (single and double)
//pipes in quotes or multiple pipes
//expansion errors (but I will move this to another part of my code)
//and redirect syntax errors
void	process_input(char *input)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(input);
	while (input[i] != '\0' && errno == 0)
	{
		if (input[i] == '\'' || input[i] == '"')
			deal_quotes(input, &i, &len);
		else if (input[i] == '|')
			deal_multiple_pipes(input, &i);
		else if (input[i] == '$')
			deal_expansion(input, &i, &len);
		else if (input[i] == '<' || input[i] == '>')
		 	deal_redirect(input, &i);
		i++;
	}
}
