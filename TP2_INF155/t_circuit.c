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
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte_destroy(circuit->portes[i]);
	}

	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_destroy(circuit->entrees[i]);
	}

	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie_destroy(circuit->sorties[i]);
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
	//boucle qui regarde si chaque pin de sortie de chaque entree est relier
	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		if (!t_pin_sortie_est_reliee(circuit->entrees[i]->pin))
			return 0;
	}
	//boucle qui regarde si chaque pin d'entree de chaque sortie est relier
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

int t_circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{
	if (nb_bits < circuit->nb_entrees) //verification si le nb_bits est plus grand ou egal au nombre d'entree
	{
		return 0;
	}

	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		circuit->entrees[i]->pin->valeur = signal[i];
	}
	return 1;
}

void t_circuit_reset(t_circuit* circuit)
{
	for (int i = 0; i < circuit->nb_portes; i++)
	{
		t_porte_reset(circuit->portes[i]);
	}

	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_reset(circuit->entrees[i]);
	}

	for (int i = 0; i < circuit->nb_sorties; i++)
	{
		t_sortie_reset(circuit->sorties[i]);
	}
}

int t_circuit_propager_signal(t_circuit* circuit)
{
	int nb_iterations = 0;
	t_porte* porte_courante;
	t_file_porte* file;

	file = t_file_porte_initialiser(circuit->nb_portes);

	if (!t_circuit_est_valide(circuit))
	{
		return 0;
	}

	for (int i = 0; i < circuit->nb_entrees; i++)
	{
		t_entree_propager_signal(circuit->entrees[i]);
	}

	for (int i = 0; i < circuit->nb_portes; i++)
	{
		file->nb_elts++;
		file->tab[i] = circuit->portes[i];

	}

	while (file->nb_elts >= 0 && nb_iterations < pow(circuit->nb_portes, 2))
	{
		porte_courante = t_file_porte_defiler(file);
		t_porte_propager_signal(porte_courante);

		if (!t_porte_propager_signal(porte_courante))
		{
			t_file_porte_enfiler(file, porte_courante);
		}
		nb_iterations++;
	}

	if (nb_iterations == pow(circuit->nb_portes, 2))
	{
		return 0; //Il a une boucle dans le signal
	}
	return 1; //Le signal a propager
}