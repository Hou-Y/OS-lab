#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define N 100

int main (int argc, char **argv) {
  char str[100];
  char com[40], argg[10][10];
  FILE* in;

  setbuf(stdout,0);

  if (argc != 2){
  printf("err no arg\n");
  return -1;
  }

  in= fopen(argv[1], "r");
  //while(fscanf("%s %s %s", )==3){
  //read(in, str, N)!=NULL;
  //printf ("Comando: %s\n", str);
    while(fgets(in, "%s %s\n", com, argg)!=EOF){
      printf("Letto %s\n", com);
    if(!fork()){
      printf("exec : %s %s\n", com, argg);
      //non sai quanti argomenti un comando ha meglio usare execv!
    execvp(com, argg);
    // execl("/bin/ls", "ls", "-l", (char *)0);
    str[0] = '\0';}
    else 
      wait((int *)0);
    sleep(3);
  }
  close(in);
  return 0; 
  }
