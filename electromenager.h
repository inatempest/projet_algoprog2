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
#include <ctype.h> //pour éviter la casse lors de la recherche par nom


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


/*********************************************************************

Prototypes des fonctions du menu Equiper sa maison

**********************************************************************/


void initListe(Liste *liste,int cat);

//spécifique à l'inventaire
void lireFicElec(Liste tableau[],const char* nomFic);
void afficherListeCat(Liste tableau[],int cat); //permet de lire une catégorie

//spécifique à la liste maison
void afficherListe(Liste *liste); 
void enregistrerListe(Liste *liste,const char* nomFic);
void lireFicMaison(Liste *maison,const char* nomFic);

//fonctions utilitaires
void afficherObjet(Objet *objet);
void parcoursCat(Liste tableau[],Liste *maison,int cat);
void rechercheNom(Liste tableau[],Liste *maison);
void ajouterObjMan(Liste *maison);
void ajouterObjMaison(Liste *maison,Objet *objet);
void supprimerObj(Liste *maison);


/*********************************************************************

Prototypes des menus et sous-menus

**********************************************************************/
void equiperMaison(Liste tableau[],Liste *maison);
void rechercheCat(Liste tableau[],Liste *maison);
#endif
