#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define BUF_SIZE 10
int main(int argc, char const *argv[])
{
	char str[BUF_SIZE];
	char buf[BUF_SIZE];
	int fd_1 = open("a.txt",O_WRONLY);
	printf("FD => %d\n",fd_1);
	int dup_1 = dup2(fd_1,8);
	printf("new FD => %d\n",dup_1 );
	
	do{	

		printf("Enter String");
		scanf("%s",str);
		lseek(dup_1,0,SEEK_END);

		write(dup_1,str,BUF_SIZE);
		close(dup_1);

	}while(str[0] != 'n');
	
	return 0;
}