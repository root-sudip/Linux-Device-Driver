#include <stdio.h>
#include <sys/stat.h>

//S_IFIFO
//S_IFCHR
//S_IFDIR
//S_IFBLK
//S_IFREG
//Permission
//S_IRUSR
//S_IWUSR
//S_IXUSR
//S_IRWXU
//S_IRWXG
//S_IRWXO

//fifi communicate with two process and char communicate with device

int main(){
	int return_val;

	return_val = mknod ("char", S_IRUSR| S_IWUSR|S_IFIFO, 0);	
	if(return_val < 0){
		printf("Error to create file \n");
	}
	else{
		printf("Successfully created \n");
	}


	return 0;
}