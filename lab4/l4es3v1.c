#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig){
    //printf(" H ");

}

int main (int argc ,char **argv){
    int i=0, j=0;
    //signal(SIGUSR1, handler); 
    signal(SIGALRM, handler); 
    if(fork()){ //parent
        while(i<10){
        printf("Parent wake up\n");
         kill(0, SIGALRM);
        //kill(0, SIGUSR1);
        sleep(1); //si ferma un attimo per evitare di stampare parent wake up appena dopo il precedente parente wake up
        
        //kill(pid, nome del segnale)
        //il nome del segnale è tra quelli di default come SIGUSR1, SIGALRM
        // su slide 9 di u4s4 alarm

        /*in questo es, se mando il SIGALRM e uso il hadler per quello
        finisce che anche lo sleep manda a sè stesso un SIGALRM, facendo in modo che 
        sia padre che figlio chiamino il hadler*/

        /* eppure usando un segnale che non infastidisca nessuno SIGUSR1 finisce che
        alla prima ite*/
        i++;}
    }
    else{ //child
    
    while(j<10){
         pause();  //aspetta il segnale del padre prima di partire con la stampa
         //lo sleep termina una volta ricevuto il segnale SIGALRM
          //il child quando va in sleep manda il SIGCHLD?
         /*attenzione: se non usi il signal handler la reazione
        la reazione di default è terminare il processo c*/
         printf("Child wake up\n\n");
        
         j++;}
    }

    return 0;
}

