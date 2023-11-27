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
void sender (pid_t, int *p, int *p1);
void receiver (int *p, int *p1);
void catcher ();

int
main (int argc, char **argv) {
  int cpid, status;
  int receiverPid, senderPid;
  int p[2], p1[2];

  signal(SIGUSR1,catcher); //debugger

  receiverPid = fork(); 
  if (receiverPid == 0) { //sono nel figlio (e il padre ha il PID del figlio)
    pipe(p); //sender scrive / receiver legge
    pipe(p1); //viceversa
    receiverPid=getpid();

    senderPid = fork();

    if (senderPid == 0) {
        sender (receiverPid, p ,p1); 
      }
    else {
      receiver (p, p1); 
      
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

void sender (pid_t receiverPid, int *p, int *p1) {
  
  char line[N];
  int sentMsg=0, senderPid = getpid() , check;
  int len;
  close(p[0]);
  close(p1[1]);
  while (1) {
    //fprintf (stdout, "SENDER (receiverPid=%d): ", receiverPid);
    fflush (stdout);
    scanf ("%s", line);
    len=strlen(line);
    write(p[1], &len, 1);
    write(p[1], line, len);
    read(p1[0], &check, 1 ); //come ACK
    //finisci qua
    //fprintf (fp, "%d %s", senderPid, line);

    sentMsg++; 	
    //kill (receiverPid, SIGUSR1); 
    if (strcmp(line, "end") == 0)
      break;


  }
  close(p[1]);
  exit(sentMsg); 
}


void receiver (int *p, int *p1) {
  char line[N];
  int receivedMsg=0, senderPid, i, check;
  close(p[1]);
  close(p1[0]);
  while (1) {
    read(p[0], &check, 1);
    read(p[0], line, check);

    if (strcmp(line, "end") == 0)
      break;
              
    for (i=0; i<strlen(line); i++)
      line[i] = toupper(line[i]);
    fprintf (stdout, "RECEIVER : %s\n", line);
    fflush (stdout);
    //sleep(1); fai qualcosa
    receivedMsg++;     
    //kill (senderPid, SIGUSR1);
    write(p1[1], &check, 1);
  }  

  exit (receivedMsg); 
}

