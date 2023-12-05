#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>

#define OPZIONI 10
#define LEN     10
#define MAX     80

int
main (
  int argc,
  char* argv[]
  )
{
  char tmp[MAX], command[MAX], **mat, *tmpP;
  FILE *fp;
  int i, nString;
 fp = fopen(argv[1], "r");
  if (fp==NULL) {
    fprintf (stderr, "Error opening file.");
    exit (1);
  }

  command[0] = '\0';
  while (fscanf(fp, "%s", tmp) != EOF) {
    if (strcmp(tmp,"end") != 0) {
      strcat (command, tmp);
      strcat (command, " ");
    } else {
      printf ("Comando: %s\n", command);
      system (command);
      command[0] = '\0';
    }
  }
  fclose(fp);
return 0;}
