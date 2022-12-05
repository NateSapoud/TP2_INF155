/*
Titre: t_sortie.c
Description: Programme qui implémente les fonctions de la structure t_sortie.

Auteur: Tri-Tam Phan - William Blais Di Quinzio - Nathan Guindon Durocher
Date: 2022-11-28
*/

/***********COMMANDES PRÉPROCESSEUR*************/
#include "t_sortie.h"


/********* DÉFINITION DES FONCTION **************/

t_sortie* t_sortie_init(int num)
{
	t_sortie* nouvelle_sortie; //Cree une nouvelle sortie
	//Nom de la sortie comportant 4 charactere; le premier qui est "S" (pour sortie), le deuxiemee et troisiem qui vont etre les chiffres, et le quatrieme qui est le \0
	nouvelle_sortie = (t_sortie*)malloc(sizeof(t_sortie));

	if (nouvelle_sortie == NULL) //va verifier si la memoire est epuisee ou non. si elle est epuisee, quitte la fonction
	{
		printf("Espace memoire epuisee pour la fonction nouvelle_sortie!");
		system("pause");
		exit (EXIT_FAILURE);
	}

	nouvelle_sortie->id = num; //la valeur "id" du struct "t_sortie" va prendre la valeur du numero que l'utilisateur a mis 
	nouvelle_sortie->nom = (char*)malloc(sizeof(char) * NOM_SORTIE_TAILLE_MAX);
	if (nouvelle_sortie == NULL)
	{
		free(nouvelle_sortie);
		printf("Espace memoire epuisee pour la fonction nouvelle_sortie!");
		system("pause");
		exit(EXIT_FAILURE);
	}
	sprintf(nouvelle_sortie->nom, "S%d", num);//Assignation du nom de la nouvelle sortie
	

	nouvelle_sortie->pin = t_pin_entree_init(); //Crée une nouvelle pin sortie.

	return nouvelle_sortie; //retourne le pointeur vers la sortie de circuit créée
}

void t_sortie_destroy(t_sortie* sortie)
{
	t_pin_sortie_destroy(sortie->pin); //va libérer la memoire occupée par la pin de la fonction "sortie"
	free(sortie); //libère le bloc de memoire alloue dynamiquement pour la fonction "sortie"
}

t_pin_entree* t_sortie_get_pin(t_sortie* sortie)
{
	return sortie->pin; //va retourner un pointeur de la sortie vers l'entree
}

int t_sortie_relier(t_sortie* dest, const t_pin_sortie* source) 
{
	t_pin_entree_relier(dest->pin,source);

	//s'il y a une liaison de fait, va retourner vrai (1). Sinon, s'il n'y a pas de lien, retourne faux (0)
	if (t_pin_entree_est_reliee(dest->pin))
		return 1;
	else
		return 0;
	
}

int t_sortie_est_reliee(t_sortie* sortie)
{

	//s'il y a une liaison de fait, va retourner vrai (1). Sinon, s'il n'y a pas de lien, retourne faux (0)
	if (t_pin_entree_est_reliee(sortie))
	{
		return 1;
	}
	else if (!t_pin_entree_est_reliee(sortie))
	{
		return 0;
	}

}

void t_sortie_reset(t_sortie* sortie)
{
	t_pin_entree_reset(sortie->pin); //va réinitialiser la fonction "sortie"
}

int t_sortie_get_valeur(t_sortie* sortie)
{
	t_pin_entree_get_valeur(sortie->pin); //va prendre la valeur de la sortie 
}




