/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 15:41:05 by hwang         #+#    #+#                 */
/*   Updated: 2022/11/23 20:58:45 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

/*
根据当前philo左右手的叉子号，锁住相应号码的mutex_forks，并写下log。
这样其他philo的线程就不可以再得到该叉子。
*/
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->mutex_forks[philo->left_fork]);
	write_log(philo, STATUS_FORK);
	pthread_mutex_lock(&philo->rules->mutex_forks[philo->right_fork]);
	write_log(philo, STATUS_FORK);
}

/*
一个philo得到叉子后，就开始吃东西，需要先把该philo的mutex锁住。
（保证纯吃饭，这样数吃饭次数的线程，就不能check了）
写下log后，开始吃饭。（用usleep挂起线程）
吃完后eat_count加一。
*/
void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat = get_time();
	philo->is_eating = 1;
	write_log(philo, STATUS_EAT);
	pthread_mutex_unlock(&philo->mutex);
	ft_usleep(philo->rules->time_to_eat);
	pthread_mutex_lock(&philo->mutex);
	philo->eat_count++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
}

/*
根据当前philo左右手的叉子号，分别解锁相应号码的mutex_forks。（释放给其他线程）
还回叉子后开始睡觉，写下log后，开始睡觉。（用usleep挂起线程）
睡完后写下think的log，think的过程相当于等待叉子的过程，一旦得到叉子，又可以开始吃饭。
*/
void	return_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rules->mutex_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->rules->mutex_forks[philo->right_fork]);
	write_log(philo, STATUS_SLEEP);
	ft_usleep(philo->rules->time_to_sleep);
	write_log(philo, STATUS_THINK);
}
