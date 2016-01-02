#include <sys/types.h>          /* opendir, stat, closedir */
#include <dirent.h>             /* opendir, readdir, closedir */
#include <errno.h>              /* perror */
#include <stdlib.h>             /* exit */
#include <sys/stat.h>           /* stat */
#include <unistd.h>             /* stat */
#include <time.h>               /* ctime */
#include <pwd.h>                /* getpwuid */
#include <grp.h>                /* getgrgid */
#include <stdio.h>              /* printf */

int main(void)
{
    DIR *dp;
    struct dirent *dirp;
    struct stat st;
    struct passwd *pw;
    struct group *grp;
    char *ftime;

    if ((dp = opendir(".")) == NULL) {
        printf("Cannot open this directory\n");
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((dirp = readdir(dp)) != NULL) {
        if (dirp->d_reclen != 0) {
            stat(dirp->d_name, &st);
            ftime = ctime(&st.st_mtime);
            //ftime[16] = '\0';
            //ftime += 4;
            pw = getpwuid(st.st_uid);
            grp = getgrgid(st.st_gid);
            printf("%3zu %-8s %-7s %9zu %s %s\n",
                   st.st_nlink, pw->pw_name, grp->gr_name,
                   st.st_size, ftime, dirp->d_name);
        }
    }

    closedir(dp);
    return 0;
}
