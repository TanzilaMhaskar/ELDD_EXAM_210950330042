#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main()
{
int fd;
fd=open("/dev/IOCTL",O_RDONLY,0777);
char kbuff[100];
if(fd < 0)
{
printf("\n Error Cannot open file\n");
exit(1);
}
read(fd,kbuff,1000);
printf("\n Kernel Data is = %s \n",kbuff);
close(fd);
return 0;
}


