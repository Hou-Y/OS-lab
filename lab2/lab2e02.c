#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv){
  int n, t, i=0;
  if (argc != 3){
  printf("err no arg\n");
  return -1;
  }
  
  n = atoi(argv[1]);
  //out = open(argv[2], O_RDWR, O_CREAT);
  t = atoi(argv[2]);
  //2^(n) figli, NON *2 figli!!!!!!!!!!!!!!!!!
  //dopo che il padre ha fatto il fork il figlio muore
  fprintf (stdout, "Starting Process: PID=%d\n",  getpid());
  for(i=0; i<n; i++){ 
  	//ogni volta che aggiungo un livello il numero attuale di processi viene elevato al quadrato
  	 if (fork()) {
    	// Parent
    		
             if(fork()) {
             	fprintf (stdout, "Child : PID=%d; FatherPID=%d;\n",
             getpid(), getppid());
             	exit(0);
             	}
            
             }
         /*else {
    	// Child
    		fprintf (stdout, "Child : PID=%d; FatherPID=%d; ReturnPID=%d\n",
             getpid(), getppid(), pid);}*/
  }
sleep(t);
fprintf(stdout, "Terminated after %d \n", i);
   	
  return 0;
}
