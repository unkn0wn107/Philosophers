/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:11:18 by agaley            #+#    #+#             */
/*   Updated: 2023/11/29 23:20:24 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_simu	simuinit;
	t_simu	*simu;
	t_args	args;

	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	simu = &simuinit;
	simu->args = &args;
	args_init(simu, argv, argc);
	if (!args_are_valid(simu, argv, argc))
		return (EXIT_FAILURE);
	simu_init(simu);
	simu_run(simu);
	simu_destroy(simu, 0);
	return (EXIT_SUCCESS);
}

void	args_init(t_simu *simu, char **argv, int argc)
{
	simu->args->num_philos = ft_atoi(argv[1]);
	simu->args->time_to_die = ft_atoi(argv[2]);
	simu->args->time_to_eat = ft_atoi(argv[3]);
	simu->args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		simu->args->min_eats = ft_atoi(argv[5]);
	else
		simu->args->min_eats = -1;
}

int	args_are_valid(t_simu *simu, char **argv, int argc)
{
	char	*str[5];
	int		result;

	result = 1;
	str[0] = ft_itoa(simu->args->num_philos);
	str[1] = ft_itoa(simu->args->time_to_die);
	str[2] = ft_itoa(simu->args->time_to_eat);
	str[3] = ft_itoa(simu->args->time_to_sleep);
	if (argc == 6)
		str[4] = ft_itoa(simu->args->min_eats);
	if (ft_strcmp(argv[1], str[0]) || ft_strcmp(argv[2], str[1])
		|| ft_strcmp(argv[3], str[2]) || ft_strcmp(argv[4], str[3])
		|| (argc == 6 && ft_strcmp(argv[5], str[4])))
		result = 0;
	free(str[0]);
	free(str[1]);
	free(str[2]);
	free(str[3]);
	if (argc == 6)
		free(str[4]);
	if (result == 1
		&& (simu->args->num_philos < 0 || simu->args->time_to_die < 0
			|| simu->args->time_to_eat < 0 || simu->args->time_to_sleep < 0))
		result = 0;
	return (result);
}
