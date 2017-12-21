#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_int(int);
int main(void)
{
    int i=0;
    sigset_t newmask, oldmask, waitmask;
    printf("program start:\n");
    if(signal(SIGINT, sig_int) == SIG_ERR){
        printf("signal error\n");
        return -1;
    }
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) <0){
        printf("SIG_BLOCK ERROR\n");
        return -1;
    }
    printf("in critical region:\n");
    while(i<10)
    {
        printf("%d\n",i);
        i++;
        sleep(1);
    }
    
    if(sigsuspend(&waitmask) !=-1){
        printf("sigsupend error\n");
        return -1;
    }

    printf("after return from sigsusspend:\n");

    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) <0){
        printf("SIG_SETMASK ERROR\n");
        return -1;
    }
    printf("program exit:\n");
    exit(0);
}

static void sig_int(int signo){
    printf("\nin sig_int:\n");
}