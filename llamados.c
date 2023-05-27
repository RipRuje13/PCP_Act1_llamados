#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int process_fork(int nproc) {
int i;
for(i=1; i<=nproc-1;i++) if(fork()==0) return(i);
return(0);
}

static char *cmd[]={"who","ls","date","ps","uname"};
int j,i,pid,status,proc;
int buf; 
FILE *fp;

main() {
j=rand()%5; /* utilizado por el proceso uno*/
pid=process_fork(6);

    switch(pid){
        case 0: printf("estoy en proceso");
        wait(&status);
        fprintf(stdout,"\n\n ********* padre con ID=%ld \n\n",getpid());
        exit(1);

        case 1: fprintf(stdout,"\n soy el proceso 1 con ID=%ld \n\n",getpid());
        execlp(cmd[j],cmd[j],0);
        exit(0);

        case 2: fprintf(stdout,"\n soy el proceso 2 con ID=%ld \n\n",getpid());
        system("sort -n suma");
        exit(0);

        case 3: fprintf(stdout,"\n soy el proceso 3 con ID=%ld \n\n",getpid());
        execlp("sort","sort","-n","suma",0);
        exit(0);

        case 4: fprintf(stdout,"\n soy el proceso 4 con ID=%ld \n\n",getpid());
            if((fp=fopen("suma","r"))==NULL){
                printf("error al abri el archivo");
                exit(0);
            }
            else {
                printf("buscando archivo \n");
                while(!feof(fp)){
                    fscanf(fp,"%d",&buf);
                    printf("%d \n",buf);
                }
                fclose(fp);
                exit(0);
            }

        case 5: fprintf(stdout,"\n soy el proceso 5 con ID=%ld \n\n",getpid());

        if((fp=fopen("suma","a"))==NULL){
            printf("error al abrir el archivo/escritura");
            exit(0);
        }
        else {
            printf("escribiendo archivo \n");
            fprintf(fp,"%d\n",2000);
            fclose(fp);
            exit(0);
        }

        default: printf("no hay tal comando \n");
        exit(0);
    }
    wait(&status);
}