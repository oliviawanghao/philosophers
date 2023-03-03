/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hwang <hwang@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 15:56:06 by hwang         #+#    #+#                 */
/*   Updated: 2022/11/23 20:50:23 by hwang         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

# define STATUS_EAT		0
# define STATUS_FORK	1
# define STATUS_SLEEP	2
# define STATUS_THINK	3
# define STATUS_DIED	4
# define STATUS_FINISH	5

struct	s_rules;

typedef struct s_philo
{
	int				position;
	int				is_eating;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	uint64_t		last_eat;
	struct s_rules	*rules;
	pthread_mutex_t	mutex;
	pthread_t		tid;
}	t_philo;

typedef struct s_rules
{
	int					number_of_philo;
	uint64_t			time_to_die;
	uint64_t			time_to_eat;
	uint64_t			time_to_sleep;
	int					must_eat;
	uint64_t			start_time;
	t_philo				*philos;
	pthread_mutex_t		*mutex_forks;
	pthread_mutex_t		mutex_log;
	pthread_mutex_t		mutex_finish;
	int					finish;
	pthread_t			tid_death;
	pthread_t			tid_count;
}	t_rules;

int			ft_strlen(char const *str);
long long	ft_atoi(const char *str);
int			check_int(char *str);
int			get_rules(char *str);
int			get_time_rules(char *str);
void		ft_putnbr_fd(uint64_t n, int fd);
int			error(char *str);

uint64_t	get_time(void);
void		ft_usleep(uint64_t time_in_ms);
int			one_philo(int time_to_die);
void		write_log(t_philo *philo, int status);
int			init_rules(t_rules *rules, int argc, char **argv);
int			clean_rules(t_rules *rules);

void		eat(t_philo *philo);
void		take_forks(t_philo *philo);
void		return_forks(t_philo *philo);

int			check_finish(t_rules *rules);
int			check_death(t_philo *philo);
int			reach_count(t_rules *rules);
void		join_philo(t_rules *rules);

#endif