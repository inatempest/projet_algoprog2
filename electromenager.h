/*
=================================================================================================
Name : electromenager.h
Author : Viviana Hirsch
Version : 0
Description : Structures et prototypes des fonctions relatives aux appareils électroménagers
=================================================================================================
*/

#ifndef ELECTROMENAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LG_MAX 30
#define LG_LIGNE 80

#define nb_cat 4

typedef enum Categorie Categorie;
enum Categorie
{
	Bureau,Cuisine,Entretien,Autre,none
};

typedef struct objet_
{
	char nom[LG_MAX];
	int consommation;
	int puissance;
	int priorite;
	struct objet_ *suiv;
	}Objet;
	
typedef struct
{
	Objet *tete;
	int categorie;
	}Liste;


void initListe(Liste *liste,int cat);
void lireFicElec(Liste tableau[],const char* nomFic);
void afficherListeCat(Liste tableau[],int cat);
void afficherObjet(Objet *objet);

void rechercheCat(Liste *liste,Liste *maison);

void menu(Liste *liste,int *surface_maison,int *surface_toit,Liste *maison);
void equiperMaison(Liste *liste,Liste *maison);
#endif
