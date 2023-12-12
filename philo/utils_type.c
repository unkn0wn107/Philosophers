/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 01:04:20 by agaley            #+#    #+#             */
/*   Updated: 2023/11/16 02:21:47 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Converts a string to an integer.
 *
 * @param str The string to convert.
 *
 * @returns The integer representation of the string.
 */
int	ft_atoi(const char *str)
{
	int					sign;
	size_t				i;
	unsigned long int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (result != (10 * result + (str[i] - '0')) / 10)
			return ((sign + 1) / -2);
		result = 10 * result + (str[i] - '0');
		i++;
	}
	return ((int)(sign * result));
}

int	ft_nbrlen(int nbr)
{
	int			i;
	int			min;
	long int	n;

	i = 0;
	min = 0;
	n = nbr;
	if (n < 0)
	{
		n *= -1;
		min = 1;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (++i + min);
}

void	ft_nbrcpy(char *str, int nbr)
{
	long int	n;

	n = nbr;
	if (n < 0)
		n *= -1;
	str = str + ft_nbrlen(nbr);
	*(str--) = '\0';
	if (n == 0)
		*(str--) = '0';
	while (n != 0)
	{
		if (n < 10)
			*(str--) = n + '0';
		else
			*(str--) = n % 10 + '0';
		n /= 10;
	}
	if (nbr < 0)
		*str = '-';
}

/**
 * Converts an integer to a string.
 *
 * @param nbr The integer to convert.
 *
 * @returns The string representation of the integer.
 */
char	*ft_itoa(int nbr)
{
	char		*str;

	str = (char *)malloc((1 + ft_nbrlen(nbr)) * sizeof(char));
	if (!str)
		return (NULL);
	ft_nbrcpy(str, nbr);
	return (str);
}
