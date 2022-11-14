/*
Module: T_ENTREE
Description: D�finit le type t_entree (Entr�e de circuit) et fournit les 
			 fonctions pour le manipuler.
Auteur: Anis Boubaker
Derni�re modification: 2018-03-19
*/

#ifndef ENTREE_H_
#define ENTREE_H_

#include "t_pin_sortie.h"

#define NOM_ENTREE_TAILLE_MAX 10 //Taille maximale du nom de l'entr�e
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct t_pin_sortie t_pin_sortie;

typedef struct t_entree{
	int id; //Identifiant num�rique de l'entr�e
			//doit �tre unique parmi les entr�es 
			//du circuit
	char *nom; //Nom de l'entr�e
	t_pin_sortie *pin; //Pin de sortie
} t_entree;



/*
Fonction: T_ENTREE_INIT
Description: Cr�e une nouvelle entr�e de circuit. Le constrcuteur re�oi un 
			 identifiant num�rique qui (on assume) est unique dans le circuit.

			 � partir de cet identifiant, la fonction construit le nom de l'entr�e. 
			 Ex.: E1 est le nom de l'entr�e ayant pour identifiant 1.

Param�tres:
- id: Entier repr�sentant l'identifiant num�rique de l'entr�e (unique dans un circuit)
Retour: Pointeur vers l'entr�e de circuit cr��e
Param�tres modifi�: Aucun.
*/
t_entree *t_entree_init(int num);

/*
Fonction: T_ENTREE_DESTROY
Description: Lib�re la m�moire occup�e par l'entr�e et tous ses composants (i.e. la pin).
NDE: Ne pas oublier de d�truire la pin_sortie de l'entr�e.
Param�tres:
- entree: Pointeur vers l'entr�e � d�truire.
Retour: Aucun.
*/
void t_entree_destroy(t_entree *entree);

/*
Fonction: T_ENTREE_GET_PIN
Description: Accesseur - Retourne un pointeur vers la pin_sortie de l'entr�e
Param�tres:
- entree: Pointeur vers l'entr�e de circuit dont on veut acc�der � la pin_sortie.
Retour: Pointeur vers la pin_sortie de l'entr�e.
*/
t_pin_sortie *t_entree_get_pin(t_entree *entree);

/*
Fonction: T_ENTREE_EST_RELIEE
Description: V�rifie si une entr�e de circuit est reli�e. Pour qu'elle soit reli�e,
			sa pin de sortie doit �tre reli�e.
NDE: Il existe des fonctions dans t_pin_sortie qui vous permet
	 de v�rifier si une pin est reli�e. Utilisez-la!
Param�tres:
- entree: Pointeur vers l'entr�e que l'on souhaite v�rifier.
Retour: Bool�en Vrai si la porte est enti�rement reli�e, faux sinon.
*/
int t_entree_est_reliee(t_entree *entree);

/*
Fonction: T_ENTREE_RESET
Description: R�initialise une entr�e. Pour r�initialiser une entr�e, il suffit
			 de r�-initialiser sa pin_sortie.

NDE: Il y'a une fonctions pr�te dans le module t_pin_sortie.

Param�tres:
- entree: Pointeur vers l'entr�e de circuit � r�initialiser.
Retour: Aucun
*/
void t_entree_reset(t_entree *entree);

/*
Fonction: T_ENTREE_PROPAGER_SIGNAL
Description: Propage le signal � partir de l'entr�e de circuit pass�e en param�tre.
			 Pour que le signal puisse se propager, il faut que la pin_sortie de
			 l'entr�e ait une valeur (i.e. !=-1).

NDE: Utilisez la fonction t_pin_sortie_propager_signal.
Param�tres:
- entr�e: Pointeur vers l'entr�e de circuit dont on veut propager le signal.
Retour: Bool�en: vrai si le signal a pu se propager (i.e. la pin_sortie a une
		valeur), Faux sinon.
*/
int t_entree_propager_signal(t_entree *entree);

/*
Fonction: T_ENTREE_GET_VALEUR
Description: Retourne la valeur du signal de l'entr�e. Ceci correspond � la valeur
			du signal de sa pin_sortie.

Param�tres:
- entree: Pointeur vers l'entr�e de circuit dont on veut connaitre la valeur.
Retour: Entier: valeur du signal � l'entr�e du circuit. 
*/
int t_entree_get_valeur(t_entree *entree);

#endif