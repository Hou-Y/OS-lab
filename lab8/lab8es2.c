#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
//3 semafori
/*typedef struct sem_tag{
    char lock;
    int count;
    process_t *h;
} semaphore
*/

// Mutual Exclusion semaphore
typedef int * semaphore;
semaphore meI, meBCD, meG, meA;

semaphore make_sem () {
  int *sem;

  sem = calloc (2,sizeof(int));
  pipe (sem);
  return sem;
}
//necessito di un contatore
void WAIT (semaphore s) {
  int junk, i;
        if (read(s[0], &junk, 1) <=0) {
            fprintf(stderr, "ERROR : wait\n");
            exit(1);
        }
}

void SIGNAL(semaphore s) {
  if (write(s[1], "x", 1) <=0) {
    fprintf(stderr, "ERROR : signal\n");
    exit(1);
  }
}

void pipe_sem_destroy(semaphore sem){
  close(sem[0]);
  close(sem[1]);
  free(sem);
}

int main(int argc, char **argv){
    int np, npSC, i;
    //int *meI, *meBCD, *meG;
    meI = make_sem();
    meBCD = make_sem(); 
    meG = make_sem();
    meA = make_sem();
    setbuf(stdout, 0);
    //parto con zero visto che è per sincronizzare
    //numero minimo: 4 semafori
    SIGNAL(meA);
    for(np=0; np<3; np++)
    {
    /*semaforo per BCD, per G, per H e per I*/
    WAIT(meA);
    printf("A ");
    SIGNAL(meBCD); //in realtà sembra non serva
    WAIT(meBCD);
    if(!fork()){ //padre che riceve il PID dal figlio
        printf("B ");
        SIGNAL(meI);

        if(fork()){
        printf("D ");
        printf("H ");
        SIGNAL(meI);
        
        }
        else{
            printf("C ");
            if(fork()){
                printf("E ");
                SIGNAL(meG);
            }
            else{
                printf("F ");
                SIGNAL(meG);
                WAIT(meG);
                WAIT(meG);
                printf("G ");
                SIGNAL(meI);
            }
            
        }
    }
    else{
        for(i=0; i<3; i++)
            WAIT(meI); //3 volte fino a quando non raggiunge zero
        printf("I\n");
        SIGNAL(meA);
    }
    
    }
    //come distruggo il semaforo
    pipe_sem_destroy(meI);
    pipe_sem_destroy(meG);
    pipe_sem_destroy(meBCD);
//// come mai prima si fermava ad I ma ora riparte da A fino a G una 
//seconda volta anche se non dovrebbe??
//unica differenza è stato terminare con uno spazio anzichè un \n!

// il numero minimo di semafori vale 3?
    return 0;
}
