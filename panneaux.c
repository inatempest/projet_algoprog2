/*
=================================================================================================
Name : panneaux.c
Author : Viviana Hirsch & Mathilde Pierrat
Description : Fonctions relatives aux panneaux solaires
=================================================================================================
*/

#include "panneaux.h"

void lireFicMonth(Month tab_month[],const char* nomFic)
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
			tab_month[i]=*month;
		}
		fclose(fichier);
	}
	else
		printf("Désolé, ce fichier n'existe pas :(\n");
}

void lireFicDay(Day tab_day[],const char* nomFic)
{
	FILE *fichier;
	fichier=fopen(nomFic,"r");
	Day *day;
	char heure[10];
	
	if(fichier!=NULL)
	{
		char ligne[LG_LIGNE];
		for(int i=0;i<7;i++) //on enlève les 7 premières lignes
			fgets(ligne,LG_LIGNE,fichier);
		
		for(int i=0;i<NB_HOUR;i++)
		{
			fgets(ligne,LG_LIGNE,fichier);
			day=(Day*)malloc(sizeof(Day));
			fscanf(fichier,"%s %lf %lf %lf",heure,&day->global_ir,&day->direct_ir,&day->diffuse_ir);
			day->hour=i;
			tab_day[i]=*day;
		}
		fclose(fichier);
	}
	else
		printf("Désolé, ce fichier n'existe pas :(\n");
}
	
void enregistrerRSI(double *nbPanneaux,int *surface_toit,Liste *maison,int *surface_maison,Month tab_month[],Day tab_day[],const char* nomFic)
{
	FILE *fichier;
	fichier=fopen(nomFic,"w");
	
	fprintf(fichier,"Votre consommation actuelle d'électricité : \n");
	
	double kWh_JOUR=consoWhParTemps(maison,surface_maison,JOUR)/1000;
	double prix_JOUR=consoWhEURO(maison,surface_maison,JOUR);	
	fprintf(fichier,"Consommation par jour : \n");
	fprintf(fichier,"En euro : %.0lf | En kWh : %.0lf \n",prix_JOUR,kWh_JOUR);

	double kWh_SEMAINE=consoWhParTemps(maison,surface_maison,SEMAINE)/1000;
	double prix_SEMAINE=consoWhEURO(maison,surface_maison,SEMAINE);	
	fprintf(fichier,"Consommation par semaine : \n");
	fprintf(fichier,"En euro : %.0lf | En kWh : %.0lf \n",prix_SEMAINE,kWh_SEMAINE);
	
	double kWh_MOIS=consoWhParTemps(maison,surface_maison,MOIS)/1000;
	double prix_MOIS=consoWhEURO(maison,surface_maison,MOIS);	
	fprintf(fichier,"Consommation par mois : \n");
	fprintf(fichier,"En euro : %.0lf | En kWh : %.0lf \n",prix_MOIS,kWh_MOIS);
	
	double kWh_AN=consoWhParTemps(maison,surface_maison,ANNEE)/1000;
	double prix_AN=consoWhEURO(maison,surface_maison,ANNEE);	
	fprintf(fichier,"Consommation par an : \n");
	fprintf(fichier,"En euro : %.0lf | En kWh : %.0lf \n",prix_AN,kWh_AN);
	
	double max=nbPanneauxDisp(surface_toit);
	int cout_max=coutInstallation(surface_toit,&max);
	fprintf(fichier,"Nombre total de panneaux solaires qu'il est possible d'installer : %.0lf \n",max);
	fprintf(fichier,"Coût d'une telle installation : %d \n",cout_max);
	
	double optimisation=nbPanneauxNecessaires(tab_month,maison,surface_maison,surface_toit);
	if(optimisation==max)
	{
		int cout_optimise=coutInstallation(surface_toit,&optimisation);
		fprintf(fichier,"Nombre de panneaux solaires suffisant : %.0lf \n",optimisation);
		fprintf(fichier,"Coût d'une telle installation : %d \n",cout_optimise);
	}
	else
		fprintf(fichier,"Pas suffisamment de surface disponible pour subvenir à la consommation");
	
	int an_RSI=retourSurInvestissement(nbPanneaux,tab_month,surface_toit,maison,surface_maison);
	fprintf(fichier,"Avec le nombre de panneaux choisi, soit %.0lf , la durée de retour sur investissement est estimée à %d ans.\n",*nbPanneaux,an_RSI);
	
	fclose(fichier);
}
	

double calculWH(Liste *maison,int *surface_maison,int duree)
{
	double total=0;
	Objet *obj=maison->tete;
	while(obj!=NULL)
	{
		if(strcmp(obj->nom,"Chauffage (m²)")==0 || strcmp(obj->nom,"Ampoule LED")==0)
			obj->conso_WH=(obj->consommation)*(obj->puissance)*(*surface_maison);
		else
			obj->conso_WH=(obj->consommation)*(obj->puissance);
		total+=obj->conso_WH*duree;
		obj=obj->suiv;
	}
	return total;
	
}

double nbPanneauxDisp(int *surface_toit)
{
	return(floor((*surface_toit)/P));
}

double nbPanneauxNecessaires(Month tab_month[],Liste *maison, int *surface_maison, int *surface_toit)
{
	double moyenne_mois=moyenneMois(tab_month)/12;
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

int coutInstallation(int *surface_toit,double *nbPanneaux)
{
	double cout_total=COUT*(*nbPanneaux)*PANNEAU_WC;
	printf("\nL'installation coûtera %.0f €\n",cout_total);
	return cout_total;
}

int optimisationSemaine(Liste *maison,Day tab_day[], double *nb_panneaux)
{
	int nb_elements=maison->nb_elements;
	int capacity=floor(moyenneJour(tab_day)*7*(*nb_panneaux)*P); //production des panneaux sur une semaine
	int** V=(int**)malloc(sizeof(int*)*(capacity+1)); //tableau de capacity+1 colonnes
	int** app_garde_bool=(int**)malloc(sizeof(int*)*(capacity+1)); //case vaut 1 si l'objet est gardé
	Objet** app_garde=(Objet**)malloc(sizeof(Objet*)*(capacity+1));
	Objet *objet;
	int conso;
	
	//initialisation des tableaux
	for(int b=0;b<=capacity;b++)
	{
		V[b]=(int*)malloc(sizeof(int)*(nb_elements+1)); //tableau de nb_elements+1 lignes
		app_garde_bool[b]=(int*)malloc(sizeof(int)*(nb_elements+1));
		app_garde[b]=(Objet*)malloc(sizeof(Objet)*(nb_elements+1));
		V[b][0]=0; //première ligne remplie de 0
		
		for(int t=0;t<=nb_elements;t++)
			app_garde_bool[b][t]=0; 
	}
	

	for(int b=0;b<=capacity;b++)
	{
	objet=maison->tete;
		for(int t=1;t<=nb_elements;t++)
		{
		conso=(int)floor(objet->conso_WH)*SEMAINE; //consommation de l'objet sur une semaine
			if(conso<=b)
			{
				V[b][t]=max(V[b][t-1],V[b-conso][t-1]+objet->priorite);
				
				if(V[b-conso][t]+(objet->priorite)>V[b][t-1])
				{
					app_garde_bool[b][t]=1;
					app_garde[b][t]=*objet; //affiche l'objet gardé
				}
			}
			else
				V[b][t]=V[b][t-1];
			objet=objet->suiv;

		}
	}
			
	printf("Sur une semaine, vous pourriez alimenter grâce à vos panneaux solaires :\n");
	int k=capacity;
	for(int t=nb_elements;t>=0;t--)
	{
		if(app_garde_bool[k][t]==1)
		{
			printf("%s\n",(app_garde[k][t]).nom);
			conso=(int)floor((app_garde[k][t]).conso_WH);
			k=k-conso;
		}
	}
	return V[capacity][nb_elements];
}

int retourSurInvestissement(double *nbPanneaux,Month tab_month[],int *surface_toit,Liste *maison,int *surface_maison)
{
	int cout_total=coutInstallation(surface_toit,nbPanneaux);
	double besoin_an=calculWH(maison,surface_maison,ANNEE);
	double economie=0;
	double prod_an=moyenneMois(tab_month)*(*nbPanneaux)*P; //production annuelle des panneaux solaires en Wh sur un an 
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


double moyenneMois(Month tab_month[])
{
	double moyenne_ir=0;
	for(int i=0;i<NB_MONTH;i++)
		moyenne_ir+=tab_month[i].irradiation; 
	moyenne_ir=moyenne_ir/NB_MONTH*1000; //moyenne de l'irradiation sur un an en Wh/m2
	return moyenne_ir;
}

double moyenneJour(Day tab_day[])
{
	double moyenne=0;
	for(int i=0;i<NB_HOUR;i++)
		moyenne+=tab_day[i].global_ir;
	moyenne=(moyenne/NB_HOUR); //moyenne de l'irradiation sur un jour en Wh/m2
	return moyenne;
}
		
void saisirSurfaces(int *surface_maison,int *surface_toit)
{
	printf("Veuillez saisir une nouvelle surface pour votre maison : \n");
	scanf("%d",surface_maison);
	printf("Veuillez saisir une nouvelle surface pour votre toit : \n");
	scanf("%d",surface_toit);
}

int max(int a,int b)
{
	if(a>=b)
		return a;
	return b;
}
	

/**************************************************************


	Menus et sous-menus
	
	
***************************************************************/

void menu(Liste tableau[],int *surface_maison,int *surface_toit,Liste *maison,Month tab_month[],Day tab_day[])
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
				menuPanneau(surface_maison,surface_toit,maison,tab_month,tab_day);
				break;
			case 3:
				quitter=true;
				break;
		}
	}
}

void menuPanneau(int *surface_maison,int *surface_toit,Liste *maison,Month tab_month[],Day tab_day[])
{
	bool quitter=false;
	int choix;
	double nbPanneaux=nbPanneauxDisp(surface_toit); //par défaut on prend autant de panneaux que possible
	calculWH(maison,surface_maison,0); //permet de calculer la conso en Wh de tous les appareils
	
	while(!quitter)
	{
		printf("\n");
		printf("0 Consommation de la maison en kWh et en €\n");
		printf("1 Nb de panneaux solaires necessaires\n"); //si on prenait tous les appareils demandés
		printf("2 Optimisation appareils/panneaux solaires sur une semaine\n"); //donne les appareils tels que les panneaux solaires subviennent à leurs besoins, en fonction des priorités de l'utilisateur
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
				nbPanneaux=nbPanneauxNecessaires(tab_month,maison,surface_maison,surface_toit);
				break;
			case 2:
				optimisationSemaine(maison,tab_day,&nbPanneaux);
				break;
			case 3:
				coutInstallation(surface_toit,&nbPanneaux);
				break;
			case 4:
				retourSurInvestissement(&nbPanneaux,tab_month,surface_toit,maison,surface_maison);
				break;
			case 5:
				enregistrerRSI(&nbPanneaux,surface_toit,maison,surface_maison,tab_month,tab_day,"RSI.txt");
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
	
