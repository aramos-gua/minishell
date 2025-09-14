/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:25:02 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/14 13:10:09 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//checks if a string exist in an array index, flag is true when last char is a 
//delimiter (Eg. HOME= Vs norminette)
int	exist_in_arr(char *str, char **array, bool exp)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	if (exp == true)
		if (ft_strchr(str, '='))
			len -= 1;
	while (array[i])
	{
		if (ft_strncmp(str, array[i], len) == 0)
		{
			if (!exp)
				return (i);
			else if (exp && ft_strchr(str, '='))
				return (i);
			else
				return (-2);
		}
		i++;
	}
	return (-1);
}

//creates a duplicate two2d array of env
void	fill_exp(t_data *all)
{
	int	i;

	i = 0;
	while (all->c_envp[i])
		i++;
	all->c_exp = ft_calloc((i + 1), sizeof(char *));
	if (!all->c_exp)
		return (all->return_val = 1, perror("malloc error"));
	i = 0;
	while (all->c_envp[i])
	{
		all->c_exp[i] = ft_strdup(all->c_envp[i]);
		i++;
	}
	all->c_exp[i] = NULL;
}

//appends a new entry at the end of c_exp array for export of strings 
//that do or not contain a '=' character
static char	**update_exp(t_data *all, char *new_element, t_token *arg_node)
{
	char	**array;
	int		i;
	int		len;

	len = ft_strlen(new_element);
	i = exist_in_arr(new_element, all->c_exp, true);
	if (i == -2)
		return (all->c_exp);
	if (i != -1 && new_element[len - 1] == '=')
		return (ft_strlcpy(all->c_exp[i], \
		arg_node->token, ft_strlen(arg_node->token) + 1), all->c_exp);
	i = 0;
	while (all->c_exp[i])
		i++;
	array = malloc((i + 2) * sizeof(char *));
	if (!array)
		return (all->return_val = 1, NULL);
	i = -1;
	while (all->c_exp[++i])
		array[i] = all->c_exp[i];
	array[i++] = ft_strdup(arg_node->token);
	array[i] = NULL;
	return (array);
}

//updates the two2d array of env by appending a new key/value delimited by '='
static char	**update_envp(t_data *all, char *new_element, t_token *arg_node)
{
	char	**array;
	int		i;

	i = exist_in_arr(new_element, all->c_envp, false);
	if (i != -1)
		return (ft_strlcpy(all->c_envp[i], arg_node->token, \
		ft_strlen(arg_node->token) + 1), all->c_envp);
	i = 0;
	while (all->c_envp[i])
		i++;
	array = malloc((i + 2) * sizeof(char *));
	if (!array)
		return (all->return_val = 1, NULL);
	i = 0;
	while (all->c_envp[i])
	{
		array[i] = all->c_envp[i];
		i++;
	}
	array[i++] = ft_strdup(arg_node->token);
	array[i] = NULL;
	return (array);
}

//recreates the export builtin function, handling keys not containing
//'=' char, and prepending information on export
int	ft_export(t_data *all, int proc, t_token *cmd_node)
{
	t_token	*arg;
	char	*key_val;

	if (all->total_proc > 1)
		return (1);
	if (all->c_exp == NULL)
		fill_exp(all);
	if ((ft_lstsize(all->tokens, proc)) == 1)
		ft_print_exp(all);
	arg = cmd_node->next;
	while (arg->type == ARGUMENT && arg->process_nbr == proc)
	{
		if (arg->token && (!ft_isalpha(arg->token[0]) && arg->token[0] != '_'))
		{
			export_error(all, arg);
			break ;
		}
		key_val = nullify(arg->token);
		if (key_val[ft_strlen(key_val) - 1] == '=')
			all->c_envp = update_envp(all, key_val, arg);
		all->c_exp = update_exp(all, key_val, arg);
		arg = arg->next;
	}
	return (1);
}
