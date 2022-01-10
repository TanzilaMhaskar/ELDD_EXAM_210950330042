#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <asm/ioctl.h>
#include <sys/ioctl.h>
#define stats_IOWR('a' ,1,int32_t*)

struct stats{
	int size;
	char buff[];
	int r_w;
};

int main()
{
int fd;
char Ubuff[]="User Buffer = Write from user to kernel";
char kbuff[100];
fd=open("/dev/IOCTL",O_RDWR,0777);
struct stats ToSend={100,Ubuff,1};


if(fd < 0)
{
printf("\n Error Cannot open file\n");
exit(1);
}

ioctl (fd,stats,&ToSend);
write(fd,Ubuff,sizeof(Ubuff));
read(fd,kbuff,1000);
printf("\n Kernel Buffer = %s \n",kbuff);
close(fd);
return 0;
}


