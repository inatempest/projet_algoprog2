/*
=================================================================================================
Name : panneaux.h
Author : Viviana Hirsch
Description : Structures et prototypes des fonctions relatives aux panneaux solaires
=================================================================================================
*/
#ifndef PANNEAUX_H
#define PANNEAUX_H

#include "electromenager.h"

#define P 1,7 //surface (m²) d'un panneau
#define COUT 2500 //coût d'intallation de panneaux solaires par kWc

void menuPanneau(int *surface_maison,int *surface_toit,Liste *maison);

#endif

