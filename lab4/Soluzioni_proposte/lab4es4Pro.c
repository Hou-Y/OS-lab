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

  receiverPid = fork(); //ottendo il PID del "padre"
  if (receiverPid == 0) {
    receiver (); //se sono sul figlio della prima fork F1
  } else {
    senderPid = fork();
    if (senderPid == 0) {
      sender (receiverPid); //uso il PID del padre OG
    }
  }

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

  senderPid = getpid();

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
    kill (receiverPid, SIGUSR1);
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

