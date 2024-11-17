#include "minitalk_bonus.h"

static t_client_overall    client_overall;

void	context_sender(int serversig, siginfo_t *info, void *context)
{
	unsigned char	tmp;

	(void)serversig;
	(void)info;
	(void)context;
	if (client_overall.i >= 8)
	{
		client_overall.i = 0;
		client_overall.str++;
		if (*(client_overall.str) == '\0')
			exit(0);
	}
	tmp = (*(client_overall.str) & 1);
	*(client_overall.str) >>= 1;
	client_overall.i++;
	if(tmp == 1)
	{
		if (kill(client_overall.pid, SIGUSR2) == -1)
			ft_printf("%s\n", "kill error, signal cannot be sent");
	}
	else
	{
		if (kill(client_overall.pid, SIGUSR1) == -1)
			ft_printf("%s\n", "kill error, signal cannot be sent");
	}
	// if (kill(client_overall.pid, tmp + SIGUSR1) == -1)
	// 	ft_printf("%s\n", "kill error, signal cannot be sent");
}

int	main(int ac, char **av)
{
	if (ac < 3)
		ft_printf("%s\n", "there have to be at least 2 arguments");
	if (ac > 3)
		ft_printf("%s\n", "too many arguments");
	client_overall.pid = ft_atoi(av[1]);
	client_overall.str = av[2];
	client_overall.i = 0;
	client_overall.sa.sa_flags = SA_SIGINFO;
	client_overall.sa.sa_sigaction = context_sender;
	if (sigaction(SIGUSR1, &(client_overall.sa), NULL) == -1)
		ft_printf("%s\n", "sigaction error");
	context_sender(0, NULL, NULL);
	while (1)
		pause();
	return (0);
}