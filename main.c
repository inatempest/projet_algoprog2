/*
=================================================================================================
Name : main.c
Author : Viviana Hirsch
Description : Main du projet
=================================================================================================
*/


#include "electromenager.h"
#include "panneaux.h"

int main()
{
	const char* NOM_FIC="appareils_electromenagers.csv";

	//initialisation des catégories
	Liste bureauL;
	initListe(&bureauL,Bureau);
	Liste cuisineL;
	initListe(&cuisineL,Cuisine);
	Liste entretienL;
	initListe(&entretienL,Entretien);
	Liste autreL;
	initListe(&autreL,Autre);
	
	//initialisation de l'inventaire
	Liste inventaire[4]={bureauL,cuisineL,entretienL,autreL};//tableau de listes
	lireFicElec(inventaire,NOM_FIC);
	
	//initialisation de la liste maison
	Liste maison;
	initListe(&maison,none);
	
	//initialisation des surfaces
	int surface_maison;
	int surface_toit;
	printf("Donner surface maison : ");
	scanf("%d",&surface_maison);
	printf("\nDonner surface toit : ");
	scanf("%d",&surface_toit);
	
	
	//lecture des fichiers Monthly et Daily
	const char* NOM_FIC_MONTH="Monthlydata_48.582_7.769_SA_2005_2016.csv";
	Month data_month[NB_MONTH];
	lireFicMonth(data_month,NOM_FIC_MONTH);

	const char* NOM_FIC_DAY="Dailydata_48.582_7.769_SA_04_35deg_0deg.csv";
	Day data_day[NB_HOUR];
	lireFicDay(data_day,NOM_FIC_DAY);
	
	//appel au menu
	menu(inventaire,&surface_maison,&surface_toit,&maison,data_month,data_day);
	return 0;
}
