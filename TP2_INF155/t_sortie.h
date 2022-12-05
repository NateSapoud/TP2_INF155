/*
Module: T_SORTIE
Description: D�finit le type t_sortie (sortie de circuit) et fournit les
			 fonctions pour le manipuler.
Auteur: Anis Boubaker
Derni�re modification: 2018-03-19
*/


#ifndef SORTIE_H_
#define SORTIE_H_

#include "t_pin_entree.h"



typedef struct t_pin_entree t_pin_entree;

#define NOM_SORTIE_TAILLE_MAX 10 //Taille maximale du nom
								 //de la sortie
#define _CRT_SECURE_NO_WARNINGS

struct t_sortie{
	int id; //Identifiant num�rique de la sortie de circuit.
			//doit �tre unique parmi les sorties du circuit
	char *nom; //Nom de la sortie
	t_pin_entree *pin; //Pin de la sortie
};

typedef struct t_sortie t_sortie; 


/*
Fonction: T_SORTIE_INIT
Description: Cr�e une nouvelle sortie de circuit. Le constrcuteur re�oi un
			 identifiant num�rique qui (on assume) est unique dans le circuit.

			 � partir de cet identifiant, la fonction construit le nom de la sortie.
			 Ex.: S1 est le nom de la sortie ayant pour identifiant 1.

Param�tres:
- id: Entier repr�sentant l'identifiant num�rique de la sortie (unique dans un circuit)
Retour: Pointeur vers la sortie de circuit cr��e
Param�tres modifi�: Aucun.
*/
t_sortie *t_sortie_init(int num);

/*
Fonction: T_SORTIE_DESTROY
Description: Lib�re la m�moire occup�e par la sortie et tous ses composants (i.e. la pin).
NDE: Ne pas oublier de d�truire la pin_entr�e de la sortie.
Param�tres:
- sortie: Pointeur vers la sortie � d�truire.
Retour: Aucun.
*/
void t_sortie_destroy(t_sortie *sortie);

/*
Fonction: T_SORTIE_GET_PIN
Description: Accesseur - Retourne un pointeur vers la pin_entree de la sortie
			de circuit.
Param�tres:
- sortie: Pointeur vers la sortie de circuit dont on veut acc�der � la pin_entree.
Retour: Pointeur vers la pin_entree de la sortie de circuit.
*/
t_pin_entree *t_sortie_get_pin(t_sortie *sortie);


/*
Fonction: T_SORTIE_RELIER
Description: Relie sortie de circuit � un autre composant du circuit (entr�e ou une autre porte)
			 On note ici qu'on relie la pin_entree de la sortie vers une pin_sortie
			 d'un autre composant. Les seuls autres composants disposant de pin_sortie sont
			 les entr�es du circuit et les portes. 

			 Si la sortie a d�j� �t� reli�e, le nouveau lien �crase l'ancien. 

NDE: Pour faire la liaison, la fonction t_pin_entree_relier vous sera tr�s utile!
Param�tres:
- sortie: Pointeur vers la sortie de circuit � relier.
- source: La pin_sortie vers laquelle nous allons relier la pin_sortie de la sortie de
		  circuit. 
Retour: Bool�en : Vrai si la liaison a bien �t� effectu�e. Faux sinon. 
*/
int t_sortie_relier(t_sortie *dest, const t_pin_sortie *source);






/*
Fonction: T_SORTIE_EST_RELIEE
Description: V�rifie si une sortie de circuit est reli�e. Pour qu'elle soit reli�e,
			sa pin_entree doit �tre reli�e.
NDE: Il existe une fonction dans t_pin_entree qui vous permet
	 de v�rifier si une pin est reli�e. Utilisez-la!
Param�tres:
- sortie: Pointeur vers la sortie que l'on souhaite v�rifier.
Retour: Bool�en Vrai si la porte est enti�rement reli�e, Faux sinon.
*/
int t_sortie_est_reliee(t_sortie *sortie);

/*
Fonction: T_SORTIE_RESET
Description: R�initialise une sortie. Pour r�initialiser une sortie, il suffit
de r�-initialiser sa pin_entree.

NDE: Il y'a une fonctions pr�te dans le module t_pin_entree.

Param�tres:
- sortie: Pointeur vers la sortie de circuit � r�initialiser.
Retour: Aucun
*/
void t_sortie_reset(t_sortie *sortie);

/*
Fonction: T_SORTIE_GET_VALEUR
Description: Retourne la valeur du signal de la sortie. Ceci correspond � la valeur
			 du signal de sa pin_entree.

NDE: Il y'a une fonctions pr�te dans le module t_pin_entree.

Param�tres:
- sortie: Pointeur vers la sortie de circuit dont on veut connaitre la valeur.
Retour: Entier: valeur du signal � la sortie
*/
int t_sortie_get_valeur(t_sortie *sortie);

#endif