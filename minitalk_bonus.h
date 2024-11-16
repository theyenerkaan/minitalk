#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# define _POSIX_C_SOURCE 200809L

# include <signal.h>
# include <stdlib.h>

typedef struct s_overall_client
{
	struct sigaction	sa;
	pid_t				pid;
	char			    *str;
	int					i;
}	t_client_overall;

typedef struct s_overall_server
{
	unsigned char	c;
	int				i;
	pid_t			pid;
}	t_server_overall;

int	ft_atoi(const char *str);

#endif