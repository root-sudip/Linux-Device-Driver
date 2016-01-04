#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
	int fd = open("a.txt",O_RDONLY | O_CREAT);
	printf("fd =>%d\n",fd);
	int fd_dup = dup(fd);
	printf("dup =>%d \n", fd_dup);

	//another function better 

	int new_dup = dup2(fd,6);
	printf("new_dup =>%d\n",new_dup);

	return 0;
}