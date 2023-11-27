/*Implement a C program that generates two children, a producer and a consumer. 
  The producer child reads from the keyboard some strings, and it transfers them to the consumer. 
  The consumer child converts the strings into uppercase characters, and it visualizes the strings in standard output.

The introduction of the string “end” terminates both children's processes and then, in sequence, it terminates the parent process. 
The transfer of the strings has to take place through a file.

Suggestions:

Derive the solution from that of the previous exercise
Communicating processes are not a parent and a child, but two “siblings”; as a consequence, you have to make sure that each child knows the PID of the “brother”*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

//DOMANDA= il sender (figlio 2) manda il signal al padre OG però! la parte dove sta il pause che aspetta il segnale è il figlio 1, com'è che lo riceve????

#define N 132
#define NAME "tmp.txt"
//sender = producer
// receiver = consumer
void sender (pid_t);
void receiver ();
void catcher ();

int
main (int argc, char **argv) {
  int cpid, status;
  int receiverPid, senderPid;

  signal(SIGUSR1,catcher); //debugger

  receiverPid = fork(); //il pdare ottiene il PID del figlio 
  if (receiverPid == 0) {
    receiver (); //se sono sul figlio della prima fork F1, dà al figlio 0
  } 
  else {
    senderPid = fork();
      if (senderPid == 0) {
        sender (receiverPid); //uso il PID del primo figlio
      }
  }
  /*CI SONOOOOOO:
  il PADRE OG es: PID=1
  fa un figlio e riceve PID=0
  e poi il PADRE forka di nuovo, ora, ci sta un padre con PID=1 e due "figli"
  anche se i figli tornano PID=0 al  PADRE hanno ognuno il SUO PID che posso ottenere usando getpid() dentro al loro processo (es F1=11 e F2=21)
  ma IO decido che il PADRE farà il figlio (1)  e uno dei due figli sarà nominato PADRE 
  */

  fprintf (stdout, "Sender   PID %d\n", senderPid);
  fprintf (stdout, "Receiver PID %d\n", receiverPid);

  cpid = wait(&status);
  if (WIFEXITED(status)) {
    printf("Terminated PID %d  Status %d\n", cpid, WEXITSTATUS (status));
  }

  cpid = wait(&status);
  if (WIFEXITED(status)) {
    printf("Terminated PID %d  Status %d\n", cpid, WEXITSTATUS (status));
  }


  
  return (0);
}

void
catcher() {
  //fprintf (stdout, "CATCHER\n");
  //fflush (stdout);
  return;
}

void sender (pid_t receiverPid) {
  FILE *fp;
  char line[N];
  int sentMsg=0, senderPid;

  senderPid = getpid(); //ottengo il pid SUO

  while (1) {
    fprintf (stdout, "SENDER (receiverPid=%d): ", receiverPid);
    fflush (stdout);
    scanf ("%s", line);

    fp = fopen (NAME, "w");
    if (fp == NULL) {
      fprintf(stderr, "Errore open file: %s\n", NAME);
      exit(1);
    }
    fprintf (fp, "%d %s", senderPid, line);
    fclose(fp);

    sentMsg++; 	
    kill (receiverPid, SIGUSR1); //però questo manda il segnale alla branca dove lavora SOLO il sender (if/else) con receiverPID!=0
    //altrimenti lavora SOLO il receiver (se receiverPID==0) 
    //però questo lo manda al padre OG - in altre parole non al processo con il wait che ha il pause visto che quello si triggera solo se receiverPID=0 
    if (strcmp(line, "end") == 0)
      break;

    pause ();
  }

  exit(sentMsg); 
}

void receiver () {
  FILE *fp;
  char line[N];
  int receivedMsg=0, senderPid, i;
  
  while (1) {
    pause(); //aspetta il signal dal sender 

    fp = fopen (NAME, "r");
    if (fp == NULL) {
      fprintf(stderr, "Errore open file: %s\n", NAME);
      exit(1);
    }
    fscanf (fp, "%d %s", &senderPid, line);
    fclose(fp);
    
    if (strcmp(line, "end") == 0)
      break;
              
    for (i=0; i<strlen(line); i++)
      line[i] = toupper(line[i]);
    fprintf (stdout, "RECEIVER (senderPid=%d): %s\n", senderPid, line);
    fflush (stdout);
    sleep(1);
    receivedMsg++;     
    kill (senderPid, SIGUSR1);
  }  

  exit (receivedMsg); 
}

