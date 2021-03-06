/*
=================================================================================================
Name : electromenager.c
Author : Viviana Hirsch & Mathilde Pierrat
Description : Fonctions relatives aux appareils électroménagers
=================================================================================================
*/

#include "electromenager.h"
#include "panneaux.h"


void initListe(Liste *liste,int cat)
{
	liste->tete=NULL;
	liste->categorie=cat;
	liste->nb_elements=0;
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
		fprintf(fichier,"%s;%s;%d;%f;%d\n",categorie,obj->nom,obj->puissance,obj->consommation,obj->priorite);
		obj=obj->suiv;
	}
	fclose(fichier);
}

void lireFicMaison(Liste *maison,const char* nomFic)
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
			maison->nb_elements++;
			char *ptr_chaine=strtok(ligne,";"); //sépare la ligne en fonction des point-virgules
			obj=(Objet*)malloc(sizeof(Objet));
			
			//catégorie de l'objet
			char categorie[10];
			sscanf(ptr_chaine,"%s",categorie);
			ptr_chaine=strtok(NULL,";");
			//nom de l'objet
			sscanf(ptr_chaine,"%[^\t\n]",obj->nom); //force sscanf à ne s'arrêter qu'à une tab ou retour à la ligne
			ptr_chaine=strtok(NULL,";");
			//puissance de l'objet
			sscanf(ptr_chaine,"%d",&obj->puissance);
			ptr_chaine=strtok(NULL,";");
			//consommation (h/jour) 
			sscanf(ptr_chaine,"%f",&obj->consommation);
			ptr_chaine=strtok(NULL,";");
			//priorité
			sscanf(ptr_chaine,"%d",&obj->priorite);
			ptr_chaine=strtok(NULL,";");
			//initialisation de la conso en Wh
			obj->conso_WH=(obj->consommation)*(obj->puissance);
			
			if (strcmp(categorie,"Bureau")==0)
			{
				obj->categorie=Bureau;
			}
			else if (strcmp(categorie,"Cuisine")==0)
			{
				obj->categorie=Cuisine;
			}
			else if (strcmp(categorie,"Entretien")==0)
			{
				obj->categorie=Entretien;
			}
			else if (strcmp(categorie,"Autre")==0)
			{
				obj->categorie=Autre;
			}
			
			obj->suiv=maison->tete;
			maison->tete=obj;

		}
	fclose(fichier);
	}
	else
		printf("Le fichier n'existe pas, désolée :(");
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
	
	//transforme toute la chaîne de caractère en minuscules
	for(int i = 0; lettres[i]; i++){
  	lettres[i] = tolower(lettres[i]);
	}
	

	for(int i=0;i<nb_cat;i++)
		{
			Objet *obj=tableau[i].tete;
			Objet *temporaire;
			temporaire=(Objet*)malloc(sizeof(Objet));
			
			while(obj!=NULL)
			{
				char nom_tempo[LG_MAX];
				strcpy(temporaire->nom,obj->nom);
				temporaire->puissance=obj->puissance;
				temporaire->categorie=obj->categorie;
				
				//transforme toute la chaîne de caractère en minuscules
				strcpy(nom_tempo,temporaire->nom);
				for(int i = 0; nom_tempo[i]; i++){
  				nom_tempo[i] = tolower(nom_tempo[i]);
				}
				
				if(strstr(nom_tempo,lettres)!=NULL)//renvoie NULL si lettres n'est pas dans temporaire->nom
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
	printf("Choix :");
	scanf("%d",&objet->categorie);
	printf("\n");
	
	ajouterObjMaison(maison,objet);
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
	
	maison->nb_elements++; //compte le nb d'éléments ajoutés à la maison
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
				maison->nb_elements-=1;
				return;
			}
		}
		courant=courant->suiv;
		prec=prec->suiv;
	}
	printf("\nNous n'avons pas trouvé l'appareil à supprimer :(\n");
}
/**************************************************************


	Menus et sous-menus
	
	
***************************************************************/
		
	
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
		printf("6 Charger son fichier Maison\n");
		printf("7 Quitter\n");
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
				lireFicMaison(maison,"MaMaison.csv");
			case 7:
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
	
				
	
	
