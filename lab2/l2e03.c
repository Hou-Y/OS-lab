#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
//precedence graph = control flow graph
int main(){
int i, pid;
printf("P1\n");
//for (i=1; i<=2; i++) {
  pid= fork ();
  if(pid==0){ //child
  	printf("P3\n");
  	printf("P6\n");
  	//printf ("P%d\n", pid);
  	printf("P8\n");
  	exit(0);
  	}
  else { //parent
  	printf("P2\n");
  	pid=fork();
  	if(pid==0){ //child2
  		printf("P5\n");
  		exit(0);}
  	else{ //parent
  		i=pid;
  		printf("P4\n");
  		}
  	waitpid(i, NULL, 0);
  	//NULL == ignora il valore uscente dal figlio
  	// status 0 e' il default ma lo devi per forza
  	//inserire per farlo funzionare
  	printf("P7\n");
  	
  	}
  	
//while (wait((int *) 0 )!=pid); 
//NON HO CAPITO LA DIFFERENZA TRA il while wait e il wait normale (quello aspetta qualsiasi padre??
wait((int *) 0 );
printf ("P9\n");
return 0;
}
