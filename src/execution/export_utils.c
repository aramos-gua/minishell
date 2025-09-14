/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_stdout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 13:07:59 by aramos            #+#    #+#             */
/*   Updated: 2025/09/14 13:09:31 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//returns and int corresponding to the index of the occurrence of '='. Inclusive
int	var_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (i + 1);
	return (-1);
}

//returns a substring of a string up to '=' char or \0
char	*nullify(char *cmd)
{
	int		len;
	char	*cmd_cut;

	len = var_len(cmd);
	cmd_cut = ft_substr(cmd, 0, len);
	return (cmd_cut);
}

//handles the addition of "" to the value portion of the export entries
void	ft_putexp(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
	write(STDOUT_FILENO, &str[i++], 1);
	write(STDOUT_FILENO, "\"", 2);
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
	ft_putendl_fd("\"", STDOUT_FILENO);
}

//prints the keys and values to STDOUT prepending and handling ""
int	ft_print_exp(t_data *all)
{
	int	i;

	i = 0;
	while (all->c_exp[i])
	{
		if (all->c_exp[i][0] == '\0')
		{
			i++;
			continue ;
		}
		ft_dprintf(STDOUT_FILENO, "declare -x ");
		if (ft_strchr(all->c_exp[i], '='))
			ft_putexp(all->c_exp[i]);
		else
			ft_dprintf(STDOUT_FILENO, "%s\n", all->c_exp[i]);
		i++;
	}
	return (1);
}

void	export_error(t_data *all, t_token *arg)
{
	ft_dprintf(2, "minishell: export: \'%s\': %s\n", arg->token, INV_ARG);
	all->return_val = 1;
	arg = arg->next;
	return ;
}
