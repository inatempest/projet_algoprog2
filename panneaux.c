/*
=================================================================================================
Name : panneaux.c
Author : Viviana Hirsch
Description : Fonctions relatives aux panneaux solaires
=================================================================================================
*/

#include "panneaux.h"

double calculWH(Liste *maison,int *surface_maison,int duree)
{
	double total=0;
	Objet *obj=maison->tete;
	while(obj!=NULL)
	{
		if(strcmp(obj->nom,"Chauffage (m²)")==0 || strcmp(obj->nom,"Ampoule LED")==0)
			obj->conso_WH=(obj->consommation)*(obj->puissance)*(*surface_maison)*duree;
		else
			obj->conso_WH=(obj->consommation)*(obj->puissance)*duree;
		total+=obj->conso_WH;
		obj=obj->suiv;
	}
	return total;
	
}

double nbPanneauxDisp(int *surface_toit)
{
	return(floor((*surface_toit)/P));
}

int coutInstallation(int *surface_toit,double *nbPanneaux)
{
	double cout_total=COUT*(*nbPanneaux)*PANNEAU_WC;
	printf("\nL'installation coûtera %.0f €\n",cout_total);
	return cout_total;
}

int choixDuree()
{
	printf("\nChoix de la durée :\n");
	printf("0 Par jour\n");
	printf("1 Par semaine\n");
	printf("2 Par mois\n");
	printf("3 Par an\n");
	int choix;
	printf("Choix : ");
	scanf("%d",&choix);
	int duree;
	switch(choix)
	{
		case 0:
			duree=JOUR;
			break;
		case 1:
			duree=SEMAINE;
			break;
		case 2:
			duree=MOIS;
			break;
		case 3:
			duree=ANNEE;
			break;
	}
	return duree;
}

double consoWhParTemps(Liste *maison,int *surface_maison,int periode)
{
	double total_Wh=calculWH(maison,surface_maison,periode);
	return total_Wh;
}

double consoWhEURO(Liste *maison,int *surface_maison, int periode)
{
	double total_Wh=calculWH(maison,surface_maison,periode);
	double kWh=total_Wh/1000;
	double prix_total=PRIX_MOYEN*kWh;
	return prix_total;
}

void lireFicIr(Month tableau[],const char* nomFic)
{
	FILE *fichier;
	fichier=fopen(nomFic,"r");
	Month *month;
		
	if(fichier!=NULL)
	{	
		char ligne[LG_LIGNE];
		for(int i=0;i<5;i++) //on enlève les 5 premières lignes
			fgets(ligne,LG_LIGNE,fichier);
	
		for(int i=0;i<NB_MONTH;i++)
		{
			fgets(ligne,LG_LIGNE,fichier);
			month=(Month*)malloc(sizeof(Month));
			fscanf(fichier,"%d %s %lf",&month->annee,month->mois,&month->irradiation);
			tableau[i]=*month;
		}
		fclose(fichier);
	}
	else
		printf("Désolé, ce fichier n'existe pas :(\n");
}

void afficherTableau(Month tableau[])
{
	for(int i=0;i<NB_MONTH;i++)
	{
		printf("%d %s %.1lf\n",tableau[i].annee,tableau[i].mois,tableau[i].irradiation);
	}
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
		printf("0 Consommation de la maison en kWh et en €\n");
		printf("1 Nb de panneaux solaires necessaires\n"); //si on prenait tous les appareils demandés
		printf("2 Optimisation appareils/panneaux solaires sur un mois\n"); //donne les appareils tels que les panneaux solaires subviennent à leurs besoins, en fonction des priorités de l'utilisateur
		printf("3 Cout installation panneaux solaires\n");
		printf("4 Durée associee au retour sur investissement\n");
		printf("5 Enregistrer indicateurs RSI\n");
		printf("6 Entrer de nouvelles valeurs pour les surfaces\n");
		printf("7 Quitter\n");
		printf("Choix : ");
		scanf("%d",&choix);
		
		switch(choix)
		{
			case 0:
				menuConso(maison,surface_maison);
				break;
			case 2:
				break;
			case 3:
				//coutInstallation(surface_toit);
				break;
			case 7:
				quitter=true;
				break;
		}
	}
}

void menuConso(Liste *maison, int *surface_maison)
{
	int periode=choixDuree();
	double kWh=consoWhParTemps(maison,surface_maison,periode)/1000;
	double prix_total=consoWhEURO(maison,surface_maison,periode);
	
	printf("\n");
	switch(periode)
	{
		case JOUR:
			printf("La consommation est de %.0f kWh par jour\n",kWh);
			printf("Vous payez actuellement %.0f € par jour\n",prix_total);
			break;
		case SEMAINE:
			printf("La consommation est de %.0f kWh par semaine\n",kWh);
			printf("Vous payez actuellement %.0f € par semaine\n",prix_total);
			break;
		case MOIS:
			printf("La consommation est de %.0f kWh par mois\n",kWh);
			printf("Vous payez actuellement %.0f € par mois\n",prix_total);
			break;
		case ANNEE:
			printf("La consommation est de %.0f kWh par an\n",kWh);
			printf("Vous payez actuellement %.0f € par an\n",prix_total);
			break;
	}
}	
	
