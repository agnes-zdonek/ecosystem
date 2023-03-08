#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <string.h>

#include "../include/ecosys.h"

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define MAX_ENERGY 50

void generate_rand_x_y_energy(int *x, int *y, float *energy) {
  *x = rand() % SIZE_X;
  *y = rand() % SIZE_Y;
  *energy = rand() % MAX_ENERGY;
}

int main(void) {

  //srand(time(NULL));
  
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;

  
  for(int i = 0; i < 20; i++){
    int x,y;
    float energie;
    generate_rand_x_y_energy(&x,&y,&energie);
    ajouter_animal(x, y, energie, &liste_proie);
    generate_rand_x_y_energy(&x,&y,&energie);
    ajouter_animal(x, y, energie, &liste_predateur);
  }

  afficher_ecosys(liste_proie,liste_predateur);

  printf("\n\n~~~~ ~~~~ ~~~~ ~~~~ ~~~~ ~~~~ \n\n");

  //la suppression de quelques proies et quelques pr edateurs

  enlever_animal(&liste_proie, liste_proie->suivant);
  enlever_animal(&liste_proie, liste_proie->suivant->suivant);

  enlever_animal(&liste_predateur, liste_predateur);
  enlever_animal(&liste_predateur, liste_predateur->suivant->suivant->suivant);
  

  afficher_ecosys(liste_proie,liste_predateur);

  /***TME3*/

  ecrire_ecosys("./input_output/test_ecosys.txt", liste_predateur, liste_proie);

  Animal *liste_proie2= NULL;
  Animal *liste_predateur2 = NULL;
  lire_ecosys("./input_output/test_ecosys.txt", &liste_predateur2, &liste_proie2);

  afficher_ecosys(liste_proie2,liste_predateur2);

  liste_proie = liberer_liste_animaux(liste_proie);
  liste_predateur = liberer_liste_animaux(liste_predateur);

  liste_proie2 = liberer_liste_animaux(liste_proie2);
  liste_predateur2 = liberer_liste_animaux(liste_predateur2);

  return 0;
}