#include "minitalk_bonus.h"

void    context_handler(int signal, siginfo_t *info, void *context)
{
    static unsigned char    c;
    static unsigned char    k;
    int                     i;
    pid_t                   pid;

    (void)signal;
    (void)info;
    (void)context;
    if (i >= 8)
    {
        i = 0;
        k++;
        if (k == '\0')
            exit(0);
    }
    c = k & 1;
    k >>= 1;
    i++;
    if(kill(pid, c + SIGUSR1) == -1)
        ft_printf("%s\n", "kill error");
}

int main(int ac, char **av)
{
    struct sigaction    sig;
    pid_t   pid;
    char    *content;
    int     i;

    if (ac < 3)
        ft_printf("%s\n", "there have to be at least 2 arguments");
    if (ac > 3)
        ft_printf("%s\n", "too many arguments");
    pid = ft_atoi(av[1]);
    content = av[2];
    i = 0;
    sig.sa_flags = SA_SIGINFO;
    sig.sa_sigaction = context_handler;
    if (sigaction(SIGUSR1, &sig, NULL) == -1)
        ft_printf("%s\n", "sigaction error");
    context_handler(0, NULL, NULL);
    while (1)
        pause();
    return (0);
}