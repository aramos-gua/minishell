/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:47:06 by mtice             #+#    #+#             */
/*   Updated: 2025/07/12 18:59:12 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_double_char(char **arr)
{
	int	j;
	
	j = 0;
	while (arr[j] != NULL)
		free(arr[j++]);
	free(arr);
}

void	handle_error(char *message, char exit_status)
{
	if (errno != 0 && message != NULL)
		perror(message);
	else if (errno == 0 && message != NULL)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(message, 2);
	}
	//free_all(info);
	if (exit_status == 'f')
		exit(EXIT_FAILURE);
	else if (exit_status == 's')
		exit(EXIT_SUCCESS);
}
