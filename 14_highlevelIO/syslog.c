#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>

int main(void)
{
    openlog("wayne",LOG_CONS|LOG_PID,0);
    syslog(LOG_DEBUG, "this is a syslog test message \n");
    closelog();
    return 0;
}