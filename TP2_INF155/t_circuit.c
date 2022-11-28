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
	t_porte* nouvelle_porte;
	nouvelle_porte = t_porte_init(circuit->nb_portes, le_type);
	if (nouvelle_porte == NULL)
	{
		return NULL;
	}
	circuit->nb_portes++;

	return nouvelle_porte;
}