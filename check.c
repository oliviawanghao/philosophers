/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 14:15:01 by hwang         #+#    #+#                 */
/*   Updated: 2022/11/22 19:31:41 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	check_finish(t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex_finish);
	if (rules->finish == 1)
	{
		pthread_mutex_unlock(&rules->mutex_finish);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&rules->mutex_finish);
		return (0);
	}
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (!(philo->is_eating) && (get_time()
			> (philo->last_eat + philo->rules->time_to_die)))
	{
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->mutex);
		return (0);
	}
}

int	reach_count(t_rules *rules)
{
	t_philo	*philo;
	int		must_eat;
	int		i;
	int		reached_philo_count;

	must_eat = rules->must_eat;
	i = 0;
	reached_philo_count = 0;
	while (i < rules->number_of_philo)
	{
		philo = &rules->philos[i];
		pthread_mutex_lock(&philo->mutex);
		if (philo->eat_count >= must_eat)
		{
			reached_philo_count++;
		}
		pthread_mutex_unlock(&philo->mutex);
		i++;
	}
	if (reached_philo_count == rules->number_of_philo)
		return (1);
	else
		return (0);
}

void	join_philo(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philo)
	{
		pthread_join(rules->philos[i].tid, NULL);
		i++;
	}
	pthread_join(rules->tid_death, NULL);
	if (rules->must_eat > 0)
		pthread_join(rules->tid_count, NULL);
}
