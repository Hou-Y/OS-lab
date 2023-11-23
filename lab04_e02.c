#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
  int i = 0;
char str[100];
  setbuf(stdout,0);
  while (i<=2 && fork()){
    if (!fork()) {
      fprintf (stdout, "Running Exec ...");
      execlp ("echo", "echo", "i*i ", (char *) 0);
    }
    wait(2);
    i++;
    fprintf (stdout, "Running System ...");
    sprintf(str, "echo i+i = %d", i );
    system (str);
  }

  return (0);
} 
