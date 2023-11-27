#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc ,char **argv){
    int n;
    while(fscanf(stdin, "%d", &n)!= 0){
        if(n%2==0)
            fprintf(stderr, " as standard output %d\n", n);
        else 
            fprintf(stdout, "as standard error %d\n", n);
    }
    return 0;
}