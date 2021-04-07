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

	Liste bureauL;
	initListe(&bureauL,Bureau);
	Liste cuisineL;
	initListe(&cuisineL,Cuisine);
	Liste entretienL;
	initListe(&entretienL,Entretien);
	Liste autreL;
	initListe(&autreL,Autre);
	Liste inventaire[4]={bureauL,cuisineL,entretienL,autreL};//tableau de listes


	lireFicElec(inventaire,NOM_FIC);
	
	Liste maison;
	initListe(&maison,none);
	
	int surface_maison;
	int surface_toit;
	printf("Donner surface maison : ");
	scanf("%d",&surface_maison);
	printf("\nDonner surface toit : ");
	scanf("%d",&surface_toit);
	
	menu(inventaire,&surface_maison,&surface_toit,&maison);
	return 0;
}
