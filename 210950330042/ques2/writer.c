#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main()
{
int fd;
fd=open("/dev/waitstatic",O_WRONLY,0777);
char Ubuff[]="User Buffer WAIT STATIC";

if(fd < 0)
{
printf("\n Error Cannot open file\n");
exit(1);
}
write(fd,Ubuff,sizeof(Ubuff));
close(fd);
return 0;
}


