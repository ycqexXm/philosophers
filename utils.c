/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 04:28:57 by yorlians          #+#    #+#             */
/*   Updated: 2023/06/30 15:50:39 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
		put character
*/
void	put_char(char c, int fd)
{
	write (fd, &c, 1);
}

/*
	put string
*/
void	put_string(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		put_char(s[i], fd);
		i++;
	}
}

/*
	check if its a digit
*/
int	digit_check(char *c)
{
	while (c && *c)
	{
		if (*c < '0' || *c > '9')
			return (0);
		c++;
	}
	return (1);
}

/*
	determine whether a given string
	represents a valid integer value
*/
int	is_int(char *str)
{
	int		i;
	int		result;

	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		if (result > 2147483647)
			return (-1);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (1);
}

/*
	convert a string representation of an integer
			to an actual integer value
*/
int	atoi_philo(char *str)
{
	int		i;
	int		result;

	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}
