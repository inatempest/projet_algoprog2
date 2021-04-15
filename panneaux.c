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

void lireFicIr(Month tab[],const char* nomFic)
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
			tab[i]=*month;
		}
		fclose(fichier);
	}
	else
		printf("Désolé, ce fichier n'existe pas :(\n");
}

void afficherTableau(Month tab[])
{
	for(int i=0;i<NB_MONTH;i++)
	{
		printf("%d %s %.1lf\n",tab[i].annee,tab[i].mois,tab[i].irradiation);
	}
}

double saisirNbPanneaux(int *surface_toit)
{
	double max=nbPanneauxDisp(surface_toit);
	double choix_nb;
	printf("Donner le nombre de panneaux voulu :\n");
	scanf("%le",&choix_nb);
	if(choix_nb>max)
	{
		printf("Impossible de mettre autant de panneaux.\n");
		return max;
	}
	else
		return choix_nb;
}

int retourSurInvestissement(double *nbPanneaux,Month tab[],int *surface_toit,Liste *maison,int *surface_maison)
{
	int cout_total=coutInstallation(surface_toit,nbPanneaux);
	double besoin_an=calculWH(maison,surface_maison,ANNEE);
	double economie=0;
	double prod_an=moyenneMois(tab)*12*(*nbPanneaux)*P; //production annuelle des panneaux solaires en Wh sur un an 
	int an=0;
	double difference;
	
	while(economie<cout_total)
	{
		economie+=consoWhEURO(maison,surface_maison,ANNEE); //économie du prix qu'aurait coûté l'électricité
		if(prod_an<besoin_an)
		{
			difference=besoin_an-prod_an; //Wh nécessaire pour pallier au manque des panneaux
			economie-=difference/1000*PRIX_MOYEN; //différence en kWh multiplié par le prix moyen d'1 kWh
		}
		an++;
		printf("Argent récupéré au bout de %d ans : %.0lf €\n",an,economie);
	}
	printf("Les panneaux solaires seront rentables dans %d ans!\n",an);
	return an;
}

double moyenneMois(Month tab[])
{
	double moyenne_ir=0;
	for(int i=0;i<NB_MONTH;i++)
		moyenne_ir+=tab[i].irradiation; 
	moyenne_ir=moyenne_ir/NB_MONTH*1000; //moyenne de l'irradiation sur un mois en Wh
	return moyenne_ir;
}

double nbPanneauxNecessaires(Month tab[],Liste *maison, int *surface_maison, int *surface_toit)
{
	double moyenne_mois=moyenneMois(tab);
	double besoin_mois=calculWH(maison,surface_maison,MOIS);
	double surface_nec=besoin_mois/moyenne_mois;
	double max=nbPanneauxDisp(surface_toit);
	double nb_panneaux;
	nb_panneaux=floor(surface_nec/P);
	printf("Vous avez besoin de %.0lf panneaux pour subvenir à votre consommation.\n",nb_panneaux);
	if(nb_panneaux>max)
	{
		printf("Pas assez de surface disponible pour mettre le nb de panneaux nécessaires.\n");
		printf("Vous pouvez mettre au maximum %.0lf panneaux.\n",max);
		return max;
	}
	else
		return nb_panneaux;
}
		
void saisirSurfaces(int *surface_maison,int *surface_toit)
{
	printf("Veuillez saisir une nouvelle surface pour votre maison : \n");
	scanf("%d",surface_maison);
	printf("Veuillez saisir une nouvelle surface pour votre toit : \n");
	scanf("%d",surface_toit);
}
	

/**************************************************************


	Menus et sous-menus
	
	
***************************************************************/

void menu(Liste tableau[],int *surface_maison,int *surface_toit,Liste *maison,Month tab[])
{
	bool quitter=false;
	int choix;
	
	while(!quitter)
	{
		printf("\n");
		printf("0 Voir l'inventaire disponible\n");
		printf("1 Equiper sa maison\n"); //donner des ordres de priorités aux appareils
		printf("2 Installer des panneaux photovoltaïques\n");
		printf("3 Quitter\n");
		printf("Choix : ");
		scanf("%d",&choix);
		
		switch(choix)
		{
			case 0:
				printf("\n******BUREAU******\n");
				afficherListeCat(tableau,Bureau);
				printf("\n******CUISINE******\n");
				afficherListeCat(tableau,Cuisine);
				printf("\n******ENTRETIEN******\n");
				afficherListeCat(tableau,Entretien);
				printf("\n******AUTRE******\n");
				afficherListeCat(tableau,Autre);
				break;
			case 1:
				equiperMaison(tableau,maison);
				break;
			case 2:
				menuPanneau(surface_maison,surface_toit,maison,tab);
				break;
			case 3:
				quitter=true;
				break;
		}
	}
}

void menuPanneau(int *surface_maison,int *surface_toit,Liste *maison,Month tab[])
{
	bool quitter=false;
	int choix;
	double nbPanneaux=nbPanneauxDisp(surface_toit); //par défaut on prend autant de panneaux que possible
	
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
		printf("7 Saisir le nb de panneaux solaires manuellement\n");
		printf("8 Quitter\n");
		printf("Choix : ");
		scanf("%d",&choix);
		
		switch(choix)
		{
			case 0:
				menuConso(maison,surface_maison);
				break;
			case 1:
				nbPanneaux=nbPanneauxNecessaires(tab,maison,surface_maison,surface_toit);
				break;
			case 2:
				break;
			case 3:
				coutInstallation(surface_toit,&nbPanneaux);
				break;
			case 4:
				retourSurInvestissement(&nbPanneaux,tab,surface_toit,maison,surface_maison);
				break;
			case 6:
				saisirSurfaces(surface_maison,surface_toit);
				break;
			case 7:
				nbPanneaux=saisirNbPanneaux(surface_toit);
				break;
			case 8:
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
	
