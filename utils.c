/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 15:50:43 by hwang         #+#    #+#                 */
/*   Updated: 2022/11/23 21:26:59 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr_fd(uint64_t n, int fd)
{
	char	str[13];
	int		length;

	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (length > 0)
		length--;
	while (length >= 0)
		write(fd, &str[length--], 1);
}

int	get_rules(char *str)
{
	int			ret;
	long long	nb;

	ret = check_int(str);
	if (ret > 0)
	{
		nb = ft_atoi(str);
		if (nb <= INT_MAX)
		{
			ret = (int)nb;
			return (ret);
		}
	}
	else if (ft_atoi(str) == 0)
	{
		ret = 0;
		return (ret);
	}
	ret = -1;
	return (ret);
}

int	get_time_rules(char *str)
{
	int			ret;
	long long	nb;

	ret = check_int(str);
	if (ret > 0)
	{
		nb = ft_atoi(str);
		if (nb <= INT_MAX)
		{
			ret = (int)nb;
			return (ret);
		}
	}
	ret = 0;
	return (ret);
}
