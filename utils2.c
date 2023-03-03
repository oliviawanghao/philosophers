/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 16:30:10 by hwang         #+#    #+#                 */
/*   Updated: 2022/11/23 21:42:45 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
	{
		return (1);
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_issign(int c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	check_int(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(*str))
		str++;
	if (ft_issign(*str))
	{
		if (*str == '-')
			return (-1);
		else
			str++;
	}
		str++;
	while (ft_isdigit(*str))
		str++;
	while (ft_isspace(*str))
		str++;
	if (*str)
		return (-1);
	return (1);
}

long long	ft_atoi(const char *str)
{
	long long	sign;
	long long	nb;

	sign = 1;
	nb = 0;
	while (*str != 0)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '+' || *str == '-')
		{
			if (*str == '-')
				sign = sign * (-1);
			str++;
		}
		while (*str >= '0' && *str <= '9')
		{
			nb = nb * 10 + (*str - '0');
			str++;
		}
		break ;
	}
	return (nb * sign);
}
