/*
Module: T_PORTE
Description: D�finit le type porte et fournit les fonctions pour manipuler une porte.
Note: Ce module a �t� con�u de sorte � ce qu'il soit facielement extensible pour traiter
      des portes peronnalis�es (i.e. des circuits qu'on r�utilise comme des portes dans 
	  d'autres circuits. Pour limiter le travail des �tudiants, cette fonctionnalit� a �t�
	  abandonn�e mais il n'en demeure pas moins un point d'�volution potentiel du projet. 
      Les �tudiants courageux sont encourag�s � consid�rer, voir impl�menter cette �volution.
Auteur: Anis Boubaker
Derni�re modification: 2018-03-19
*/

#ifndef T_PORTE_H_
#define T_PORTE_H_

#include <string.h>
#include <stdio.h>
#include "t_pin_entree.h"
#include "t_pin_sortie.h"
#include "t_circuit.h"


typedef struct t_pin_entree t_pin_entree;
typedef struct t_pin_sortie t_pin_sortie;
typedef struct t_circuit t_circuit;


#define NOM_PORTE_TAILLE_MAX 10 //Taille maximale du nom d'une porte
								//En nombre de caract�res

/*
�num�ration: E_TYPES_PORTES
Description: �num�re les types de portes permis 
*/
enum e_types_portes { PORTE_ET, PORTE_OU, PORTE_NOT, PORTE_XOR };
typedef enum e_types_portes e_types_portes;

/*
D�finit le type t_porte qui permet de stocker l'information relative � une porte.
*/
struct t_porte {
	int id; //Identifiant num�rique de la porte (doit �tre unique dans un circuit)
	//Nom de la porte construit automatiquement � partie de l'identifiant (ex.: P1)
	char *nom; 
	e_types_portes type; //Type de la porte (parmi les types �num�r�s)
	//Tab statique de pointeurs vers des pin entr�e. L'ensemble des pins entr�e
	//repr�sente les entr�es de la porte.
	t_pin_entree *entrees[MAX_ENTREES];
	//Pointeur vers la pin sortie de la porte.
	t_pin_sortie *sortie; 
	//Nombre d'entr�es de la porte. Repr�sente le nombre d'�l�ments significatifs
	//dans le tableau du champs "entrees"
	int nb_entrees; 
};

typedef struct t_porte t_porte;

/*
Fonction: T_PORTE_INIT
Description: Cr�e une nouvelle porte du type sp�cifi� en param�tre. Selon le type, la 
			 fonction initialise les pin_entree et pin_sortie qui conviennent au type.

			 L'identifiant num�rique re�u en param�tre doit �tre unique dans le circuit
			 (aucune autre porte ne doit avoir le m�me identifiant). � partir de cet 
			 identifiant, la fonction construit le nom de la porte. Ex.: P2 est le nom 
			 de la porte ayant pour identifiant 2.

Param�tres: 
- id: Entier repr�sentant l'identifiant num�rique de la porte (unique dans un circuit)
- type: Le type de porte � cr�er, selon la liste des types pr�d�finis dans t_types_portes
Retour: Pointeur vers la porte cr��e
Param�tres modifi�: Aucun.
*/
t_porte *t_porte_init(int id, e_types_portes type);

/*
Fonction: T_PORTE_DESTROY
Description: Lib�re la m�moire occup�e par la porte et tous ses composants.
NDE: Ne pas oublier de d�truire toutes les pin_entree et pin_sortie appartenant � la porte.
Param�tres:
- porte: Pointeur vers la porte � d�truire.
Retour: Aucun.
*/
void t_porte_destroy(t_porte *porte);

/*
Fonction: T_PORTE_CALCULER_SORTIES
Description: Calcule la valeur des pin sorties de la porte, selon la valeur des pin_entree 
			 et le type de porte. Par exemple, si la porte est une porte ET, et que les deux
			 pin_entree de la porte ont une valeur de 1, la pin_sortie de la porte doit avoir
			 la valeur 1. 
NDE: 
- N'oubliez pas qu'il existe des op�rateurs binaires en C. Utilisez-les!
- N'oubliez pas que, pour modifier la valeur d'une pin_sortie (par ex.), vous devez utiliser
  le mutateur corespondant (dans l'exemple t_pin_sortie_set_valeur) et ne pas modifier la valeur
  du champs directement (car nous sommes � l'ext�rieur du module t_pin_sortie).
Param�tres:
- porte: Pointeur vers la porte dont on souhaite calculer les sorties (dans cette version du 
		 programme, il n'existe qu'une seule sortie par porte).
Retour: Aucun.
*/
void t_porte_calculer_sorties(t_porte *porte);


/*
Fonction: T_PORTE_RELIER
Description: Relie une des entr�es de la porte � un autre composant du circuit (entr�e ou une autre porte)
			 On note ici qu'on relie une des pin_entree de la porte vers une pin_sortie
			 d'un autre composant. Les seuls autres composants disposant de pin_sortie sont
			 les entr�es du circuit et les autres portes. 

			 Si l'entr�e de la porte en question a d�j� �t� reli�e, l'ancien lien est remplac�
			 par le nouveau.

NDE: Pour faire la liaison, la fonction t_pin_entree_relier vous sera tr�s utile!
Param�tres:
- porte: Pointeur vers la porte � relier.
- num_entree: l'indice de la pin_entree � relier dans le tableau des entr�es. 
			  Si cet indice n'existe pas, la fonction retourne faux.  
- source: La pin_sortie vers laquelle nous allons relier l'entr�e de la porte. 
Retour: Bool�en : Vrai si la liaison a bien �t� effectu�e. Faux sinon. 
*/
int t_porte_relier(t_porte *dest, int num_entree, const t_pin_sortie *source);

/*
Fonction: T_PORTE_EST_RELIEE
Description: V�rifie si une porte est enti�rement reli�e. Pour qu'elle soit enti�rement
			 reli�e, ses pin d'entr�es et ses pins de sortie doivent �tre reli�es.
NDE: Il existe des fonctions dans t_pin_entree et t_pin_sortie qui vous permettent
     de v�rifier si une pin est reli�e. Utilisez-les!
Param�tres:
- porte: Pointeur vers la porte que l'on souhaite v�rifier.
Retour: Bool�en Vrai si la porte est enti�rement reli�e, faux sinon.
*/
int t_porte_est_reliee(t_porte *porte);

/*
Fonction: T_PORTE_RESET
Description: R�initialise une porte. Pour r�initialiser une porte, il suffit
			 de r�-initialiser chacune de ses pin. 
			 
NDE: Encore ici, il y'a des fonctions pr�tes dans les modules t_pin_entree
	 et t_pin_sortie pour r�-initialiser les pins.
Param�tres:
- porte: Pointeur vers la porte � r�initialiser.
Retour: Aucun
*/
void t_porte_reset(t_porte *porte);

/*
Fonction: T_PORTE_PROPAGER_SIGNAL
Description: Propage le signal � partir de la porte pass�e en param�tre.
			 Pour que le signal puisse se propager, il faut que la porte
			 ait une valeur sur chacune de ses entr�es (i.e. !=-1).
			 Si c'est le cas, il suffit de calculer la sortie, puis de propager
			 le signal � partir de la pin_sortie.

NDE: Une fois que vous avez calcul� la valeur de la pin sortie, utilisez 
	 la fonction t_pin_sortie_propager_signal.
Param�tres:
- porte: Pointeur vers la porte dont on veut propager le signal.
Retour: Bool�en: vrai si le signal a pu se propager (i.e. toutes les entr�es ont
		r��u un signal, Faux sinon.
*/
int t_porte_propager_signal(t_porte *porte);



/*
Fonction: T_PORTE_GET_PIN_SORTIE
Description: Accesseur - Retourne un pointeur vers la pin_sortie de la porte.
Param�tres:
- porte: Pointeur vers la porte dont on veut acc�der � la pin_sortie.
Retour: Pointeur vers pin_sortie de la porte/
*/
t_pin_sortie* t_porte_get_pin_sortie(t_porte* porte);

#endif