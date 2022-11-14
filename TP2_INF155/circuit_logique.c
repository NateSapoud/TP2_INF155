/*
SIMULATEUR DE CIRCUIT LOGIQUE

Programme qui illustre l'utilisation de la librairie de circuits logique.

Un circuit est construit de fa�on programmatique (les portes, les entr�es, les sorties sont cr��es et
ajout�es au circuit, puis reli�es entre-elles. Une fois construit, on v�rifie si il est valide. Si il est
valide, un sigal est appliqu� aux entr�es et propag� � travers les circuit. Nous terminons par afficher 
le signal en sortie. 
*/


#include <stdlib.h>
#include <stdio.h>
#include "t_circuit.h"
#include "t_porte.h"
#include "t_entree.h"
#include "t_sortie.h"


int main(void)
{
	//d�claration de variables
	int signal[3];
	t_circuit* circuit;
	t_porte* porte_ou;
	t_porte* porte_et;
	t_porte* porte_not;
	t_porte* porte_xor;
	t_entree* entree0;
	t_entree* entree1;
	t_entree* entree2;
	t_sortie* sortie0;

	//Cr�ation du circuit
	circuit = t_circuit_init();

	//Ajout des portes
	porte_ou = t_circuit_ajouter_porte(circuit, PORTE_OU);
	porte_et = t_circuit_ajouter_porte(circuit, PORTE_ET);
	porte_not = t_circuit_ajouter_porte(circuit, PORTE_NOT);
	porte_xor = t_circuit_ajouter_porte(circuit, PORTE_XOR);

	//Ajout des entr�es
	entree0 = t_circuit_ajouter_entree(circuit);
	entree1 = t_circuit_ajouter_entree(circuit);
	entree2 = t_circuit_ajouter_entree(circuit);

	//Ajout des sorties
	sortie0 = t_circuit_ajouter_sortie(circuit);

	//Ajout de liens
	t_porte_relier(porte_ou, 0, t_entree_get_pin(entree0));
	t_porte_relier(porte_ou, 1, t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 0, t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 1, t_entree_get_pin(entree2));
	t_porte_relier(porte_not, 0, t_porte_get_pin_sortie(porte_ou));
	t_porte_relier(porte_xor, 0, t_porte_get_pin_sortie(porte_not));
	t_porte_relier(porte_xor, 1, t_porte_get_pin_sortie(porte_et));
	t_sortie_relier(sortie0, t_porte_get_pin_sortie(porte_xor));

	//V�rification de la validit� du circuit
	if (t_circuit_est_valide(circuit)) {
		printf("Circuit valide!\n");

		signal[0] = 1;
		signal[1] = 1;
		signal[2] = 1;

		t_circuit_reset(circuit);
		t_circuit_appliquer_signal(circuit, signal, 3);

		if (t_circuit_propager_signal(circuit)) {
			printf("Signal propage avec succes.\n");
			printf("Sortie 0: %d\n", t_sortie_get_valeur(sortie0));
		}
		else {
			printf("Erreur lors de la propagation du signal.\n");
		}
	}
	else {
		printf("Circuit invalide!\n");
	}

	

	t_circuit_destroy(circuit);

	system("pause");
	return 0;
}
