/*
=================================================================================================
Name : electromenager.c
Author : Viviana Hirsch
Description : Fonctions relatives aux appareils électroménagers
=================================================================================================
*/

#include "electromenager.h"
#include "panneaux.h"


void initListe(Liste *liste,int cat)
{
	liste->tete=NULL;
	liste->categorie=cat;
}

void lireFicElec(Liste tableau[],const char* nomFic)
{
	FILE *fichier;
	fichier=fopen(nomFic,"r");
		
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
			sscanf(ptr_chaine,"%[^\t\n]",obj->nom); //force sscanf à ne s'arrêter qu'à une tab ou retour à la ligne
			ptr_chaine=strtok(NULL,";");
			//puissance de l'objet
			sscanf(ptr_chaine,"%d",&obj->puissance);
			ptr_chaine=strtok(NULL,";");
			//initialisation de la priorité
			obj->priorite=0;
			//initialisation de la consommation
			obj->consommation=0;
			//initialisation de la conso en Wh
			obj->conso_WH=0;
			
			//placement dans la bonne liste chaînée
			if (strcmp(categorie,"Bureau")==0)
			{
				obj->categorie=Bureau;
				obj->suiv=tableau[Bureau].tete;
				tableau[Bureau].tete=obj;
			}
			else if (strcmp(categorie,"Cuisine")==0)
			{
				obj->categorie=Cuisine;
				obj->suiv=tableau[Cuisine].tete;
				tableau[Cuisine].tete=obj;
			}
			else if (strcmp(categorie,"Entretien")==0)
			{
				obj->categorie=Entretien;
				obj->suiv=tableau[Entretien].tete;
				tableau[Entretien].tete=obj;
			}
			else if (strcmp(categorie,"Autre")==0)
			{
				obj->categorie=Autre;
				obj->suiv=tableau[Autre].tete;
				tableau[Autre].tete=obj;
			}
		}
		fclose(fichier);
	}
	else
		printf("\nDésolé, le fichier est introuvable :(\n");
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

void afficherListe(Liste *liste)
{
	Objet *obj=liste->tete;
	while(obj!=NULL)
	{
		afficherObjet(obj);
		obj=obj->suiv;
	}
}

void afficherObjet(Objet *objet)
{
	printf("Categorie: %d \nNom : %s \nPuissance (W) : %d \nPriorité : %d\nConsommation : %f\n\n",objet->categorie,objet->nom,objet->puissance,objet->priorite,objet->consommation);
}

void parcoursCat(Liste tableau[],Liste *maison,int cat)
{
	Objet *obj=tableau[cat].tete;
	
	
	while(obj!=NULL)
	{
		Objet *temporaire;
		temporaire=(Objet*)malloc(sizeof(Objet));
		strcpy(temporaire->nom,obj->nom);
		temporaire->puissance=obj->puissance;
		temporaire->categorie=obj->categorie;
		
		printf("Voulez-vous l'appareil suivant dans votre maison : %s ? o/n\n",temporaire->nom);
		char choix[3];
		scanf("%s",choix);
		if (strcmp(choix,"o")==0)
		{
			ajouterObjMaison(maison,temporaire);
		}
		obj=obj->suiv;
	}
}

void rechercheNom(Liste tableau[],Liste *maison)
{
	printf("Donnez le nom ou les premières lettres de l'appareil recherché : ");
	char lettres[LG_MAX];
	scanf("%s",lettres);
	

	for(int i=0;i<nb_cat;i++)
		{
			Objet *obj=tableau[i].tete;
			Objet *temporaire;
			temporaire=(Objet*)malloc(sizeof(Objet));
			
			while(obj!=NULL)
			{
				strcpy(temporaire->nom,obj->nom);
				temporaire->puissance=obj->puissance;
				temporaire->categorie=obj->categorie;
				
				if(strstr(temporaire->nom,lettres)!=NULL)//renvoie NULL si lettres n'est pas dans temporaire->nom
				{
					printf("Recherchiez-vous cet objet : %s ? o/n \n",temporaire->nom);
					char choix[3];
					scanf("%s",choix);
					if(strcmp(choix,"o")==0)
					{
						ajouterObjMaison(maison,temporaire);
						return; //on sort de la fonction
					}
				}
				obj=obj->suiv;
			}
		}
	printf("\nDésolé, l'appareil n'a pas été trouvé :(\n");		
}

void ajouterObjMaison(Liste *maison,Objet *objet)
{
	objet->suiv=maison->tete;
	maison->tete=objet;
	
	int priorite;
	printf("Donnez un ordre de priorité : \n");
	scanf("%d",&priorite);
	objet->priorite=priorite;
			
	float conso_h;
	printf("Donnez moyenne d'utilisation par jour (en heures) : \n");
	scanf("%f",&conso_h);
	objet->consommation=conso_h;
}

void ajouterObjMan(Liste *maison)
{
	Objet *objet;
	objet=(Objet*)malloc(sizeof(Objet));
	
	printf("Donner le nom de l'appareil : \n");
	scanf("%s",objet->nom);
	
	int puissance;
	printf("Donnez sa puissance (W) : \n");
	scanf("%d",&puissance);
	objet->puissance=puissance;
	
	printf("\n");
	printf("Choisir la catégorie :\n");
	printf("0 Bureau\n");
	printf("1 Cuisine\n");
	printf("2 Entretien\n");
	printf("3 Autre\n");
	printf("4 Quitter\n");
	printf("Choix :");
	scanf("%d",&objet->categorie);
	printf("\n");
	
	ajouterObjMaison(maison,objet);
}

void supprimerObj(Liste *maison)
{
	Objet *courant=maison->tete;
	Objet *prec, *temp;
	
	char suppr[LG_MAX];
	printf("Donner le nom de l'appareil à supprimer de la liste : \n");
	scanf("%s",suppr);
	
	if(strcmp(courant->nom,suppr)==0) //cas particulier si l'élément à supprimer est la tête
	{
		temp=courant;
		maison->tete=courant->suiv;
		free(temp);
		return;
	}
	
	courant=courant->suiv;
	prec=maison->tete;	
	while(courant!=NULL && prec!=NULL)
	{
		if(strcmp(courant->nom,suppr)==0)
		{
			printf("Voulez-vous vraiment supprimer %s de votre liste ? o/n\n",courant->nom);
			char choix[3];
			scanf("%s",choix);
			if (strcmp(choix,"o")==0)
			{
				temp=courant;
				prec->suiv=courant->suiv;
				free(temp);
				return;
			}
		}
		courant=courant->suiv;
		prec=prec->suiv;
	}
	printf("\nNous n'avons pas trouvé l'appareil à supprimer :(\n");
}

void enregistrerListe(Liste *liste,const char* nomFic)
{
	FILE *fichier;
	fichier=fopen(nomFic,"w");
	fprintf(fichier,"Catégorie;Electro;Puissance (W);Consommation (h/jour);Priorité\n");
	Objet *obj=liste->tete;
	char categorie[LG_MAX];
	while(obj!=NULL)
	{
		switch(obj->categorie)
		{
			case 0:
			strcpy(categorie,"Bureau");
			break;
			case 1:
			strcpy(categorie,"Cuisine");
			break;
			case 2:
			strcpy(categorie,"Entretien");
			break;
			case 3:
			strcpy(categorie,"Autre");
			break;
		}
		printf("%s\n",categorie);
		fprintf(fichier,"%s;%s;%d;%f;%d\n",categorie,obj->nom,obj->puissance,obj->consommation,obj->priorite);
		obj=obj->suiv;
	}
	fclose(fichier);
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
				menuPanneau(surface_maison,surface_toit,maison);
				break;
			case 3:
				quitter=true;
				break;
		}
	}
}
		
	
void equiperMaison(Liste tableau[],Liste *maison)
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
		printf("Choix : ");
		scanf("%d",&choix);
		
		switch(choix)
		{
			case 0:
				rechercheCat(tableau,maison);
				break;
			case 1:
				rechercheNom(tableau,maison);
				break;
			case 2:
				ajouterObjMan(maison);
				break;
			case 3:
				afficherListe(maison);
				break;
			case 4:
				enregistrerListe(maison,"MaMaison.csv");
				break;
			case 5:
				supprimerObj(maison);
				break;
			case 6:
				quitter=true;
				break;
		}
	}
}

void rechercheCat(Liste tableau[],Liste *maison)
{
	int choix;
	bool quitter=false;
	
	while(!quitter)
	{
		printf("\n");
		printf("Choisir la catégorie\n");
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
				parcoursCat(tableau,maison,Bureau);
				break;
			case 1:
				parcoursCat(tableau,maison,Cuisine);
				break;
			case 2:
				parcoursCat(tableau,maison,Entretien);
				break;
			case 3:
				parcoursCat(tableau,maison,Autre);
				break;
			case 4:
				quitter=true;
				break;
		}
	}
}
	
				
	
	
