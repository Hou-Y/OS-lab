#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX 50

struct s_name{
  char *namein;
  char *nameout;
};

typedef struct s_name names;

void pgrm(int , char* , char*);
void *leggi(void *names);
int *ordina(int *dis, int N);
void scrivi(int *ord, FILE *fb, int N);



int main (
  int argc,
  char *argv[]
  )
  // argv[1]=n
  //argv[2]= strA
{
  int n, i;

  if (argc != 4){
  printf("err no arg\n");
  exit(-1);
  }

  n = atoi (argv[1]);
  printf("Ordered vector No \n");
   printf("arg %s \n", argv[2]);
  printf("arg %s \n", argv[3]);
  pgrm(n, argv[2], argv[3]);
  //prima tutti gli input e poi tutti gli outpu
  //input come vettore di stringhe (nomi)

  //non dovrei avere problemi di race condition visto che operano 
  //tutti su input diversi
  return 0;
}

void pgrm( //acts like a manager, 
  int n,
  char *strA,
  char *strB
  )
{
  int i;
  pthread_t *ID;
  names **name;
  char *ID_A=NULL, *ID_B=NULL;
  void *retval;
  ID = malloc(n*sizeof(pthread_t));
  name = malloc(n*sizeof(names*));
  for(i=0; i<n;i++)
    name[i]=malloc(n*sizeof(names));
  name[0]->namein=strtok_r(strA ,",", &ID_A);
  printf("nome OG %s \n", name[0]->namein);
  name[0]->nameout=strtok_r(strB, ",", &ID_B);
  //strB finisce per rimpiazzare strA nel buffer!!! usando strtok 
  //per entrambe
  printf("nome OUT %s \n", name[0]->nameout);
  pthread_create(&(ID[0]),NULL, leggi, (void*)(name[0]));
  for(i=1; i<n; i++){
    pthread_create(&(ID[i]),NULL, leggi, (void*)(name[i]));
    name[i]->namein=strtok_r(NULL ,",", &ID_A);
    printf("nome OG %s \n", name[i]->namein);
    name[i]->nameout=strtok_r(NULL, ",", &ID_B);
    printf("nome OUT %s \n", name[i]->nameout);
    
    //aspetta fino al write prima di attivare il prossimo thread
    //oppure lo faccio concurrent, però così chi aspetta?
    //dovrebbe aspettarli TUTTI, ciclo aggiuntivo dove aspetta ogni singolo thread?
  }
  for(i=0; i<n;i++){
    pthread_join((ID[i]), &retval); 
  }
  free(ID);
  free(name);
  return ;
}

void* leggi(void *name){
  printf("yeeeeet");
  int *vet;
  FILE *f, *fb;
  int j, i, N;
  //char *in;
  //non posso usarlo direttamente, first parse input
  //forse metterlo in una funzione e chiamarlo nel for?
  names* name_struc=(names*)name;
  //dentro funzione read_f
  //in=name->namein;
    f = fopen(name_struc->namein, "r");
    //in= open(argv[2], O_RDONLY);
    fscanf(f, "%d", &(N)); //primo valore numero di interi nel file
    vet = (int *)malloc(N* sizeof(int));
    if (vet == NULL) {
      printf("Allocatin Error.\n");
      exit(1);
    }

    for(i=0; i<N; i++){
      fscanf(f, "%d", &(vet[i]));
      printf("%d", vet[i]);
      //read(in, v[i], N);
    }
    fclose(f);

    vet=ordina(vet, N);
    fb=fopen(name_struc->nameout, "w");
    scrivi(vet,fb, N);
    free(vet);
  
  return NULL;
}

int *ordina(int *dis, int N){
  //usando insertion sort
  int i, t, j;
  for(i=1; i<=N; i++){ // il primissimo elemento (in posizione zero è già ordinato)
    t = dis[i];
    for(j=i-1; j>=0 && t<dis[j]; j--){
        dis[j+1]= dis[j];
    }

    dis[j+1]=t;
  }
  return dis;
}

void scrivi(int *ord, FILE *fb, int N){
  int i;
  for(i=0; i<N; i++){
    fprintf(fb, "%d\n", ord[i]);
    //debug
  }
  return ;
}
