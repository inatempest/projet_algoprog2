/*
=================================================================================================
Name : panneaux.h
Author : Viviana Hirsch
Description : Structures et prototypes des fonctions relatives aux panneaux solaires
=================================================================================================
*/
#ifndef PANNEAUX_H
#define PANNEAUX_H

#include <math.h>
#include "electromenager.h"

#define P 1.7 //surface (m²) d'un panneau
#define COUT 2.5 //coût d'intallation de panneaux solaires par Wc
#define PANNEAU_WC 300 //nombre de Wc par panneau solaire
#define PRIX_MOYEN 0.1765 //prix moyen (2019) en France par kWh

#define NB_MONTH 144 //nb de mois dans un fichier monthly
#define NB_YEAR 12 //nb d'années dans un fichier monthly
#define NB_HOUR 24

typedef enum Temps Temps;
enum Temps
{
	JOUR=1,SEMAINE=7,MOIS=30,ANNEE=365
};

typedef struct _month
{
	int annee;
	char mois[LG_MAX];
	double irradiation;
}Month;

typedef struct _day
{
	int hour;
	double global_ir;
	double direct_ir;
	double diffuse_ir;
}Day;

/********************************************************************

Prototypes des fonctions du menu Panneaux photovoltaïques

*********************************************************************/


void lireFicMonth(Month tab_month[],const char* nomFic);
void lireFicDay(Day tab_day[],const char* nomFic);
void enregistrerRSI(double *nbPanneaux,int *surface_toit,Liste *maison,int *surface_maison,Month tab_month[],Day tab_day[],const char* nomFic);

double calculWH(Liste *maison,int *surface_maison,int duree); //met à jour la conso en Wh de chaque objet et renvoie le total de la consommation en fonction de l'entier duree

double nbPanneauxDisp(int *surface_toit); //nb panneaux max
double nbPanneauxNecessaires(Month tab_month[],Liste *maison, int *surface_maison, int *surface_toit); //nb panneaux nécessaires
double saisirNbPanneaux(int *surface_toit);

int coutInstallation(int *surface_toit, double *nbPanneaux);
int optimisationSemaine(Liste *maison,Day tab_day[], double *nb_panneaux);
int retourSurInvestissement(double *nbPanneaux,Month tab_month[],int *surface_toit,Liste *maison,int *surface_maison); //renvoie nb d'années avant amortissement

double consoWhParTemps(Liste *maison,int *surface_maison,int periode); //renvoie la conso en kWh sur une période
double consoWhEURO(Liste *maison,int *surface_maison, int periode); //renvoie la conso en € sur une période

double moyenneMois(Month tab_month[]); //renvoie la moyenne en Wh/m2 sur un mois
double moyenneJour(Day tab_day[]); //renvoie la moyenne en Wh/m2 sur un jour

void saisirSurfaces(int *surface_maison,int *surface_toit);
int max(int a,int b);


/*********************************************************************

Prototypes des menus et sous-menus

**********************************************************************/
void menu(Liste *liste,int *surface_maison,int *surface_toit,Liste *maison,Month tab_month[],Day tab_day[]);
void menuPanneau(int *surface_maison,int *surface_toit,Liste *maison,Month tab_month[],Day tab_day[]);
void menuConso(Liste *maison, int *surface_maison);
int choixDuree();

#endif

