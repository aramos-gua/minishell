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

#include "../../inc/minishell.h"

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
	int		i;
	char	**array;

	i = 0;
	while (all->c_envp[i])
		i++;
	array = ft_calloc((i + 1), sizeof(char *));
	if (!array)
		return (all->return_val = 1, perror("malloc error"));
	i = -1;
	while (all->c_envp[++i] != NULL)
		array[i] = ft_strdup(all->c_envp[i]);
	array[i] = NULL;
	if (all->c_exp)
		free_double_char(all->c_exp);
	all->c_exp = array;
}

//appends a new entry at the end of c_exp array for export of strings 
//that do or not contain a '=' character
static	int	update_exp(t_data *all, char *new_element, t_token *arg_node)
{
	char	**array;
	int		i;
	int		len;

	array = NULL;
	len = ft_strlen(new_element);
	i = exist_in_arr(new_element, all->c_exp, true);
	if (i == -2)
		return (0);
	else if (i != -1 && new_element[len - 1] == '=')
		return (free(all->c_exp[i]), all->c_exp[i] = ft_strdup(arg_node->token), 0);
	i = 0;
	while (all->c_exp[i])
		i++;
	array = ft_calloc((i + 2), sizeof(char *));
	if (!array)
		return (1);
	i = -1;
	while (all->c_exp[++i])
		array[i] = ft_strdup(all->c_exp[i]);
	array[i++] = ft_strdup(arg_node->token);
	array[i] = NULL;
	free_double_char(all->c_exp);
	all->c_exp = array;
	return (0);
}

//updates the two2d array of env by appending a new key/value delimited by '='
static	int	update_envp(t_data *all, char *new_element, t_token *arg_node)
{
	char	**array;
	int		i;

	array = NULL;
	i = exist_in_arr(new_element, all->c_envp, false);
	if (i != -1)
		return (free(all->c_envp[i]), all->c_envp[i] = ft_strdup(arg_node->token), 0);
	i = 0;
	while (all->c_envp[i])
		i++;
	array = malloc((i + 2) * sizeof(char *));
	if (!array)
		return (1);
	i = -1;
	while (all->c_envp[++i])
		array[i] = ft_strdup(all->c_envp[i]);
	array[i++] = ft_strdup(arg_node->token);
	array[i] = NULL;
	free_double_char(all->c_envp);
	all->c_envp = array;
	return (0);
}

int	valid_exp_arg(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (str[0] == '=' || str[0] == '-' || ft_isdigit(str[0]) || str[0] == '+' || str[0] == '?')
		return (1);
	while (str[i] && (ft_isalpha(str[0]) || str[0] == '_'))
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]) && str[i] != '=')
			ret = 1;
		i++;
	}
	return (ret);
}

//recreates the export builtin function, handling keys not containing
//'=' char, and prepending information on export
int	ft_export(t_data *all, int proc, t_token *cmd_node)
{
	t_token	*arg;
	char	*key_val;

	key_val = NULL;
	if (all->total_proc > 1)
		return (all->return_val = 1, 1);
	if ((ft_lstsize(all->tokens, proc)) == 1)
		ft_print_exp(all);
	arg = cmd_node->next;
	while (arg->type == ARGUMENT && arg->process_nbr == proc)
	{
		if (arg->token && valid_exp_arg(arg->token))
		{
			export_error(all, arg);
			break ;
		}
		key_val = nullify(arg->token);
		if (key_val && key_val[ft_strlen(key_val) - 1] == '=')
			update_envp(all, key_val, arg);
		update_exp(all, key_val, arg);
		arg = arg->next;
		if (key_val)
			free(key_val);
	}
	return (1);
}
