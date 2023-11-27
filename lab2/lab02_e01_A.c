#include <stdio.h>
#include <stdlib.h>

int main(){
int i;
for (i=1; i<=2; i++) {
  if (!fork ())
    printf ("%d\n", i);
}
printf ("%d\n", i);
return 0;
}
