#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig){
    printf("\n");

}

int main (int argc ,char **argv){
    int i=0, j=0;
    signal(SIGUSR1, handler); 
    if(fork()){ //parent
        while(i<10){
        printf("Parent wake up\n");
        kill(0, SIGUSR1);
        sleep(1); //si ferma un attimo per evitare di stampare parent wake up appena dopo il precedente parente wake up

        //kill(pid, nome del segnale)
        //il nome del segnale è tra quelli di default come SIGUSR1, SIGALRM
        // su slide 9 di u4s4 alarm
        i++;}
    }
    else{ //child
    
    while(j<10){
         pause();  //aspetta il segnale del padre prima di partire con la stampa
         //lo sleep termina una volta ricevuto il segnale SIGALRM
          
         /*attenzione: se non usi il signal handler la reazione
        la reazione di default è terminare il processo c*/
         printf("Child wake up\n");
         j++;}
    }

    return 0;
}

