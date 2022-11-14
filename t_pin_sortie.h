/*
Module: T_PIN_SORTIE
Description: D�finit le type t_pin_sortie. Une pin_sortie est un point de connexion appartenant
			 � un �l�ment du circuit qui �met un signal (mais n'en re�oit pas).
			 Les �l�ments d'un circuit ayant une pin sortie sont les portes (les sorties des portes) 
			 ainsi que les entr�es du circuit.

			 Pour qu'une pin sortie �mette un signal, ce signal doit �tre stock� dans le champs valeur. 
			 Une pin_sortie qui est inactive (pas aliment�e) aura la valeur -1.

			 Une pin sortie permet de relier le composant auquel elle appartient � d'autres composants.
			 Elle doit �tre reli�e � des "pin d'entr�e" des composants auquel on souhaite se connecter.

			 Note: Contrairement � une pin d'entr�e, une pin de sortie peut �tre reli�e � plusieurs 
			 pin d'entr�e : Ceci permet d'�mettre le m�me signal � plusieurs composants.

Auteur: Anis Boubaker
Derni�re modification: 2018-03-19
*/

#ifndef T_PIN_SORTIE_H_
#define T_PIN_SORTIE_H_

#define SORTIE_MAX_LIAISONS 10

#include "t_pin_entree.h"
#include "t_circuit.h"

typedef struct t_pin_entree t_pin_entree;
typedef struct t_circuit t_circuit;


//D�finit le type t_pin_sortie
struct t_pin_sortie {
	int valeur; //Valeur du signal re�u par la pin entree. -1 si la pin est inactive.
	//Tableau de pointeurs vers des pin entr�e auquel cette pin sortie est connect�e
	t_pin_entree *liaisons[SORTIE_MAX_LIAISONS];
	//Nombre de pin entr�e vers lesquels cette pin sortie est connect�e.
	//Ce champs repr�sente le nombre d'�l�ments effectifs du tableau liaisons.
	int nb_liaisons;
};
typedef struct t_pin_sortie t_pin_sortie;

/*
Fonction: T_PIN_SORTIE_INIT (constructeur)
Description: Cr�e une nouvelle pin sortie.
Param�tres: Aucun
Retour: Pointeur vers la pin sortie qui a �t� cr��e
Param�tres modifi�: N/A.
*/
t_pin_sortie *t_pin_sortie_init(void);

/*
Fonction: T_PIN_SORTIE_DESTROY (Destructeur)
Description: Lib�re la m�moire occup�e par la pin sortie.
Param�tres:
- pin: Pointeur vers la pin sortie � d�truire.
Retour: Aucun.
Param�tres modifi�: pin
*/
void t_pin_sortie_destroy(t_pin_sortie *pin);

/*
Fonction: T_PIN_SORTIE_GET_VALEUR (Accesseur)
Description: Accesseur du champs valeur.
Param�tres:
- pin: Pointeur vers la pin sortie.
Retour: (entier) Valeur du pin : 0, 1 ou -1.
Param�tres modifi�: aucun
*/
int t_pin_sortie_get_valeur(t_pin_sortie *pin);

/*
Fonction: T_PIN_SORTIE_GET_VALEUR (Mutateur)
Description: Mutateur du champs valeur.
Param�tres:
- pin: Pointeur vers la pin sortie.
- valeur: nouvelle valeur de la pin sortie (doit obligatoirement �tre -1, 0 ou 1)
Retour: Aucun
Param�tres modifi�: pin
*/
void t_pin_sortie_set_valeur(t_pin_sortie *pin, int valeur);

/*
Fonction: T_PIN_SORTIE_AJOUTER_LIEN
Description: Relie la pin sortie � une pin entr�e. Cette fonction permet de relier le composant, auquel
			 apparatien la pin sortie, � un autre composant, auquel appartient la pin entr�e.

			 La fonction doit v�rifier qu'on exc�de le nombre maximal de liens autoris�s 
			 (SORTIE_MAX_LIAISONS)
Param�tres:
- pin_sortie: La pin sortie � relier
- pin_entree: La pin entr�e � laquelle la pin sortie sera reli�e.
Retour: Vrai si le lien a bien �t� ajout�, faux sinon.
*/
int t_pin_sortie_ajouter_lien(t_pin_sortie *pin_sortie, const t_pin_entree *pin_entree);

/*
Fonction: T_PIN_SORTIE_SUPPRIMER_LIEN
Description: Supprime un lien existant entre la pin_sortie et une pin_entree pass�e en param�tre.
			 Si il n'existe aucun lien entre ces pins, la fonction n'aura aucun effet.

Param�tres:
- pin_sortie: La pin sortie dont on veut supprimer le lien
- pin_entree: La pin entr�e vers laquelle la pin sortie est li�e.
Retour: Aucun
*/
void t_pin_sortie_supprimer_lien(t_pin_sortie *pin_sortie, const t_pin_entree *pin_entree);


/*
Fonction: T_PIN_SORTIE_EST_RELIEE
Description: Permet de v�rifier si une pin sortie est reli�e � au moins une pin entr�e.

Param�tres:
- pin_sortie: La pin sortie dont on veut v�rifier la liaison
Retour: Bool�en: Vrai si la pin sortie est reli�e, Faux sinon.
*/
int t_pin_sortie_est_reliee(t_pin_sortie *pin);

/*
Fonction: T_PIN_SORTIE_PROPAGER_SIGNAL
Description: Fonction qui propage le signal de la pin sortie vers toutes les pin entr�e 
			 avec lesquelles elle est reli�e.

			 La pin ne doit pas �tre inactive (valeur = -1) pour que le signal puisse se 
			 propager.

Param�tres:
- pin_sortie: La pin sortie dont on veut propager le signal
Retour: Bool�en: Vrai si le signal s'est bien propag�, faux sinon. Le signal ne peut se propager
	    si la pin est inactive ou si elle n'est reli�e � aucune pin entr�e.
*/
int t_pin_sortie_propager_signal(t_pin_sortie *pin);

/*
Fonction: T_PIN_ENTREE_RESET
Description: R�-initialise la valeur de la pin entree
Parametre:
- pin_entree: La pin entr�e dont on veut r�initialiser la valeur
Retour: Aucun.
*/
void t_pin_sortie_reset(t_pin_sortie *pin);

/*
Fonction: TPIN_SORTIE_SERIALISER_LIENS
Description: Transforme en texte les informations de la pin sortie.
*/
void t_pin_sortie_serialiser_liens(t_pin_sortie *pin, t_circuit *circuit, char *resultat);

#endif