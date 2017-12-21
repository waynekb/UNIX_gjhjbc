#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <signal.h>
#include <stdlib.h>

void daemonize(const char *cmd)
{
    int i,fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction a;

}