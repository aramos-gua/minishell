/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:05:41 by mtice             #+#    #+#             */
/*   Updated: 2025/07/25 21:14:38 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_env(t_data *all)
{
	int	j;

	j = 0;
	while (all->c_envp[j] != NULL && all->c_envp[j][0] != '\0')
		printf("%s\n", all->c_envp[j++]);
}

int	find_envp(t_data *all, char *envp[])
{
	int	j;

	j = 0;
	while (envp[j] != NULL)
		j++;
	if (envp[j] == NULL && j == 0)
		return (1);
	all->c_envp = malloc(sizeof(char *) * (j + 1));
	j = 0;
	while (envp[j] != NULL)
	{
		all->c_envp[j] = ft_strdup(envp[j]);
		j++;
	}
	all->c_envp[j] = NULL;
	all->c_exp = NULL;
	return (0);
}
