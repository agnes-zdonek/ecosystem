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

 
int main(void) {

  //srand(time(NULL));

  int map[SIZE_X][SIZE_Y];
  for (int i = 0; i < SIZE_X; i++){
    for (int j = 0; j < SIZE_Y; j++){
      map[i][j] = 0;
    }
  }
 
  /*Part 2: exercice 4, question 2 */
  Animal *ani_troc = creer_animal(0, 0, 21.37);
  ani_troc->dir[0] = 1;
  ani_troc->dir[1] = 1;
  bouger_animaux(ani_troc);
  printf("animal ani: x %d, y %d\n", ani_troc->x, ani_troc->y);
  liberer_liste_animaux(ani_troc);

  /*exercice 4, question 4 */

  Animal *liste_reproduction = NULL;

  for(int i = 0; i < 2; i++){
    int x,y;
    float energie;
    generate_rand_x_y_energy(&x,&y,&energie,0);
    ajouter_animal(x, y, energie, &liste_reproduction);
  }

  printf("\n\n~~~~ ~~~~ ~~~~ ~~~~ ~~~~ ~~~~ \n\n");

  printf("%d ",compte_animal_rec(liste_reproduction));
  reproduce(&liste_reproduction, 1.0);
  printf("%d ",compte_animal_rec(liste_reproduction));
  reproduce(&liste_reproduction, 1.0);
  printf("%d ",compte_animal_rec(liste_reproduction));
  reproduce(&liste_reproduction, 1.0);
  printf("%d ",compte_animal_rec(liste_reproduction));
 

  liste_reproduction = liberer_liste_animaux(liste_reproduction);
  
  printf("\n\n~~~~ ~~~~ ~~~~ ~~~~ ~~~~ ~~~~ \n\n");

  /*exercice 6, question 3  */

  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;

  
  for(int i = 0; i < 200; i++){
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

  while(j!=200 && liste_proie!=NULL){
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

