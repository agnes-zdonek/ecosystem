#ifndef _ECOSYS_H_
#define _ECOSYS_H_
#include <stdio.h>

#define SIZE_X 20
#define SIZE_Y 50

float p_ch_dir=0.01;
float p_reproduce_proie=0.3;
float p_reproduce_predateur=0.1;
int temps_repousse_herbe=-25;

typedef struct _animal {
  int x;
  int y;
  int dir[2]; 
  float energie;
  struct _animal *suivant;
} Animal;



Animal *creer_animal(int x, int y, float energie);
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal);
unsigned int compte_animal_rec(Animal *la);
unsigned int compte_animal_it(Animal *la);

void ajouter_animal(int x, int y, float energie, Animal **liste_animal);
void enlever_animal(Animal **liste, Animal *animal);
Animal* liberer_liste_animaux(Animal *liste);
void afficher_ecosys(Animal *liste_predateur, Animal *liste_proie);


void bouger_animaux(Animal *la);
Animal *animal_en_XY(Animal *l, int x, int y);
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie);
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) ;
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]);

void reproduce(Animal **liste_animal, float p_reproduce);
void clear_screen();

void ecrire_animal(FILE *file, Animal *liste_anim, char *type);
void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur, Animal *liste_proie);
void lire_ecosys(const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie);


#endif
