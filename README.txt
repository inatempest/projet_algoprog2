/*
=================================================================================================
Name : README.txt
Author : Viviana Hirsch & Mathilde Pierrat
Description : Explications sur les fichiers et instructions
=================================================================================================
*/

FICHIERS PRESENTS :

- Makefile

- main.c
	Permet l'initialisation des listes des catégories et de la maison, du tableau formant l'inventaire.
	Permet également la lecture des fichiers Monthly et Daily.
	Entre ensuite directement dans le menu principal.

- electromenager.h
	Contient les structures relatives aux électroménagers et les prototypes des fonctions du menu "Equiper sa maison"

- electromenager.c
	Contient les fonctions relatives aux électroménagers, les fonctions du menu "Equiper sa maison" soit "Recherche par nom", "Enregistrement d'un fichier", "Ajout manuel d'un appareil", etc.
	
- panneaux.h
	Contient les structures relatives aux fichiers d'irradiation et les prototypes des fonctions du menu "Installer des panneaux photovoltaïques"
	
- panneaux.c
	Contient les fonctions relatives aux calculs du rendement et retour sur investissement des panneaux, à savoir "Durée du retour sur investissement", "Nombre de panneaux nécessaires", etc.
	
- Monthly_..._.csv et Daily_..._month.csv
	Contiennent les informations d'irradiation utilisées soit par année dans le cas d'un fichier Monthly, soit par heure et par mois dans le cas d'un fichier Daily, pour une ville au choix de l'utilisateur (nécessite d'aller chercher les fichiers correspondant, ville de Gardanne et mois d'avril par défaut)
	
- appareils_electromenagers.csv
	Contient une liste pré-remplie d'appareils électroménagers sélectionnables par l'utilisateur. Remplit l'inventaire.

- MaMaison.csv
	Nom du fichier dans lequel l'utilisateur peut enregistrer les appareils de sa maison après avoir fini de les choisir. Il peut également récupérer les données que ce fichier contient.

- RSI.txt
	Nom du fichier dans lequel l'utilisateur peut enregistrer les informations liées au retour sur investissement, à savoir le nombre de panneaux nécessaires, le coût d'installation, la durée de retour sur investissement, etc.
	
_____________________________________________________________
	
INSTRUCTIONS :

Pour changer les fichiers Monthly et Daily utiliser, ouvrir le main et y changer le nom des fichiers à l'emplacement indiqué.

L'utilisateur,au lancement, doit rentrer les valeurs des surfaces de sa maison et de sa toiture.
Les menus permettent ensuite de naviguer dans les différentes fonctionnalités.

MENU PRINCIPAL :
0 Voir l'inventaire disponible
1 Equiper sa maison
2 Installer des panneaux photovoltaïques
3 Quitter

MENU Equiper sa maison :
0 Recherche par catégorie
1 Recherche par nom	//supporte la casse
2 Ajouter un appareil manuellement
3 Afficher mes appareils
4 Enregistrer ma liste		//dans le fichier MaMaison.csv
5 Supprimer un appareil de la liste
6 Charger son fichier maison 	//à partir du fichier MaMaison.csv
7 Quitter

MENU Installer des panneaux photovoltaïques: //par défaut, le nombre de panneaux pris est le nombre maximal
0 Consommation de la maison en kWh et en €
1 Nombre de panneaux solaires nécessaires
2 Optimisation appareils/panneaux solaires sur une semaine
3 Coût installation panneaux solaires
4 Durée associée au retour sur investissement
5 Enregistrer indicateurs RSI 	//dans le fichier RSI.txt
6 Entrer de nouvelles valeurs pour les surfaces
7 Saisir le nombre de panneaux manuellement
8 Quitter


