#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
//char buf[MAXPATHLEN];
//char *path;
int main(){
	DIR *dir;
	struct dirent *drp;
	printf("cwd = %s \n",getcwd(NULL,MAXPATHLEN));
	printf("Making dir...\n");
	if((dir = opendir(getcwd(NULL,MAXPATHLEN))) != NULL){
		while((drp = readdir(dir)) != NULL){
			printf("%s\n",drp->d_name);
		}
	}
	else{
		printf("Error to open !\n");
	}
	mkdir("newone",S_IRWXU);
	printf("Successfully made. \n");
	printf("Going to change dir...\n");
	chdir("newone");
	printf("Directory changed successfully\n");
	printf("cwd = %s \n",getcwd(NULL,MAXPATHLEN));
	printf("removing dir ...\n");
	chdir("..");
	rmdir("newone");
	printf("Successfully removed.\n");


}