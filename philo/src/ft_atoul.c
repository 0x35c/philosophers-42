/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:21:00 by ulayus            #+#    #+#             */
/*   Updated: 2023/03/08 14:33:42 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

long	ft_atoul(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] < 58 && nptr[i] > 47)
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	if (result * sign > 2146473647 || result * sign < 0)
		return (-1);
	return (result * sign);
}
