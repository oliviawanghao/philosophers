/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 15:45:12 by hwang         #+#    #+#                 */
/*   Updated: 2022/11/24 18:43:28 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

uint64_t	get_time(void)
{
	static struct timeval	start = {0, 0};
	struct timeval			now;

	if (start.tv_sec == 0 && start.tv_usec == 0 && \
	gettimeofday(&start, 0))
		return (1);
	if (gettimeofday(&now, 0))
		return (1);
	return (((now.tv_sec * 1000000 + now.tv_usec) - \
	(start.tv_sec * 1000000 + start.tv_usec)) / 1000);
}

void	ft_usleep(uint64_t time_in_ms)
{
	uint64_t	start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(200);
}

char	*get_message(int status)
{
	if (status == STATUS_EAT)
		return (" is eating\n");
	else if (status == STATUS_SLEEP)
		return (" is sleeping\n");
	else if (status == STATUS_FORK)
		return (" has taken a fork\n");
	else if (status == STATUS_THINK)
		return (" is thinking\n");
	else if (status == STATUS_FINISH)
		return ("must eat count reached\n");
	return (" died\n");
}

int	one_philo(int time_to_die)
{
	ft_putnbr_fd(0, 1);
	write(1, "\t", 1);
	ft_putnbr_fd(1, 1);
	write(1, get_message(STATUS_FORK), ft_strlen(get_message(STATUS_FORK)));
	ft_putnbr_fd(time_to_die + 1, 1);
	write(1, "\t", 1);
	ft_putnbr_fd(1, 1);
	write(1, get_message(STATUS_DIED), ft_strlen(get_message(STATUS_DIED)));
	return (1);
}

void	write_log(t_philo *philo, int status)
{
	static int	finish = 0;

	pthread_mutex_lock(&philo->rules->mutex_log);
	if (!finish)
	{
		ft_putnbr_fd(get_time() - philo->rules->start_time, 1);
		write(1, "\t", 1);
		if (status < STATUS_FINISH)
			ft_putnbr_fd(philo->position + 1, 1);
		if (status == STATUS_DIED || status == STATUS_FINISH)
			finish = 1;
		write(1, get_message(status), ft_strlen(get_message(status)));
	}
	pthread_mutex_unlock(&philo->rules->mutex_log);
}
