#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "ecosys.h"


/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie){
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  assert( 0 <= x && x < SIZE_X ); 
  assert( 0 <= y && y < SIZE_Y ); 
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  Animal *animal = NULL;

  assert( 0 <= x && x < SIZE_X ); 
  assert( 0 <= y && y < SIZE_Y ); 

  animal = creer_animal(x, y, energie);
  *liste_animal = ajouter_en_tete_animal(*liste_animal, animal);

  return;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {

  Animal *tmp;
  if (*liste == NULL || animal == NULL) return;
  while ((tmp = *liste) != NULL && *liste != animal) { liste = &tmp->suivant;}
  *liste = tmp->suivant;
  free(tmp);
  
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
  
  Animal *tmp = NULL;
  while (liste) {
    tmp = liste->suivant;
    free(liste);
    liste = tmp;
  }
  return NULL;

}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    cpt++;
    la=la->suivant;
  }
  return cpt;
}


/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_predateur, Animal *liste_proie){
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) { 
    for (j = 0; j < SIZE_Y; ++j) { 
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) { //if a for changed j for i
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) { //sizey -> sizex
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) { //sizex -> sizey
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) { //sizex -> sizey
    printf("-");
  }
  printf("+\n");

  printf("\n Nb proies: %5d Nb predateurs: %5d \n\n", compte_animal_rec(liste_proie), compte_animal_rec(liste_predateur));

  
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    assert(la);

    while (la) {
      if (rand() / (float)RAND_MAX < p_ch_dir) {  
          la->dir[0] = rand() % 3 - 1;
          la->dir[1] = rand() % 3 - 1;
      }
      
      if (la->x == 0 && la->dir[0] == 1){la->x = SIZE_X - 1;}
      else if (la->x == SIZE_X -1 && la->dir[0] == -1){la->x = 0;}
      else {la->x = la->x - la->dir[0];}

      if (la->y == 0 && la->dir[1] == 1){la->y = SIZE_Y - 1;}
      else if (la->y == SIZE_Y - 1 && la->dir[1] == -1){la->y = 0;}
      else { la->y = la->y - la->dir[1];}

      la = la->suivant;

  }

}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  
  Animal *liste = *liste_animal;
  while(liste != NULL){
    if (rand() / (float)RAND_MAX < p_reproduce){
      *liste_animal = ajouter_en_tete_animal(*liste_animal, creer_animal(liste->x, liste->y, liste->energie / 2.0));
      liste->energie = liste->energie / 2.0;
    }
    liste = liste->suivant;
  }

}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    
    assert(*liste_proie);

    rafraichir_monde(monde);
    bouger_animaux(*liste_proie);

    Animal *tmp = *liste_proie;
    Animal *placeholder = NULL;

    while(tmp)
    {
      (tmp->energie)--;

      if (tmp->energie <= 0){
        placeholder = tmp->suivant;
        enlever_animal(liste_proie, tmp);
        tmp = placeholder;
      } else {
      if(monde[tmp->x][tmp->y] > 0){
        tmp->energie+=monde[tmp->x][tmp->y];
        monde[tmp->x][tmp->y] = temps_repousse_herbe;
      }
      tmp = tmp->suivant;
      }

    }

    reproduce(liste_proie, p_reproduce_proie);
    
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
  
  while(l){
  if(l->x == x && l->y == y){return l;}
  l=l->suivant;
  }

  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   
  assert(*liste_predateur);
   
  bouger_animaux(*liste_predateur);
  Animal *tmp = *liste_predateur;
    
  while(tmp){
    (tmp->energie)--;

    if (tmp->energie <= 0){
      Animal *placeholder = tmp;
      tmp=tmp->suivant; 
      enlever_animal(liste_predateur, placeholder);
    }
  
    else {
    if (animal_en_XY(*liste_proie,tmp->x, tmp->y)!=NULL){
      tmp->energie=tmp->energie+animal_en_XY(*liste_proie,tmp->x, tmp->y)->energie;
      enlever_animal(liste_proie, animal_en_XY(*liste_proie,tmp->x, tmp->y));
    }

      tmp = tmp->suivant;
      
    }}

    reproduce(liste_predateur, p_reproduce_predateur);

}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){

   for(int i = 0; i < SIZE_X; i++){
    for(int j = 0; j < SIZE_Y; j++){ monde[i][j]++;}
   }

}


void ecrire_animal(FILE *file, Animal *liste_animal, char *type) {
  fprintf(file, "<%s>\n", type);
  while (liste_animal) {
    fprintf(file, "x=%d y=%d dir=[%d %d] e=%.6f\n",
    liste_animal->x, liste_animal->y, liste_animal->dir[0], liste_animal->dir[1], liste_animal->energie);
    liste_animal = liste_animal->suivant;
  }
  fprintf(file, "</%s>\n", type);
}

void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur, Animal *liste_proie) {
  FILE *f = fopen(nom_fichier, "w");
  if (!f) {
    fprintf(stderr, "Erreur lors de l'ouverture en écriture du fichier %s !\n", nom_fichier);
    exit(EXIT_FAILURE);
  }
  ecrire_animal(f, liste_proie, "proies");
  ecrire_animal(f, liste_predateur, "predateurs");
  fclose(f);
}

void lire_ecosys(const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie) {

    FILE *f=fopen(nom_fichier, "r");

    if (f==NULL) {
        printf("Erreur lors de l’ouverture de %s\n",nom_fichier);
        exit(EXIT_FAILURE);
    }

    char buffer[1000];
    int x_lu, y_lu, dir_lu[2];
    float e_lu;

    fgets(buffer, 1000, f); 
    assert(strncmp(buffer, "<proies>",8)==0);
    fgets(buffer, 1000, f); 
    
    while (strncmp(buffer,"</proies>",9)!=0) {
        sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f\n", &x_lu, &y_lu, &dir_lu[0], &dir_lu[1], &e_lu);
        Animal *a_lu=creer_animal(x_lu, y_lu, e_lu);
        a_lu->dir[0]=dir_lu[0];
        a_lu->dir[1]=dir_lu[1];
        
        a_lu->suivant=*liste_proie;
        *liste_proie = a_lu;
        fgets(buffer, 1000, f);
    }

    fgets(buffer, 1000, f); 
    assert(strncmp(buffer, "<predateurs>",12)==0);

    fgets(buffer, 1000, f); 

    while (strncmp(buffer,"</predateurs>",13)!=0) {
        sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f\n", &x_lu, &y_lu, &dir_lu[0], &dir_lu[1], &e_lu);
        Animal *a_lu=creer_animal(x_lu, y_lu, e_lu);
        a_lu->dir[0]=dir_lu[0];
        a_lu->dir[1]=dir_lu[1];
       
        a_lu->suivant=*liste_predateur;
        *liste_predateur = a_lu;
        fgets(buffer, 1000, f); 
    }

    fclose(f);
}

