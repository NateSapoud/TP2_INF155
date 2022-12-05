/*
Titre: t_porte.c
Description: Programme incluant toute les fonctions disponible dans le module t_porte.
Note: Ce module a été conçu de sorte à ce qu'il soit facielement extensible pour traiter
	  des portes peronnalisées (i.e. des circuits qu'on réutilise comme des portes dans
	  d'autres circuits. Pour limiter le travail des étudiants, cette fonctionnalité a été
	  abandonnée mais il n'en demeure pas moins un point d'évolution potentiel du projet.
	  Les étudiants courageux sont encouragés à considérer, voir implémenter cette évolution.
Auteur: William Blais Di Quinzio
		Nathan Guindon Durocher
		Tri-Tam Phan
Dernière modification: 2022-11-14
*/

/***********COMMANDES PRÉPROCESSEUR*************/
#include "t_porte.h"



t_porte* t_porte_init(int id, e_types_portes type)
{
	t_porte	*nouvelle_porte;
	nouvelle_porte = (t_porte*)malloc(sizeof(t_porte)); //Allocation dynamique de memoire pour creer une porte

	if (nouvelle_porte == NULL) //Verification de memoire
	{
		exit(EXIT_FAILURE);
	}

	nouvelle_porte->type = type;						//Initialisation de nos valeurs
	nouvelle_porte->id = id;
	nouvelle_porte->sortie = t_pin_sortie_init();
	nouvelle_porte->entrees[0] = t_pin_entree_init();

	nouvelle_porte->nom = (char*)malloc(sizeof(char) * NOM_SORTIE_TAILLE_MAX);
	if (nouvelle_porte == NULL)
	{
		free(nouvelle_porte);
		printf("Espace memoire epuisee pour la fonction nouvelle_sortie!");
		system("pause");
		exit(EXIT_FAILURE);
	}
	sprintf(nouvelle_porte->nom, "P%d", id);//Assignation du nom de la nouvelle porte
	
	if (type == PORTE_NOT) //Initialisation du nombre d'entree dependamment le type de la porte
	{
		nouvelle_porte->nb_entrees = 1;
	}
	else
	{
		nouvelle_porte->nb_entrees = 2;
		nouvelle_porte->entrees[1] = t_pin_entree_init();
	}
	
	return nouvelle_porte;
}

void t_porte_destroy(t_porte* porte)
{	
	t_pin_sortie_destroy(porte->sortie);
	t_pin_entree_destroy(porte->entrees[0]);

	if (porte->type != PORTE_NOT)
	{
		t_pin_entree_destroy(porte->entrees[1]); //Si la porte est compose de plus d'une entree
	}
	free(porte->nom);
	free(porte);	//Destruction de la memoire
}

void t_porte_calculer_sorties(t_porte* porte)
{
	if (porte->type == PORTE_NOT) //Calcule de sortie pour une porte NON
	{
		if (porte->entrees[0] == 0)
		{
			porte->sortie->valeur = 1;
		}
		else
		{
			porte->sortie->valeur = 0;
		}
	}

	if (porte->type == PORTE_ET) //Calcule de sortie pour une porte ET
	{
		if (porte->entrees[0] == 1 && porte->entrees[1] == 1)
		{
			porte->sortie->valeur = 1;
		}
		else
		{
			porte->sortie->valeur = 0;
		}
	}

	if (porte->type == PORTE_OU) //Calcule de sortie pour une porte OU
	{
		if (porte->entrees[0] == 0 && porte->entrees[1] == 0)
		{
			porte->sortie->valeur = 0;
		}
		else
		{
			porte->sortie->valeur = 1;
		}
	}

	if (porte->type == PORTE_XOR) //Calcule de sortie pour une porte XOR
	{
		if (porte->entrees[0] != porte->entrees[1])
		{
			porte->sortie->valeur = 1;
		}
		else
		{
			porte->sortie->valeur = 0;
		}
	}
}

int t_porte_relier(t_porte* dest, int num_entree, const t_pin_sortie* source)
{
	if (dest->type == PORTE_NOT && num_entree >= 2) //Verification que nous avons un choix possible
	{
		return 0;
	}

	t_pin_entree_relier(dest->entrees[num_entree], source); //Liaision de l'entree et sortie
	return 1;
}

int t_porte_est_reliee(t_porte* porte)
{
	if (porte->type == PORTE_NOT) //Verification que chaque pin sont utilise pour une porte NON
	{
		if (t_pin_entree_est_reliee(porte->entrees[0]) == 1 && t_pin_sortie_est_reliee(porte->sortie) == 1) 
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	else //Verification que chaque pin sont utilise pour une porte OU, ET ou XOR
	{
		if (t_pin_entree_est_reliee(porte->entrees[0]) == 1 && t_pin_entree_est_reliee(porte->entrees[1]) == 1 && t_pin_sortie_est_reliee(porte->sortie) == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

void t_porte_reset(t_porte* porte)
{
	if (porte->type) //Reset les valeurs pour toute les portes
	{
		t_pin_entree_reset(porte->entrees[0]);
		t_pin_sortie_reset(porte->sortie);
	}
	if (porte->type != PORTE_NOT) //Si ce n'est pas une porte NON, on reset aussi la deuxieme entree
	{
		t_pin_entree_reset(porte->entrees[1]);
	}
}

int t_porte_propager_signal(t_porte* porte)
{
	if (t_pin_entree_est_reliee(porte->entrees[0]) == 1) //Verification que la pin 1 est utiliser
	{
		if (porte->type != PORTE_NOT) //Seulement lorsque nous avons une porte autre que la NON
		{
			if (t_pin_entree_est_reliee(porte->entrees[1]) == 1) //Verification que la pin 2 est utiliser
			{
				t_porte_calculer_sorties(porte);
				t_pin_sortie_propager_signal(porte->sortie); //Propagation de la valeurs a notre sortie
			}
		}
		else
		{
			t_porte_calculer_sorties(porte);
			t_pin_sortie_propager_signal(porte->sortie); //Si nous avons une porte NON
		}
	}
}

t_pin_sortie* t_porte_get_pin_sortie(t_porte* porte)
{
	return porte->sortie;
}

