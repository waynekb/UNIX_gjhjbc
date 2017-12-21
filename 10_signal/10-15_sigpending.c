#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void sig_quit(int);

int main(void)
{
    sigset_t newmask,oldmask,pendmask;
    signal(SIGQUOIT, sig_quit);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);
    sleep(5);
    sigpending(&pendmask)
}