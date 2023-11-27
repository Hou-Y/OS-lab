#include <stdio.h>
#include <stdlib.h>

int main(){
int i;

for (i=0; i<2; i++) {
  if (fork ())
    fork ();
}
printf ("%d\n", i);
return 0;
}
