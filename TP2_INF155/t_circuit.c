/*
Titre: t_circuit.c
Description: Programme qui implémente les fonctions de la structure t_circuit.

Auteur: Nathan Guindon Durocher - William Blais Di Quinzio - Tri Tam Phan
Date: 2022-11-14
*/

/***********COMMANDES PRÉPROCESSEUR*************/
#include "t_circuit.h"


/********* DÉFINITION DES FONCTION **************/

t_circuit* t_circuit_init(void)
{
	t_circuit* nouveau_circuit;
	nouveau_circuit = (t_circuit*)malloc(sizeof(t_circuit));

	if (nouveau_circuit == NULL)
	{
		printf("Pas assez de memoire a allouer!");
		system("pause");
		exit(EXIT_FAILURE);
	}


	return nouveau_circuit;
}

void t_circuit_destroy(t_circuit* circuit)
{
	for (int i = 0; i < MAX_ENTREES; i++)
	{
		t_porte_destroy(circuit->portes[i]);
		t_entree_destroy(circuit->entrees[i]);
		t_sortie_destroy(circuit->sorties[i]);
	}

	for (int i = MAX_ENTREES; i < CIRCUIT_MAX_PORTES; i++)
	{
		t_porte_destroy(circuit->portes[i]);
	}

	free(circuit);
}

t_porte* t_circuit_ajouter_porte(t_circuit* circuit, e_types_portes le_type)
{
	//verification pour savoir si on a deja le nombre maximal de porte;
	if (circuit->nb_portes >= CIRCUIT_MAX_PORTES)
	{
		return NULL;
	}
	//creation d'une nouvelle porte dans le tas
	t_porte* nouvelle_porte;
	nouvelle_porte = t_porte_init(circuit->nb_portes + 1, le_type);
	if (nouvelle_porte == NULL)
	{
		return NULL;
	}

	circuit->nb_portes++;

	return nouvelle_porte;
}

t_entree* t_circuit_ajouter_entree(t_circuit* circuit)
{
	if (circuit->nb_entrees < MAX_ENTREES)
	{
		t_entree* nouvelle_entree;
		nouvelle_entree = t_entree_init(circuit->nb_entrees + 1);
		if (nouvelle_entree == NULL)
		{
			return NULL;
		}
		circuit->nb_entrees++;

		return nouvelle_entree;
	}
	else
		return NULL;
}

t_sortie* t_circuit_ajouter_sortie(t_circuit* circuit)
{
	if (circuit->nb_sorties < MAX_SORTIES)
	{
		t_sortie* nouvelle_sortie;
		nouvelle_sortie = t_sortie_init(circuit->nb_sorties + 1);
		if (nouvelle_sortie == NULL)
		{
			return NULL;
		}
		circuit->nb_sorties++;

		return nouvelle_sortie;
	}
	else 
		return NULL;
}

int t_circuit_est_valide(t_circuit* circuit)
{

	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		if (!t_pin_sortie_est_reliee(circuit->entrees[i]->pin))
			return 0;
	}
	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		if (!t_pin_sortie_est_reliee(circuit->sorties[i]->pin))
			return 0;
	}
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		for (int k = 0; k < circuit->portes[i]->nb_entrees; k++)
		{
			if (!t_pin_sortie_est_reliee(circuit->portes[i]->entrees[k]))
				return 0;
		}

		if (!t_pin_sortie_est_reliee(circuit->portes[i]->sortie))
			return 0;
	}
	return 1;

}