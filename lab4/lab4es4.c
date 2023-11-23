#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <sys/wait.h> 
#include <string.h>

#define Q 100

void handler(int sig){
    printf("mex ricevuto\n");
    return; 

}

int main (int argc ,char **argv){
    //file condiviso entrambi lo aprono e scrivono
    //cerca il nunmero diverso dal pid stesso (del figlio)
    int propid, cpid, i;
    char word[Q];
    FILE *F;

    //signal(SIGUSR1, handler); 
    signal(SIGUSR1, handler); 
    if(fork()){ //consumer child
        //parent ma reverso in maniera speculare l'albero e
    //decido che quello a dx, con pid!=0 è il figlio così posso mandarlo al secondo figlio
           //fprintf(F, "%d \n", getpidf()); //scrivo sul file il pid MIO
            cpid=getpid();
             //da dopo il kill del producer
             while(strcmp(word, "end")!=0) {
                pause(); //aspetto il producer
                F=fopen("f.txt", "r");
                fscanf(F, "%d %s", &propid, word);
                  //come ottenere tot lettere
                for(i=0; i<strlen(word); i++)
                    word[i] = toupper(word[i]);
                fprintf (stdout, "CONSUMER (producer=%d): %s\n", propid, word);
                
                //##come mai il FFLUSH, cosa potrebbe rimanere nel buffer???
                kill(propid, SIGUSR1);
             }      
        
        if(!fork()){ //producer child
            sleep(1); //per assicurarmi che l'altro abbia forkato e stia aspettando il producer
            //fprintf(F, "%d \n", getpidf()); //scrivo sul file il pid MIO del producer
            printf("A\n");
            //sscanf(F, "%s %s", pid, pid2);
            while(strcmp(word, "end")!=0){
                 F=fopen("f.txt", "w");
                scanf(" %s", word);
                fprintf(F, " %d %s", getpid(), word);
                fclose(F);
                kill(   cpid  , SIGUSR1 ); //mando segnale al consumer

                pause(); //riceve kill dal consumer e riparte con la lettura
            }
 

        }
        else{ //considero questo come parent
    
    }
    }
    
    fclose(F);
    return 0;
}

