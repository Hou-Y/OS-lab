#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define N 100

int main (int argc, char **argv) {
  char str[100];
  int in;

  setbuf(stdout,0);

  if (argc != 2){
  printf("err no arg\n");
  return -1;
  }

  in= open(argv[1], O_RDONLY);
  //while(fscanf("%s %s %s", )==3){
  while(read(in, str, N)!=NULL){
  printf ("Comando: %s\n", str);
    system(str);
    str[0] = '\0';
  }
  close(in);
  return 0; 
  }
