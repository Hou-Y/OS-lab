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

int fd[2];

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
  int n, nR, nW;
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
  pipe(fd);

  n = 0;
  if (fork()) {
    fprintf (stdout, "\n");
    for (;;) {
       nW = write (fd[1], &c, 1);
       n = n + nW;
       fprintf (stdout, "W %d\r", n);
    }
  } else {
    pause ();
    for (;;) {
      nR = read (fd[0], &c, 1);
      n = n + nR;
      fprintf (stdout, "R %d\r", n);
    }
  }

   return (0);
}
