/*
Titre: t_entree.c
Description: Programme qui implémente les fonctions de la structure t_entree.

Auteur: Nathan Guindon Durocher - William Blais Di Quinzio - Tri Tam Phan
Date: 2022-11-14
*/

/***********COMMANDES PRÉPROCESSEUR*************/
#include "t_entree.h"


/********* DÉFINITION DES FONCTION **************/

t_entree* t_entree_init(int num)
{

	t_entree* nouvelle_entree; //Creation d'une nouvelle entree
	char nom[4] = "E"; //Creaton d'un char commencant toujours par E et qui ne depassera 4 caractere (E + les 2 chiffres possibles + \0)

	nouvelle_entree = (t_entree*)malloc(sizeof(t_entree));

	if (nouvelle_entree == NULL) //si le malloc n'a pas reussi a allouer de la memoire
	{
		printf("Pas reussi a allouer de la memoire.\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	//set l'id au num fourni
	nouvelle_entree->id = num;

	//concatener le nom et l'id
	nouvelle_entree->nom = "E%d", num;

	//initialiser une nouvelle pin de sortie
	nouvelle_entree->pin = t_pin_sortie_init;

	return nouvelle_entree;

}

void t_entree_destroy(t_entree* entree)
{

	t_pin_sortie_destroy(entree->pin);
	//free
	free(entree);
}

t_pin_sortie* t_entree_get_pin(t_entree* entree)
{
	//retourne entree.pin puisque que le parametre est deja un pointeur
	return entree->pin;
}

int t_entree_est_reliee(t_entree* entree)
{
	//verifie si la pin de sortie est relier
	return t_pin_sortie_est_reliee(entree->pin);

}

void t_entree_reset(t_entree* entree)
{
	//reset la pin de sortie de l'entree en parametre
	t_pin_sortie_reset(entree->pin);
}

int t_entree_propager_signal(t_entree* entree)
{
	//si la valeur de la pin de sortie est a -1
	if (t_pin_sortie_get_valeur(entree->pin) == -1)
	{
		//retourne 1 si le signal a reussi a se propager, 0 sinon
		return t_pin_sortie_propager_signal(entree->pin);
	}
}

int t_entree_get_valeur(t_entree* entree)
{
	//retourne la valeur de la pin de sortie associer avec la l'entree en parametre
	return t_pin_sortie_get_valeur(entree->pin);

}