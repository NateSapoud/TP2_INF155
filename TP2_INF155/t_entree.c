/*
Titre: t_entree.c
Description: Programme qui implémente les fonctions de la structure t_entree.

Auteur: Nathan Guindon Durocher
Date: 2022-11-14
*/

/***********COMMANDES PRÉPROCESSEUR*************/
#include "t_entree.h"


/********* DÉFINITION DES FONCTION **************/

t_entree* t_entree_init(int num)
{

	t_entree nouvelle_entree; //Creation d'une nouvelle entree
	char nom[4] = "E"; //Creaton d'un char commencant toujours par E et qui ne depassera 4 caractere (E + les 2 chiffres possibles + \0)

	nouvelle_entree.id = 1;

	strcat(nom, num);
	nouvelle_entree.nom = nom;

	return &nouvelle_entree;

}

void t_entree_destroy(t_entree* entree)
{
	entree->id = NULL;
	entree->nom = NULL;
}
