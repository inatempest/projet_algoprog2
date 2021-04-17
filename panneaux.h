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


void lireFicIr(Month tab[],const char* nomFic);
void lireFicDay(Day tab[],const char* nomFic);

void afficherTableau(Month tab[]); //pour les tests

double calculWH(Liste *maison,int *surface_maison,int duree);
double nbPanneauxDisp(int *surface_toit);
int coutInstallation(int *surface_toit, double *nbPanneaux);
int choixDuree();
double consoWhParTemps(Liste *maison,int *surface_maison,int periode);
double consoWhEURO(Liste *maison,int *surface_maison, int periode);
double saisirNbPanneaux(int *surface_toit);
int retourSurInvestissement(double *nbPanneaux,Month tab[],int *surface_toit,Liste *maison,int *surface_maison);
void enregistrerRSI(double *nbPanneaux,int *surface_toit,Liste *maison,int *surface_maison,Month tab[],Day tab_day[],const char* nomFic);

double moyenneMois(Month tableau[]);
double moyenneJour(Day tab[]);

double nbPanneauxNecessaires(Month tab[],Liste *maison, int *surface_maison, int *surface_toit);
void saisirSurfaces(int *surface_maison,int *surface_toit);

int max(int a,int b);
int optimisationSemaine(Liste *maison,Day tab[], double *nb_panneaux);

void menu(Liste *liste,int *surface_maison,int *surface_toit,Liste *maison,Month tab[],Day tab_day[]);
void menuPanneau(int *surface_maison,int *surface_toit,Liste *maison,Month tab[],Day tab_day[]);
void menuConso(Liste *maison, int *surface_maison);

#endif

