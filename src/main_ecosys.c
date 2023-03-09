#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "../include/ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000
#define MAX_ENERGY 10
#define MAX_ENERGY2 60



void generate_rand_x_y_energy(int *x, int *y, float *energy, int type) {
  *x = rand() % SIZE_X;
  *y = rand() % SIZE_Y;
  if(type == 0) {*energy = rand() % MAX_ENERGY;}
  else {*energy = rand() % MAX_ENERGY2;}
}

 
int main(int argc, char* argv[]) {

  if(argc!=3){
        printf("\nyou need to supply two arguments: number of maximum iterations & starting number for prey & predators");
        exit(1);
  }
  clear_screen();
  printf("\nyou have chosen %s iterations, %s of predators and %s of prey, wait 5 seconds\n", argv[1], argv[2], argv[2]);
  sleep(5);

  //srand(time(NULL));

  int map[SIZE_X][SIZE_Y];
  for (int i = 0; i < SIZE_X; i++){
    for (int j = 0; j < SIZE_Y; j++){
      map[i][j] = 0;
    }
  }
 

  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;

  
  for(int i = 0; i < atoi(argv[2]); i++){
    int x,y;
    float energie;
    generate_rand_x_y_energy(&x,&y,&energie,0);
    ajouter_animal(x, y, energie, &liste_proie);
    generate_rand_x_y_energy(&x,&y,&energie,1);
    ajouter_animal(x, y, energie, &liste_predateur);
  }

  afficher_ecosys(liste_predateur, liste_proie); 

  int j = 0; 
  FILE *f;
  f = fopen("./input_output/Evol_Pop.txt", "w"); 

  if(f == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

  fprintf(f, "%d %d %d \n", j, compte_animal_it(liste_proie), compte_animal_it(liste_predateur));

  while(j!=atoi(argv[1]) && liste_proie!=NULL){
    rafraichir_proies(&liste_proie, map);
    rafraichir_predateurs(&liste_predateur, &liste_proie);
    afficher_ecosys(liste_predateur, liste_proie); 
    fprintf(f, "%d %d %d \n", j, compte_animal_it(liste_proie), compte_animal_it(liste_predateur));

    //sleep(3);
    j++;
  }

  fclose(f);

  liste_proie = liberer_liste_animaux(liste_proie);
  liste_predateur = liberer_liste_animaux(liste_predateur);

  
  return 0;
}

