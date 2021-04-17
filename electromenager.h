/*
=================================================================================================
Name : electromenager.h
Author : Viviana Hirsch
Description : Structures et prototypes des fonctions relatives aux appareils électroménagers
=================================================================================================
*/

#ifndef ELECTROMENAGER_H
#define ELECTROMENAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define LG_MAX 30
#define LG_LIGNE 200

#define nb_cat 4

typedef enum Categorie Categorie;
enum Categorie
{
	Bureau,Cuisine,Entretien,Autre,none
};

typedef struct objet_
{
	char nom[LG_MAX];
	float consommation;
	int puissance;
	int priorite;
	int categorie;
	float conso_WH;
	struct objet_ *suiv;
	}Objet;
	
typedef struct
{
	Objet *tete;
	int categorie;
	int nb_elements;
	}Liste;



void initListe(Liste *liste,int cat);
void lireFicElec(Liste tableau[],const char* nomFic);
void afficherListeCat(Liste tableau[],int cat);
void afficherObjet(Objet *objet);

void ajouterObjMaison(Liste *maison,Objet *objet);
void parcoursCat(Liste tableau[],Liste *maison,int cat);
void rechercheNom(Liste tableau[],Liste *maison);
void ajouterObjMan(Liste *maison);
void afficherListe(Liste *liste);
void supprimerObj(Liste *maison);
void enregistrerListe(Liste *liste,const char* nomFic);
void lireFicMaison(Liste *maison,const char* nomFic);


void equiperMaison(Liste tableau[],Liste *maison);
void rechercheCat(Liste tableau[],Liste *maison);
#endif
