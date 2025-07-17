#include "ft_printf.h"
#include <unistd.h>
#include <signal.h>

static int g_msg_len = 0;

static int handle_len(int sig)
{
    static int bit = 0;
    if (bit == 0)
        g_msg_len = 0;
    if (sig == SIGUSR1)
        g_msg_len |= (1 << (31 - bit));
    bit++;
    if (bit == 32)
    {
        ft_printf("Message length: %d\n", g_msg_len);
        bit = 0;
        return (1);
    }
    return (0);
}

static void handle_msg(int sig)
{
    static int bit = 0;
    static char c = 0;
    static char msg[1000] = {0}; // Assuming a max message length of 1000
    static int i = 0;

    
    if (sig == SIGUSR1)
        c |= (1 << (7 - bit));
    bit++;
    if (bit == 8)
    {
        msg[i++] = c;
        if (c == '\0' || i == g_msg_len)
        {
            ft_printf("%s\n", msg);
            g_msg_len = 0;
            i = 0;
            bit = 0;
            c = 0;
        }
        bit = 0;
        c = 0;
    }
}

void handle_signal(int sig)
{
    static int receiving_len = 1;
    if (receiving_len)
        receiving_len = !handle_len(sig);
    else
        handle_msg(sig);
}

int main(void)
{
    ft_printf("PID : %d\n", getpid());
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);
    while (1)
        pause();
    return (0);
}