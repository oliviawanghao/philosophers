/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 15:43:59 by hwang         #+#    #+#                 */
/*   Updated: 2022/11/23 21:37:57 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	init_mutexes(t_rules *rules)
{
	int	i;

	pthread_mutex_init(&rules->mutex_log, NULL);
	pthread_mutex_init(&rules->mutex_finish, NULL);
	rules->mutex_forks = (pthread_mutex_t *)malloc(sizeof(*(rules->mutex_forks))
			* rules->number_of_philo);
	if (!rules->mutex_forks)
		return (1);
	i = 0;
	while (i < rules->number_of_philo)
	{
		pthread_mutex_init(&rules->mutex_forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philos(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philo)
	{
		rules->philos[i].position = i;
		rules->philos[i].is_eating = 0;
		rules->philos[i].left_fork = i;
		rules->philos[i].right_fork = (i + 1) % (rules->number_of_philo);
		rules->philos[i].eat_count = 0;
		rules->philos[i].rules = rules;
		pthread_mutex_init(&rules->philos[i].mutex, NULL);
		i++;
	}
	return (0);
}

void	set_rules(t_rules *rules, char **argv)
{
	rules->number_of_philo = get_rules(argv[1]);
	rules->time_to_die = get_time_rules(argv[2]);
	rules->time_to_eat = get_time_rules(argv[3]);
	rules->time_to_sleep = get_time_rules(argv[4]);
}

int	init_rules(t_rules *rules, int argc, char **argv)
{
	set_rules(rules, argv);
	if (argc == 6)
	{
		rules->must_eat = get_rules(argv[5]);
		if (rules->must_eat == 0)
			return (1);
	}
	else
		rules->must_eat = 0;
	if (rules->number_of_philo < 1 || rules->time_to_die <= 0
		|| rules->time_to_eat <= 0 || rules->time_to_sleep <= 0
		|| rules->must_eat < 0)
		return (error("Bad argument!\n"));
	if (rules->number_of_philo == 1)
		return (one_philo(rules->time_to_die));
	rules->philos = NULL;
	rules->mutex_forks = NULL;
	rules->philos = (t_philo *)malloc(sizeof(*(rules->philos))
			* rules->number_of_philo);
	if (!rules->philos)
		return (1);
	rules->finish = 0;
	init_philos(rules);
	return (init_mutexes(rules));
}

int	clean_rules(t_rules *rules)
{
	int	i;

	if (rules->mutex_forks)
	{
		i = 0;
		while (i < rules->number_of_philo)
			pthread_mutex_destroy(&rules->mutex_forks[i++]);
		free(rules->mutex_forks);
	}
	if (rules->philos)
	{
		i = 0;
		while (i < rules->number_of_philo)
			pthread_mutex_destroy(&rules->philos[i++].mutex);
		free(rules->philos);
	}
	pthread_mutex_destroy(&rules->mutex_log);
	pthread_mutex_destroy(&rules->mutex_finish);
	free(rules);
	return (0);
}
