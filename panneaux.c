/*
=================================================================================================
Name : panneaux.c
Author : Viviana Hirsch
Description : Fonctions relatives aux panneaux solaires
=================================================================================================
*/

#include "panneaux.h"

void calculWH(Liste *maison,int *surface_maison,int duree)
{
	Objet *obj=maison->tete;
	while(obj!=NULL)
	{
		if(strcmp(obj->nom,"Chauffage (m²)")==0 || strcmp(obj->nom,"Ampoule LED")==0)
			obj->conso_WH=(obj->consommation)*(obj->puissance)*(*surface_maison)*duree;
		else
			obj->conso_WH=(obj->consommation)*(obj->puissance)*duree;
		obj=obj->suiv;
	}
}

double nbPanneauxDisp(int *surface_toit)
{
	return(floor((*surface_toit)/P));
}

int coutInstallation(int *surface_toit)
{
	double nbPanneaux=nbPanneauxDisp(surface_toit);
	double cout_total=COUT*nbPanneaux*PANNEAU_WC;
	printf("\nL'installation coûtera %.0f €\n",cout_total);
	return cout_total;
}






/**************************************************************


	Menus et sous-menus
	
	
***************************************************************/

void menuPanneau(int *surface_maison,int *surface_toit,Liste *maison)
{
	bool quitter=false;
	int choix;
	
	while(!quitter)
	{
		printf("\n");
		printf("0 Nb de panneaux solaires necessaires\n"); //si on prenait tous les appareils demandés
		printf("1 Optimisation appareils/panneaux solaires sur un mois\n"); //donne les appareils tels que les panneaux solaires subviennent à leurs besoins, en fonction des priorités de l'utilisateur
		printf("2 Cout installation panneaux solaires\n");
		printf("3 Durée associee au retour sur investissement\n");
		printf("4 Enregistrer indicateurs RSI\n");
		printf("5 Entrer de nouvelles valeurs pour les surfaces\n");
		printf("6 Quitter\n");
		printf("Choix : ");
		scanf("%d",&choix);
		
		switch(choix)
		{
			case 0:
				//nbPanneauxNec(maison);
				break;
			case 1:
				break;
			case 2:
				coutInstallation(surface_toit);
				break;
			case 6:
				quitter=true;
				break;
		}
	}
}
