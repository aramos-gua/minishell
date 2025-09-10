/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:01:37 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 13:01:39 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	dprintf_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

//#include <stdio.h>
//int	main(void)
//{
//	printf("%c", (char)ft_toupper(56));
//	return (0);
//}
