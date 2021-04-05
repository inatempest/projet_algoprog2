/*
=================================================================================================
Name : electromenager.c
Author : Viviana Hirsch
Version : 1
Description : Fonctions relatives aux appareils électroménagers
=================================================================================================
*/

#include "electromenager.h"


void initListe(Liste *liste,int cat)
{
	liste->tete=NULL;
	liste->categorie=cat;
}

void lireFicElec(Liste tableau[],const char* nomFic)
{
	FILE *fichier;
	fichier=fopen(nomFic,"r");
	//char categories[4][10]={"Bureau","Cuisine","Entretien","Autre"};
		
	if(fichier!=NULL)
	{	
		char ligne[LG_LIGNE];
		fgets(ligne,LG_LIGNE,fichier); //récupère les titres des colonnes
	

		Objet *obj;
		while(fgets(ligne,LG_LIGNE,fichier)!=NULL)
		{
			char *ptr_chaine=strtok(ligne,";"); //sépare la ligne en fonction des point-virgules
			obj=(Objet*)malloc(sizeof(Objet));
				
			//categorie de l'objet
			char categorie[10];
			sscanf(ptr_chaine,"%s",categorie);
			ptr_chaine=strtok(NULL,";");
			//nom de l'objet
			sscanf(ptr_chaine,"%s",obj->nom);
			ptr_chaine=strtok(NULL,";");
			//puissance de l'objet
			sscanf(ptr_chaine,"%d",&obj->puissance);
			ptr_chaine=strtok(NULL,";");
			//initialisation de la priorité
			obj->priorite=0;
			//initialisation de la consommation
			obj->consommation=0;
			
			//placement dans la bonne liste chaînée
			if (strcmp(categorie,"Bureau")==0)
			{
				obj->suiv=tableau[Bureau].tete;
				tableau[Bureau].tete=obj;
			}
			else if (strcmp(categorie,"Cuisine")==0)
			{
				obj->suiv=tableau[Cuisine].tete;
				tableau[Cuisine].tete=obj;
			}
			else if (strcmp(categorie,"Entretien")==0)
			{
				obj->suiv=tableau[Entretien].tete;
				tableau[Entretien].tete=obj;
			}
			else if (strcmp(categorie,"Autre")==0)
			{
				obj->suiv=tableau[Autre].tete;
				tableau[Autre].tete=obj;
			}
		}
		free(obj);
		fclose(fichier);
	}
	else
		printf("Erreur : fichier non trouve");
}
	

void afficherListeCat(Liste tableau[],int cat)
{
	Objet *obj=tableau[cat].tete;
	while(obj!=NULL)
	{
		afficherObjet(obj);
		obj=obj->suiv;
	}
}

void afficherObjet(Objet *objet)
{
	printf("Nom : %s \nPuissance (W) : %d \nPriorité : %d\nConsommation :%d\n\n",objet->nom,objet->puissance,objet->priorite,objet->consommation);
}




/**************************************************************
	Menus et sous-menus
***************************************************************/

void menu(Liste tableau[],int *surface_maison,int *surface_toit,Liste *maison)
{
	bool quitter=false;
	int choix;
	
	while(!quitter)
	{
		printf("\n");
		printf("0 Voir l'inventaire disponible\n");
		printf("1 Equiper sa maison\n"); //donner des ordres de priorités aux appareils
		printf("2 Nb de panneaux solaires necessaires\n"); //si on prenait tous les appareils demandés
		printf("3 Optimisation appareils/panneaux solaires\n"); //donne les appareils tels que les panneaux solaires subviennent à leurs besoins, en fonction des priorités de l'utilisateur
		printf("4 Cout installation panneaux solaires\n");
		printf("5 Durée associee au retour sur investissement\n");
		printf("6 Enregistrer indicateurs RSI\n");
		printf("7 Quitter\n");
		printf("Choix : ");
		scanf("%d",&choix);
		
		switch(choix)
		{
			case 0:
				afficherListeCat(tableau,Bureau);
				afficherListeCat(tableau,Cuisine);
				afficherListeCat(tableau,Entretien);
				afficherListeCat(tableau,Autre);
				break;
			case 1:
				equiperMaison(tableau,maison);
				break;
			case 7:
				quitter=true;
				break;
		}
	}
}
		
	
void equiperMaison(Liste *liste,Liste *maison)
{
	bool quitter=false;
	int choix;
	
	while(!quitter)
	{
		printf("\n");
		printf("0 Recherche par catégorie\n");
		printf("1 Recherche par nom\n");
		printf("2 Ajouter un appareil manuellement\n");
		printf("3 Afficher mes appareils\n");
		printf("4 Enregistrer ma liste\n");
		printf("5 Supprimer un appareil de la liste\n");
		printf("6 Quitter\n");
		printf("Choix :");
		scanf("%d",&choix);
		
		switch(choix)
		{
			case 0:
				//rechercheCat(liste,maison);
				break;
			case 1:
				//rechercheNom(liste,maison);
				break;
			case 2:
				//ajouterObj(maison);
				break;
			case 3:
				//afficherListe(maison);
				break;
			case 4:
				//enregistrerListe(maison,"MaMaison.csv");
				break;
			case 5:
				//supprimerObj(maison);
				break;
			case 6:
				quitter=true;
				break;
		}
	}
}

void rechercheCat(Liste *liste,Liste *maison)
{
	int choix;
	bool quitter=false;
	
	while(!quitter)
	{
		printf("Choisir la categorie\n");
		printf("0 Bureau\n");
		printf("1 Cuisine\n");
		printf("2 Entretien\n");
		printf("3 Autre\n");
		printf("4 Quitter\n");
		printf("Choix :\n");
		scanf("%d",&choix);
	
		switch(choix)
		{
			case 0:
				//parcoursCat(liste,maison,"Bureau");
				break;
			case 1:
				//parcoursCat(liste,maison,"Bureau");
				break;
			case 2:
				//parcoursCat(liste,maison,"Bureau");
				break;
			case 3:
				//parcoursCat(liste,maison,"Bureau");
				break;
			case 4:
				quitter=true;
				break;
		}
	}
}
	
				
	
	
