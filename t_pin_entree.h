/*
Module: T_PIN_ENTREE
Description: D�finit le type t_pin_entree. Une pin_entree est un point de connexion appartenant 
		     � un �l�ment du circuit qui re�oit un signal (mais n'en �met pas). 
			 Les �l�ments d'un circuit ayant une pin d'entr�e de signal sont les portes (les entr�es
			 des portes) ainsi que les sorties du circuit.

			 Si une pin entr�e re�oit un signal, ce signal est stock� dans le champs valeur. Une 
			 pin_entree qui est inactive (pas aliment�e) a la valeur -1. 

			 Une pin d'entree permet de relier le composant auquel elle appartient � un autre composant. 
			 Elle doit �tre reli�e � une "pin de sortie" du composant auquel on souhaite se connecter.

Auteur: Anis Boubaker
Derni�re modification: 2018-03-19
*/

#ifndef T_PIN_ENTREE_H_
#define T_PIN_ENTREE_H_

#include <stdlib.h>
#include "t_pin_sortie.h"

typedef struct t_pin_sortie t_pin_sortie;

//D�finit le type t_pin_entree
struct t_pin_entree {
	int valeur; //Valeur du signal re�u par la pin entree. -1 si la pin est inactive.
	t_pin_sortie *liaison; //Pointeur vers la pin sortie
								  //� laquelle cette pin est reli�e
};

typedef struct t_pin_entree t_pin_entree;

/*
Fonction: T_PIN_ENTREE_INIT (constructeur)
Description: Cr�e une nouvelle pin entr�e.
Param�tres: Aucun
Retour: Pointeur vers la pin entr�e qui a �t� cr��e
Param�tres modifi�: N/A.
*/
t_pin_entree *t_pin_entree_init();

/*
Fonction: T_PIN_ENTREE_DESTROY (Destructeur)
Description: Lib�re la m�moire occup�e par la pin entree.
Param�tres:
- pin: Pointeur vers la pin entr�e � d�truire.
Retour: Aucun.
Param�tres modifi�: pin
*/
void t_pin_entree_destroy(t_pin_entree *pin);

/*
Fonction: T_PIN_ENTREE_GET_VALEUR (Accesseur)
Description: Accesseur du champs valeur.
Param�tres:
- pin: Pointeur vers la pin entr�e.
Retour: (entier) Valeur du pin : 0, 1 ou -1.
Param�tres modifi�: aucun
*/
int t_pin_entree_get_valeur(const t_pin_entree *pin);

/*
Fonction: T_PIN_ENTREE_GET_VALEUR (Mutateur)
Description: Mutateur du champs valeur.
Param�tres:
- pin: Pointeur vers la pin entr�e.
- valeur: nouvelle valeur de la pin entr�e (doit obligatoirement �tre -1, 0 ou 1)
Retour: Aucun
Param�tres modifi�: pin
*/
void t_pin_entree_set_valeur(t_pin_entree *pin, int valeur);

/*
Fonction: T_PIN_ENTREE_RELIER
Description: Relie la pin entr�e � une pin sortie. Cette fonction permet de relier le composant, auquel 
			 apparatien la pin entr�e, � un autre composant, auquel appartient la pin sortie.

			 Cette fonction s'assure que la relation est bi-directionnelle: la pin sortie aura la pin entr�e
			 comme une des pins auxquelles elle est reliee (fait en utilisant la fontion t_pin_sortie_ajouter_lien)
Param�tres:
- pin_entree: La pin entr�e � relier
- pin_sortie: La pin sortie � laquelle la pin entr�e sera reli�e.
Retour: Aucun
*/
void t_pin_entree_relier(t_pin_entree *pin_entree, const t_pin_sortie *pin_sortie);


/*
Fonction: T_PIN_ENTREE_EST_RELIEE
Description: Permet de v�rifier si une pin entr�e est reli�e � une pin sortie.

Param�tres:
- pin_entree: La pin entr�e dont on veut v�rifier la liaison
Retour: Bool�en: Vrai si la pin entr�e est reli�e, Faux sinon.
*/
int t_pin_entree_est_reliee(t_pin_entree *pin);

/*
Fonction: T_PIN_ENTREE_RESET
Description: R�-initialise la valeur de la pin entree
Parametre: 
- pin_entree: La pin entr�e dont on veut r�initialiser la valeur
Retour: Aucun.
*/
void t_pin_entree_reset(t_pin_entree *pin);


#endif