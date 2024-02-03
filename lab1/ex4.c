#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF 4096

int main (int *argc, char **argv){
  int in, out, NR, NW;
  char s[BUF];
  in = open(argv[1], O_RDONLY);
  //out = open(argv[2], O_RDWR, O_CREAT);
  out = creat(argv[2], 0666);
  if ((in==-1)){
  fprintf(stderr, "Errore apertura file lettura\n");
  }
   if ((out==-1)){
  fprintf(stderr, "Errore creazione file\n");
  }
  while((NR = read(in, s, BUF))>0){
  // while(fscanf(in,"%s",s)!=0){
    //fscanf(in, "%s", s);
    //fprintf(out, "%s ", s);
    NW= write(out,s, NR );
  }
  close(in);
  close(out);
  exit(0);
}
