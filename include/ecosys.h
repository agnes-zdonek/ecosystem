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
 * @param energie energy > 0
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
 * @brief creates an animal
 * @param x first coordinate
 * @param y second coordinate
 * @param energie energy
 * @return created animal
 */
Animal *creer_animal(int x, int y, float energie);

/**
 * @brief appends animal at the beggining of a list
 * @param liste list
 * @param animal animal
 * @return pointer to the beggining of a list
 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal);

/**
 * @brief recursive function, counts number of animals in a list
 * @param la list of animals
 * @return number of animals in a list
 */
unsigned int compte_animal_rec(Animal *la);

/**
 * @brief iterative function, counts number of animals in a list
 * @param la list of animals
 * @return number of animals in a list
 */
unsigned int compte_animal_it(Animal *la);

/**
 * @brief creates and appends animal at the beggining of a list
 * @param x first coordinate
 * @param y second coordinate
 * @param energie energy
 * @param liste_animal pointer to the list of animals
 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal);

/**
 * @brief deletes an animal from a list
 * @param liste pointer to the list of animals
 * @param animal animal to delete
 */
void enlever_animal(Animal **liste, Animal *animal);

/**
 * @brief frees list of animals and memory allocated to it
 * @param liste liste of animals
 * @return null
 */
Animal* liberer_liste_animaux(Animal *liste);

/**
 * @brief prints a grind with predators and prey in it
 * @param liste_predateur list of predators
 * @param liste_proie list of prey
 */
void afficher_ecosys(Animal *liste_predateur, Animal *liste_proie);

/**
 * @brief changes place of an animal according to what they have in dir[2]
 * @param la animal
 */
void bouger_animaux(Animal *la);

/**
 * @brief verfies if animal l is on x,y coordinates
 * @param la animal
 * @param x first coordinate
 * @param y second coordinate
 * @return pointer to the animal or null
 */
Animal *animal_en_XY(Animal *l, int x, int y);

/**
 * @brief moves predators using bouger_animaux, manages their energy, if there is a prey on predator's case, predator eats it and has it's energy, reproduces predators
 * @param liste_predateur pointer to the list of predators
 * @param liste_proie pointer to the list of prey
 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie);

/**
 * @brief moves prey using bouger_animaux, manages their energy, eats plant if it's in prey's case, reproduces prey
 * @param liste_proie pointer to the list of prey
 * @param monde the grid we place our animals/plants in
 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) ;

/**
 * @brief regrows plants
 * @param the grind we place our animals/plants in
 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]);

/**
 * @brief reproduces animals
 * @param p_reproduce probability of reproduction
 */
void reproduce(Animal **liste_animal, float p_reproduce);

/**
 * @brief clears terminal
 */
void clear_screen();

/**
 * @brief writes one type of animals into a text file
 * @param file file
 * @param liste_animal list of animals
 * @param type string indicating if those are predators/prey
 */
void ecrire_animal(FILE *file, Animal *liste_anim, char *type);

/**
 * @brief writes list of animals into a text file
 * @param nom_fichier name of an out file
 * @param liste_predateur list of predators
 * @param liste_poire list of prey
 */
void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur, Animal *liste_proie);

/**
 * @brief reads list of animlas from a file to lists 
 * @param nom_fichier name of an out file
 * @param liste_predateur pointer to list of predators
 * @param liste_poire pointer to list of prey
 */
void lire_ecosys(const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie);


#endif
