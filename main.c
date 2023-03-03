/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 15:48:23 by hwang         #+#    #+#                 */
/*   Updated: 2023/02/21 14:22:40 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

static void	*count_check(void *rules_v)
{
	t_rules	*rules;

	rules = (t_rules *)rules_v;
	while (!check_finish(rules))
	{
		if (reach_count(rules))
		{
			write_log(&rules->philos[0], STATUS_FINISH);
			pthread_mutex_lock(&rules->mutex_finish);
			rules->finish = 1;
			pthread_mutex_unlock(&rules->mutex_finish);
			return (0);
		}
		usleep(1000);
	}
	return (0);
}

static void	*dying_check(void *rules_v)
{
	t_rules	*rules;
	t_philo	*philo;
	int		i;

	rules = (t_rules *)rules_v;
	while (!check_finish(rules))
	{
		i = 0;
		while (i < rules->number_of_philo)
		{
			philo = &rules->philos[i];
			if (check_death(philo))
			{
				write_log(philo, STATUS_DIED);
				pthread_mutex_lock(&philo->rules->mutex_finish);
				philo->rules->finish = 1;
				pthread_mutex_unlock(&philo->rules->mutex_finish);
			}
			i++;
		}
	}
	return (0);
}

static void	*start_eating(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo *)philo_v;
	philo->last_eat = get_time();
	while (!check_finish(philo->rules))
	{
		take_forks(philo);
		eat(philo);
		return_forks(philo);
	}
	return ((void *)0);
}

int	start_simulation(t_rules *rules)
{
	int			i;
	t_philo		*philo;

	rules->start_time = get_time();
	i = 0;
	while (i < rules->number_of_philo)
	{
		philo = &rules->philos[i];
		if (pthread_create(&philo->tid, NULL,
				&start_eating, (void *)philo) != 0)
			return (1);
		i++;
		usleep(100);
	}
	if (pthread_create(&rules->tid_death, NULL,
			&dying_check, (void *)rules) != 0)
		return (1);
	if (rules->must_eat > 0)
	{
		if (pthread_create(&rules->tid_count, NULL,
				&count_check, (void *)rules) != 0)
			return (1);
	}
	join_philo(rules);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (argc < 5 || argc > 6)
		return (error("Wrong number of argument!\n"));
	rules = (t_rules *)malloc((sizeof(t_rules)));
	if (!rules)
		return(error("Simulation failed"));
	if (init_rules(rules, argc, argv))
		return (clean_rules(rules) && error("Simulation failed!\n"));
	if (start_simulation(rules))
		return (clean_rules(rules) && error("Simulation failed!\n"));
	clean_rules(rules);
	return (0);
}