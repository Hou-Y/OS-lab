/*
 *  Verify the size of a pipe
 *  0 - Run in background
 *  1 - Father writes in a pipe -> it stops
 *  2 - Kill it from shell with Kill -USR1 pid
 *  3 - Start child with Kill -USR2 pid
 *  4 - Child reads from the pipe -> it stops
 *  5 - Kill it from shell with Kill -USR1 pid
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int fd[2], fd1[2];

static void signalHandler (
  int signo
  )
{
  if (signo == SIGUSR1) {
    printf ("\nReceived SIGUSR1 -> stop\n");
    exit (0);
  } else {
    if (signo == SIGUSR2) {
      printf ("\nReceived SIGUSR1 -> stop\n");
    }
  }
  return;
}

int
main (
  int argc,
  char ** argv
  )
{
  int i, nR, nW;
  char c = '1';

  // no buffering
  setbuf (stdout, 0);

  // Install Signal Handler
  if (signal (SIGUSR1, signalHandler) == SIG_ERR) {
    fprintf (stderr, "Signal Handler Error.\n");
    return (1);
  }
  if (signal (SIGUSR2, signalHandler) == SIG_ERR) {
    fprintf (stderr, "Signal Handler Error.\n");
    return (1);
  }

  // Create pipe
  pipe(fd); //padre scrive, figlio legge
  pipe(fd1); //figlio scrive padre legge
  //the child inherit the pipe (file descriptors from parent)
 
  if (fork()) {
    fprintf (stdout, "\n"); //sono il padre -> io stampo, una volta fatto scrivo qualcosa sul pipe per sbloccar il figlio che legge
    close(fd[0]); //analogamente per il figlio
    close (fd1[1]);
    for (i=0;i<10;i++) {
       fprintf (stdout, "I'm the father %d\n", getpid());
       write(fd[1], "P", 1);
      
       nW = read(fd1[0], &c, 1);
    }
    // \r su linux usato per tornare all'inizio della riga (non va a capo)
    // ci sono due casi in cui si sblocca (per il read)
    // 1) il pipe è chiuso (non ho più niente da scrivere)
    // 2) ho scritto qualcosa (finchè il doc è vuoto il read ASPETTA, ecco xkè il read è detto bloccante)
 close(fd[1]);
  } else {
    close(fd[1]); 
    close(fd1[0]);
    for (i=0;i<10;i++) {
      nR = read (fd[0], &c, 1);
      fprintf (stdout, "I'm the CHILD %d\n", getpid());
      write(fd1[1], " C" ,1);
      
    }
  }
  close(fd1[1]);
   return (0);
}
