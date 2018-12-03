#include "affiche.h"


int main(void)
{
	int i,k,l;
	int annee = 2000;
	int numero = 0;
	int** tabProba = NULL;
	int tailleProba = 0;
	
	int nombreTournois,typeTournois,typeTerrain,tailleNomTournois;
	char* nomTournois;
	char c;
	
	srand(time(NULL));
	
	Joueur_t* tabJoueur = NULL;
	ListeTournois_t* listeTournois = NULL;
	
	ListeTournois_t* listeGC = NULL;
	ListeTournois_t* listeAlt = NULL;
	
	FILE* ficTmp = fopen("listeTournois.txt","r");
	fscanf(ficTmp,"%d",&nombreTournois);
	
	
	char rep;
	
	fclose(ficTmp);
	
	tabJoueur = set_liste_joueur(tabProba,&tailleProba);
	tabProba = set_tab_proba(tailleProba);
	
	
	printf("Voulez vous lire un fichier (O,o,Y,y = Oui)\n");
	scanf(" %c",&rep);
	if(rep == 'O' || rep == 'o' || rep == 'Y' || rep == 'y')
	{
		char nomFic[1000];
		printf("\n Nom du fichier a lire (sans le \".txt\" : ");
		scanf(" %s",nomFic);
		
		int cptNomFic = 0;
		
		while(nomFic[cptNomFic] != '\0') cptNomFic++;
		
		nomFic[cptNomFic] = '.';
		nomFic[cptNomFic + 1] = 't';
		nomFic[cptNomFic + 2] = 'x';
		nomFic[cptNomFic + 3] = 't';
		nomFic[cptNomFic + 4] = '\0';
		
		
		listeAlt = malloc(80*sizeof(ListeTournois_t));
		
		int cptListe,cptMatch;
		
		for(cptListe = 0; cptListe < 80; cptListe++)
		{
			// malloc du nombre de grand joueurs
			listeAlt[cptListe].match = malloc(6*sizeof(MatchImportant_t)); 
			
			for(cptMatch = 0; cptMatch < 6; cptMatch++)
				listeAlt[cptListe].match[cptMatch].estVide = 1;
				
			listeAlt[cptListe].annee = -1;
		}
		
		if(lire_fichier_liste_tournois(nomFic,listeAlt) != -1)
			menu(listeAlt,tabJoueur,1);
		
		printf("\n\n   ***** =======>   _ Fin Alternative du programme _   <======= *****\n\n");
		
		return 0;
	}
	else
	{
		listeGC = malloc(80*sizeof(ListeTournois_t));
		
		int cptListe,cptMatch;
		
		for(cptListe = 0; cptListe < 80; cptListe++)
		{
			// malloc du nombre de grand joueurs
			listeGC[cptListe].match = malloc(6*sizeof(MatchImportant_t)); 
			
			for(cptMatch = 0; cptMatch < 6; cptMatch++)
				listeGC[cptListe].match[cptMatch].estVide = 1;
				
			listeGC[cptListe].annee = -1;
		}
	}
	
	int nombreCarriere = 50;
	int compteurCarriere;
	//for(compteurCarriere = 0; compteurCarriere < nombreCarriere; compteurCarriere++)
	{
		for(l = 0; l < 20; l++)
		{
			FILE* fichierTournois = fopen("listeTournois.txt","r");
			fscanf(fichierTournois,"%d",&nombreTournois);
			
			numero = 0;
			
			for(k=0;k<nombreTournois;k++)
			{
				fscanf(fichierTournois,"%d %d",&typeTournois,&tailleNomTournois);
				
				nomTournois = malloc(tailleNomTournois*sizeof(int));
				
				fscanf(fichierTournois,"%c",&c);
				
				for(i = 0;i < tailleNomTournois;i++)
				{
					fscanf(fichierTournois,"%c",&c);
					nomTournois[i] = c;
				}
				
				fscanf(fichierTournois,"%c",&c);
				
				fscanf(fichierTournois,"%d",&typeTerrain);

				tournois(tabJoueur,nomTournois,tailleNomTournois,typeTournois,typeTerrain,annee,numero,listeGC,tabProba);
				
				//printf("APRES TOURNOIS\n");
				trier_joueur(tabJoueur);
				set_meilleur_rang(tabJoueur);
				numero++;
				//affiche_tab_joueur(tabJoueur);
				free(nomTournois);	
			}
			annee++;
			fclose(fichierTournois);
		}
	}
	
	/*
	for(i=0;i<2;i++)
	{
		printf("OK\n");
		numero = 0;
		tournois(tabJoueur,"Dubai",5,MASTERS_250,MOQUETTE,annee,numero,listeGC,tabProba);
		printf("APRES TOURNOIS\n");
		trier_joueur(tabJoueur);
		printf("APRES TRI\n");
		set_meilleur_rang(tabJoueur);
		printf("APRES SET RANG\n");
		numero++;
		printf("---------------------------------------------------\n");
		
		//affiche_evolution_temporelle_joueur(tabJoueur);
		
		tournois(tabJoueur,"Rolland Garros",14,GRAND_CHELEM,TERRE_BATTUE,annee,numero,listeGC,tabProba);
		printf("APRES TOURNOIS\n");
		trier_joueur(tabJoueur);
		printf("APRES TRI\n");
		set_meilleur_rang(tabJoueur);
		printf("APRES SET RANG\n");
		numero++;
		printf("---------------------------------------------------\n");
		
		//affiche_evolution_temporelle_joueur(tabJoueur);
		
		tournois(tabJoueur,"Herbe tournois",14,MASTERS_1000,HERBE,annee,numero,listeGC,tabProba);
		trier_joueur(tabJoueur);
		set_meilleur_rang(tabJoueur);
		numero++;
		printf("---------------------------------------------------\n");
		
		//affiche_evolution_temporelle_joueur(tabJoueur);
		
		tournois(tabJoueur,"Huioltre",8,MASTERS_500,DUR,annee,numero,listeGC,tabProba);
		trier_joueur(tabJoueur);
		set_meilleur_rang(tabJoueur);
		numero++;
		printf("---------------------------------------------------\n");
		
		//affiche_evolution_temporelle_joueur(tabJoueur);
		annee++;
	}*/
	
	menu(listeGC,tabJoueur,0);
	
	printf("\n\n    =======>   Fin du programme   <=======\n\n");
	
	return 0;
}
