#ifndef _ECOSYS_H_
#define _ECOSYS_H_
#include <stdio.h>

#define SIZE_X 20
#define SIZE_Y 50

/**
 * @param p_ch_dir probability that an animal changes direction of moving
 * @param p_reproduce_proie probability that a prey reproduces
 * @param p_reproduce_predateur probability that a predator reproduces
 * @param temps_repousse_herbe time needed for a plant to regrow
 */
extern const float p_ch_dir;
extern const float p_reproduce_proie;
extern const float p_reproduce_predateur;
extern const int temps_repousse_herbe;

/**
 * @brief structure of an animal
 * @param x first coordinate
 * @param y second coordinate
 * @param dir directions of move: 0 - nothing, 1 - up/left, -1 - down/right
 * @param energie energy
 * @param suivant next animal in a linked list
 */
typedef struct _animal {
  int x;
  int y;
  int dir[2]; 
  float energie;
  struct _animal *suivant;
} Animal;

/**
 * ... text ...
 */
Animal *creer_animal(int x, int y, float energie);

/**
 * ... text ...
 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal);

/**
 * ... text ...
 */
unsigned int compte_animal_rec(Animal *la);

/**
 * ... text ...
 */
unsigned int compte_animal_it(Animal *la);

/**
 * ... text ...
 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal);

/**
 * ... text ...
 */
void enlever_animal(Animal **liste, Animal *animal);

/**
 * ... text ...
 */
Animal* liberer_liste_animaux(Animal *liste);

/**
 * ... text ...
 */
void afficher_ecosys(Animal *liste_predateur, Animal *liste_proie);

/**
 * ... text ...
 */
void bouger_animaux(Animal *la);

/**
 * ... text ...
 */
Animal *animal_en_XY(Animal *l, int x, int y);

/**
 * ... text ...
 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie);

/**
 * ... text ...
 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) ;

/**
 * ... text ...
 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]);

/**
 * ... text ...
 */
void reproduce(Animal **liste_animal, float p_reproduce);

/**
 * ... text ...
 */
void clear_screen();

/**
 * ... text ...
 */
void ecrire_animal(FILE *file, Animal *liste_anim, char *type);

/**
 * ... text ...
 */
void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur, Animal *liste_proie);

/**
 * ... text ...
 */
void lire_ecosys(const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie);


#endif
