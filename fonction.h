#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define NB_JOUEUR 128

#define MASTERS_250 250
#define MASTERS_500 500
#define MASTERS_1000 1000
#define GRAND_CHELEM 2000

#include "tournois.h"


Joueur_t* set_liste_joueur(int** tabProba,int* tailleTab);
int** set_tab_proba(int tailleTab);
void affiche_liste_joueur(Joueur_t* tabJoueur);
void affiche_liste_grand_joueur(Joueur_t* tabJoueur);

Tournois_t* set_tournois(int terrain,int typeTournois,char* nom,int tailleNomTournois,int edition,int num);
void tournois(Joueur_t* tabJoueur,char* nom,int tailleNomTournois,int typeTournois,int terrain,int edition,int num,ListeTournois_t* liste,int** proba);
void affiche_tableau_competition(int* t);

void mise_a_jour_point_ATP(Joueur_t* perdant,Tournois_t* tournois,int tour);
void masters250(Joueur_t* tmp,ListeTournois_t* liste,Tournois_t* t,int** proba,Joueur_t* tabJoueur,int enregistrer,int annee);
void masters500(Joueur_t* tmp,ListeTournois_t* liste,Tournois_t* t,int** proba,Joueur_t* tabJoueur,int annee);
void masters1000(Joueur_t* tmp,ListeTournois_t* liste,Tournois_t* t,int** proba,Joueur_t* tabJoueur,int annee);
void masters2000(Joueur_t* tabJoueur,ListeTournois_t* liste,Tournois_t* t,int** proba,int annee,int nomTournois);

int match(Joueur_t j1,Joueur_t j2,int nomTournois,int typeTerrain,int** proba,int annee);
int proba(int p, int idJ1, int idJ2);
int puiss(int a,int b);

Joueur_t get_joueur_by_id(Joueur_t* t,int id);
Joueur_t* get_joueur_pointeur_by_id(Joueur_t* tabJoueur,int id);
void affiche_match_important(Tournois_t* t);
void ajouter_liste_tournois(Tournois_t* t1,ListeTournois_t* liste,int y);
void trier_joueur(Joueur_t* tab);
int indice_meilleur_joueur(Joueur_t* tab,int debut);
void set_meilleur_rang(Joueur_t* tab);
void affiche_liste_tournois(ListeTournois_t* liste);

int est_dans_periode_faible(Joueur_t a,int annee);
int est_dans_periode_forte(Joueur_t a,int annee);



Joueur_t* set_liste_joueur(int** tabProba,int* tailleTab)
{
	// [1] => On remplie le tableau des joueur avec les grand joueur
	FILE* fic = NULL;
	Joueur_t* tabJoueur = NULL;
	int i;
	
	FILE* listeT = NULL;
	
	fic = fopen("listeGrandJoueur.txt","r"); 
	listeT = fopen("listeTournois.txt","r"); // pour lire le nombre de tournois
	
	tabJoueur = malloc(NB_JOUEUR*sizeof(Joueur_t));// Malloc tu tableau de Joueur
	
	if((fic == NULL)||(listeT == NULL))
	{
		printf("Erreur lors de l'ouverture du fichier\n");
		return NULL;
	}
	
	int nbT;
	fscanf(listeT,"%d",&nbT);
	fclose(listeT);
	
	int nbGrdJoueur,idTmp,nbLettre,anneeDeb,anneeFin; 
	char buf[15];
	char nom[50];
	
	// NOMBRE GRAND JOUEUR
	fscanf(fic,"%d",&nbGrdJoueur); //printf("Nb Grd Joueur => %d\n",nbGrdJoueur);
	// JOUEUR
	fscanf(fic,"%s",buf); //printf("%s\n",buf);
	*tailleTab = nbGrdJoueur;
	
	for(i = 0; i < nbGrdJoueur; i++)
	{
		// LECTURE DES JOUEURS
		fscanf(fic,"%d %d %s",&idTmp,&nbLettre,nom); //printf("%d %d %s\n",idTmp,nbLettre,nom);
		
		tabJoueur[i].id = i + 1;
		tabJoueur[i].type = 1;
		tabJoueur[i].nombrePointATP = 0;
		tabJoueur[i].rang = i + 1;
		tabJoueur[i].recordPointATP = 0;
		tabJoueur[i].meilleurRang = 128;
		
		
		char_init(&tabJoueur[i].nom);
		char_remplir(&tabJoueur[i].nom,nom,nbLettre); //char_affiche(&tabJoueur[i].nom,1);
		
		
		
		int_init(&tabJoueur[i].nbTournoisRemporte);
		
		int_malloc(&tabJoueur[i].nbTournoisRemporte,nbGrdJoueur);
		
		int_init_a_une_valeur(&tabJoueur[i].nbTournoisRemporte,0); // on initialise le tableau a 0
		
		tabJoueur[i].pointAnneePrecedente = malloc(nbT*sizeof(int));
		
		int j;
		
		for(j = 0; j < nbT ; j++)
			tabJoueur[i].pointAnneePrecedente[j] = 0;
		
		int_init(&tabJoueur[i].tempsParClassement);
		
		int_malloc(&tabJoueur[i].tempsParClassement,nbGrdJoueur);
		
		int_init_a_une_valeur(&tabJoueur[i].tempsParClassement,0); // on initialise le tableau a 0
		
	}
	
	while(1) // ON AVANCE JUSQUA PERIODE FORTE
	{
		fscanf(fic,"%s",buf);
		if(buf[0] == 'P')
			break;
	}
	//printf("PERIODE FORTE\n");
	
	int probabilite,nbPeriode;
	char poubelleVisuelle,trash1,trash2;
	
	for(i = 0; i < nbGrdJoueur ; i++)
	{
		int_init(&tabJoueur[i].probaPeriodeForte);
		int_malloc(&tabJoueur[i].probaPeriodeForte,4);
		int cptProba;
		
		
		for(cptProba = 0; cptProba < 4; cptProba++)
		{
			fscanf(fic,"%d",&probabilite); //printf("%d ",probabilite);
			tabJoueur[i].probaPeriodeForte.tab[cptProba] = probabilite;
		}
		//printf("\n");
		fscanf(fic,"%d %c",&nbPeriode,&poubelleVisuelle); //printf("%d %c ",nbPeriode,poubelleVisuelle);
		
		int_init(&tabJoueur[i].periodeForte);
		int_malloc(&tabJoueur[i].periodeForte,2*nbPeriode);
		
		int j;
		int cpt = 0;
		for(j = 0; j < nbPeriode; j++)
		{
			fscanf(fic,"%d %c %d %c",&anneeDeb,&trash1,&anneeFin,&trash2); //printf("%d %c %d %c ",anneeDeb,trash1,anneeFin,trash2);
			
			tabJoueur[i].periodeForte.tab[cpt] = anneeDeb;
			cpt++;
			tabJoueur[i].periodeForte.tab[cpt] = anneeFin;
			cpt++;
		}
		//printf("\n");
	}
	
	
	while(1) // ON AVANCE JUSQUA PERIODE FAIBLE
	{
		fscanf(fic,"%s",buf);
		if(buf[0] == 'P')
			break;
	}
	//printf("PERIODE FAIBLE\n");
	
	for(i = 0; i < nbGrdJoueur ; i++)
	{
		int_init(&tabJoueur[i].probaPeriodeFaible);
		int_malloc(&tabJoueur[i].probaPeriodeFaible,4);
		int cptProba;
		
		
		for(cptProba = 0; cptProba < 4; cptProba++)
		{
			fscanf(fic,"%d",&probabilite); //printf("%d ",probabilite);
			tabJoueur[i].probaPeriodeFaible.tab[cptProba] = probabilite;
		}
		//printf("\n");
		fscanf(fic,"%d %c",&nbPeriode,&poubelleVisuelle); //printf("%d %c",nbPeriode,poubelleVisuelle);
		
		int_init(&tabJoueur[i].periodeFaible);
		int_malloc(&tabJoueur[i].periodeFaible,2*nbPeriode);
		
		int j;
		int cpt = 0;
		for(j = 0; j < nbPeriode; j++)
		{
			fscanf(fic,"%d %c %d %c",&anneeDeb,&trash1,&anneeFin,&trash2); //printf("%d %c %d %c ",anneeDeb,trash1,anneeFin,trash2);
			
			tabJoueur[i].periodeFaible.tab[cpt] = anneeDeb;
			cpt++;
			tabJoueur[i].periodeFaible.tab[cpt] = anneeFin;
			cpt++;
		}
		//printf("\n");
	}
	
	while(1)
	{
		fscanf(fic,"%s",buf);
		if(buf[0] == 'T')
			break;
	}
	//printf("TERRAIN FAVORI\n");
	
	// TERRAIN FAVORI
	int j,typeTerrain,nbFav,idJActu; // nbFav => nombre de joueur par terrain
	
	for(i = 0; i < nbGrdJoueur; i++) // initialisation des terrain favori
	{
		tabJoueur[i].terrainFavori[0] = -1;
		tabJoueur[i].terrainFavori[1] = -1;
	}
	
	int probaTer;
	// TERRAIN FAVORI
	for(i = 0; i < nbGrdJoueur ; i++) // Lecture des terrain favori
	{
		for(j = 0; j < 4; j++)
		{
			fscanf(fic,"%d",&probaTer);
			tabJoueur[i].terrainFavori[j] = probaTer;
		}
		//printf("\n");
	}
	
	fscanf(fic,"%s",nom); //printf("%s\n",nom);
	// TOURNOIS FAVORI
	
	int nbJ,oa,rg,wim,us;
	
	for(i = 0; i < nbGrdJoueur; i++) // Lecture des tournois favori
	{
		fscanf(fic,"%d %d %d %d %d",&nbJ,&oa,&rg,&wim,&us); //printf("%d %d %d %d\n",oa,rg,wim,us);
		tabJoueur[i].tournoisFavori[0] = oa;
		tabJoueur[i].tournoisFavori[1] = rg;
		tabJoueur[i].tournoisFavori[2] = wim;
		tabJoueur[i].tournoisFavori[3] = us;
	}
	
	fclose(fic);
	
	// [2] => on remplie le tableau des joueurs avec les petits joueur
	
	int id = nbGrdJoueur + 1;
	
	for(i = nbGrdJoueur; i < NB_JOUEUR; i++)
	{
		tabJoueur[i].id = id; id++;
		tabJoueur[i].type = 0;
		tabJoueur[i].nombrePointATP = 0;
		tabJoueur[i].rang = i + 1;
		tabJoueur[i].recordPointATP = 0;
		tabJoueur[i].meilleurRang = 128;
		
		tabJoueur[i].pointAnneePrecedente = malloc(nbT*sizeof(int));
			
		for(j = 0; j < nbT ; j++)
			tabJoueur[i].pointAnneePrecedente[j] = 0;
			
		int_init(&tabJoueur[i].nbTournoisRemporte);
		
		int_malloc(&tabJoueur[i].nbTournoisRemporte,4);
		
		int_init_a_une_valeur(&tabJoueur[i].nbTournoisRemporte,0); // on initialise le tableau a 0
		
		int_init(&tabJoueur[i].tempsParClassement);
		
		int_malloc(&tabJoueur[i].tempsParClassement,nbGrdJoueur); 
		
		int_init_a_une_valeur(&tabJoueur[i].tempsParClassement,0); // on initialise le tableau a 0
	}
	
	int oo,ii;
	
	printf("PERIODE FORTE\n");
	for(oo = 0; oo < 6; oo++)
	{
		char_affiche(&tabJoueur[oo].nom,1);
		int pp = tabJoueur[oo].periodeForte.tailleTab;
		
		for(ii = 0; ii < pp; ii++)
		{
			printf("%d ",tabJoueur[oo].periodeForte.tab[ii]);
		}
		printf("\n");
	}
	
	return tabJoueur;
}

int** set_tab_proba(int tailleTab)
{
	int i,nbProba,idJ1,idJ2,p;
	int** tab = NULL;
	char buf[50];
	
	tab = malloc(tailleTab*sizeof(int*));
	for(i = 0; i < tailleTab; i++)
		tab[i] = malloc(tailleTab*sizeof(int));
	
	FILE* fic = NULL;
	fic = fopen("listeGrandJoueur.txt","r");
	
	while(1)
	{
		fscanf(fic,"%s",buf);
		
		if((buf[0] == 'P')&&(buf[1] == 'R')&&(buf[2] == 'O')&&(buf[3] == 'B')&&(buf[4] == 'A'))
			break;
	}
	
	fscanf(fic,"%d",&nbProba); //printf("PROBA %d\n",nbProba);
	
	for(i = 0; i < nbProba; i++)
	{
		fscanf(fic,"%d %d %d",&idJ1,&idJ2,&p); //printf("%d %d %d\n",idJ1,idJ2,p);
		tab[idJ1-1][idJ2-1] = p; // -1 car les id commencent a 1
		tab[idJ2-1][idJ1-1] = 100 - p; // 100 - p car c'est la proba inverse
	}
	
	for(i = 0; i < tailleTab; i++)
	{
		tab[i][i] = -1;
	}
	
	return tab;
}


void tournois(Joueur_t* tabJoueur,char* nom,int tailleNomTournois,int typeTournois,int terrain,int edition,int num,ListeTournois_t* liste,int** proba)
{
	int i;
	Tournois_t* tournois = NULL;
	tournois = set_tournois(terrain,typeTournois,nom,tailleNomTournois,edition,num);
	
	int nomTournois = -1;
	
	if(typeTournois == 2000)
	{
		/// \warning non urgent Mettre a jour par rapport au nom du tournois (faire ca de maniere plus propre)
		if(tournois->nom.tab[0] == 'O')
			nomTournois = 0;
		else if(tournois->nom.tab[0] == 'R')
			nomTournois = 1;
		else if(tournois->nom.tab[0] == 'W')
			nomTournois = 2;
		else
			nomTournois = 3;
		
		masters2000(tabJoueur,liste,tournois,proba,tournois->annee,nomTournois); // creer 1 tournoi
		
		free(tournois->match);
		free(tournois->nombrePointATP);
		char_vider(&tournois->nom);
		free(tournois);
	}
	else if(typeTournois == 1000)
	{
		Joueur_t* joueurTmp = NULL;
		
		Tournois_t* tournois2 = NULL;
		
		int j;
		
		joueurTmp = malloc(64*sizeof(Joueur_t));
		
		for(i = 0; i < 64 ; i++)
		{
			joueurTmp[i] = tabJoueur[i];
		}
		masters1000(joueurTmp,liste,tournois,proba,tabJoueur,edition); // Le premier tournois
		
		free(tournois->match);
		free(tournois->nombrePointATP);
		char_vider(&tournois->nom);
		free(tournois);
		
		free(joueurTmp);
		joueurTmp = malloc(32*sizeof(Joueur_t));
		tournois2 = set_tournois(terrain,MASTERS_500,nom,tailleNomTournois,edition,num);
		j = 0;
		for(i = 64; i < 96 ; i++)
		{
			joueurTmp[j] = tabJoueur[i];
			j++;
		}
		masters500(joueurTmp,liste,tournois2,proba,tabJoueur,edition); // Le deuxieme tournois
		
		free(tournois2->match);
		free(tournois2->nombrePointATP);
		char_vider(&tournois2->nom);
		free(tournois2);
		
		free(joueurTmp);
		
		joueurTmp = malloc(32*sizeof(Joueur_t));
		tournois2 = set_tournois(terrain,MASTERS_500,nom,tailleNomTournois,edition,num);
		j = 0;
		for(i = 96; i < 128 ; i++)
		{
			joueurTmp[j] = tabJoueur[i];
			j++;
		}
		masters500(joueurTmp,liste,tournois2,proba,tabJoueur,edition); // Le deuxieme tournois
		
		free(tournois2->match);
		free(tournois2->nombrePointATP);
		char_vider(&tournois2->nom);
		free(tournois2);
		
		free(joueurTmp);
	}
	else if (typeTournois == 500)
	{
		Joueur_t* joueurTmp = NULL;
		
		Tournois_t* tournois2 = NULL;
		Tournois_t* tournois3 = NULL;
		Tournois_t* tournois4 = NULL;
		
		joueurTmp = malloc(32*sizeof(Joueur_t));
		
		int cpt = 0;
		
		for(i = 0; i < 32 ; i++)
		{		
			joueurTmp[i] = tabJoueur[i];
		}
		
		masters500(joueurTmp,liste,tournois,proba,tabJoueur,edition); // Le premier tournois
		
		free(tournois->match);
		free(tournois->nombrePointATP);
		char_vider(&tournois->nom);
		free(tournois);
		
		free(joueurTmp);
		
		joueurTmp = malloc(32*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 32; i < 64 ; i++)
		{
			joueurTmp[cpt] = tabJoueur[i];
			cpt++;
		}
		tournois2 = set_tournois(terrain,typeTournois,nom,tailleNomTournois,edition,num);
		masters500(joueurTmp,liste,tournois2,proba,tabJoueur,edition); // Le deuxieme tournois
		
		free(tournois2->match);
		free(tournois2->nombrePointATP);
		char_vider(&tournois2->nom);
		free(tournois2);
		
		free(joueurTmp);
		joueurTmp = malloc(16*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 64; i < 80 ; i++)
		{
			joueurTmp[cpt] = tabJoueur[i];
			cpt++;
		}
		
		tournois3 = set_tournois(terrain,MASTERS_250,nom,tailleNomTournois,edition,num);
		masters250(joueurTmp,liste,tournois3,proba,tabJoueur,0,edition);
		
		free(tournois3->match);
		free(tournois3->nombrePointATP);
		char_vider(&tournois3->nom);
		free(tournois3);
		
		free(joueurTmp);
		
		joueurTmp = malloc(16*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 80; i < 96 ; i++)
		{
			joueurTmp[cpt] = tabJoueur[i];
			cpt++;
		}
		
		tournois3 = set_tournois(terrain,MASTERS_250,nom,tailleNomTournois,edition,num);
		masters250(joueurTmp,liste,tournois3,proba,tabJoueur,0,edition);
		free(joueurTmp);
		
		joueurTmp = malloc(16*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 96; i < 112 ; i++)
		{
			joueurTmp[cpt] = tabJoueur[i];
			cpt++;
		}
		
		tournois3 = set_tournois(terrain,MASTERS_250,nom,tailleNomTournois,edition,num);
		masters250(joueurTmp,liste,tournois3,proba,tabJoueur,0,edition);
		
		free(tournois3->match);
		free(tournois3->nombrePointATP);
		char_vider(&tournois3->nom);
		free(tournois3);
		
		free(joueurTmp);
		
		joueurTmp = malloc(16*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 112; i < 128 ; i++)
		{
			joueurTmp[cpt] = tabJoueur[i];
			cpt++;
		}
		
		tournois3 = set_tournois(terrain,MASTERS_250,nom,tailleNomTournois,edition,num);
		masters250(joueurTmp,liste,tournois3,proba,tabJoueur,0,edition); // Le deuxieme tournois
		
		free(tournois3->match);
		free(tournois3->nombrePointATP);
		char_vider(&tournois3->nom);
		free(tournois3);
		
		free(joueurTmp);
	}
	else
	{
		Joueur_t* joueurTmp = NULL;
		
		Tournois_t* tournois2 = NULL;
		Tournois_t* tournois3 = NULL;
		Tournois_t* tournois4 = NULL;
		Tournois_t* tournois5 = NULL;
		
		joueurTmp = malloc(16*sizeof(Joueur_t));
		
		int cpt = 0;
		
		for(i = 0; i < NB_JOUEUR ; i++)
		{
			if(i%8 == 0)
			{
				joueurTmp[cpt] = tabJoueur[i];
				cpt++;
			}
		}
		
		masters250(joueurTmp,liste,tournois,proba,tabJoueur,1,edition); // Le premier tournois
		
		free(tournois->match);
		free(tournois->nombrePointATP);
		char_vider(&tournois->nom);
		free(tournois);
		
		free(joueurTmp);
		joueurTmp = malloc(16*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 0; i < NB_JOUEUR ; i++)
		{
			if(i%8 == 1)
			{
				joueurTmp[cpt] = tabJoueur[i];
				cpt++;
			}
		}
		tournois2 = set_tournois(terrain,typeTournois,nom,tailleNomTournois,edition,num);
		masters250(joueurTmp,liste,tournois2,proba,tabJoueur,1,edition); // Le deuxieme tournois
		
		free(tournois2->match);
		free(tournois2->nombrePointATP);
		char_vider(&tournois2->nom);
		free(tournois2);
		
		free(joueurTmp);
		joueurTmp = malloc(16*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 0; i < NB_JOUEUR ; i++)
		{
			if(i%8 == 2)
			{
				joueurTmp[cpt] = tabJoueur[i];
				cpt++;
			}
		}
		tournois3 = set_tournois(terrain,typeTournois,nom,tailleNomTournois,edition,num);
		masters250(joueurTmp,liste,tournois3,proba,tabJoueur,1,edition); // Le troisieme tournois
		
		free(tournois3->match);
		free(tournois3->nombrePointATP);
		char_vider(&tournois3->nom);
		free(tournois3);
		
		free(joueurTmp);
		joueurTmp = malloc(16*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 0; i < NB_JOUEUR ; i++)
		{
			if(i%8 == 3)
			{
				joueurTmp[cpt] = tabJoueur[i];
				cpt++;
			}
		}
		tournois4 = set_tournois(terrain,typeTournois,nom,tailleNomTournois,edition,num);
		masters250(joueurTmp,liste,tournois4,proba,tabJoueur,1,edition); // Le quatrieme tournois
		
		free(tournois4->match);
		free(tournois4->nombrePointATP);
		char_vider(&tournois4->nom);
		free(tournois4);
		
		free(joueurTmp);
		joueurTmp = malloc(16*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 0; i < NB_JOUEUR ; i++)
		{
			if(i%8 == 4)
			{
				joueurTmp[cpt] = tabJoueur[i];
				cpt++;
			}
		}
		tournois5 = set_tournois(terrain,typeTournois,nom,tailleNomTournois,edition,num);
		masters250(joueurTmp,liste,tournois5,proba,tabJoueur,0,edition); 
		
		free(tournois5->match);
		free(tournois5->nombrePointATP);
		char_vider(&tournois5->nom);
		free(tournois5);
		
		free(joueurTmp);
		joueurTmp = malloc(16*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 0; i < NB_JOUEUR ; i++)
		{
			if(i%8 == 5)
			{
				joueurTmp[cpt] = tabJoueur[i];
				cpt++;
			}
		}
		tournois5 = set_tournois(terrain,typeTournois,nom,tailleNomTournois,edition,num);
		masters250(joueurTmp,liste,tournois5,proba,tabJoueur,0,edition); 
		
		free(tournois5->match);
		free(tournois5->nombrePointATP);
		char_vider(&tournois5->nom);
		free(tournois5);
		
		free(joueurTmp);
		joueurTmp = malloc(16*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 0; i < NB_JOUEUR ; i++)
		{
			if(i%8 == 6)
			{
				joueurTmp[cpt] = tabJoueur[i];
				cpt++;
			}
		}
		tournois5 = set_tournois(terrain,typeTournois,nom,tailleNomTournois,edition,num);
		masters250(joueurTmp,liste,tournois5,proba,tabJoueur,0,edition); 
		
		free(tournois5->match);
		free(tournois5->nombrePointATP);
		char_vider(&tournois5->nom);
		free(tournois5);
		
		free(joueurTmp);
		joueurTmp = malloc(16*sizeof(Joueur_t));
		cpt = 0;
		
		for(i = 0; i < NB_JOUEUR ; i++)
		{
			if(i%8 == 7)
			{
				joueurTmp[cpt] = tabJoueur[i];
				cpt++;
			}
		}
		tournois5 = set_tournois(terrain,typeTournois,nom,tailleNomTournois,edition,num);
		masters250(joueurTmp,liste,tournois5,proba,tabJoueur,0,edition); 
		
		free(tournois5->match);
		free(tournois5->nombrePointATP);
		char_vider(&tournois5->nom);
		free(tournois5);
		
		free(joueurTmp);
	}
	
	// affiche_tournois(tournois);
	
	return ;
}

Tournois_t* set_tournois(int terrain,int typeTournois,char* nom,int tailleNomTournois,int edition,int num)
{
	Tournois_t* t = malloc(sizeof(Tournois_t));
	
	if( typeTournois == 250 )
	{
		t->recompensePointATP = 250;
		t->nombreTours = 4;
		t->nombrePointATP = malloc(4*sizeof(int));
		
		t->nombrePointATP[0] = 20;
		t->nombrePointATP[1] = 45;
		t->nombrePointATP[2] = 90;
		t->nombrePointATP[3] = 150;
	}
	else if( typeTournois == 500 )
	{
		t->recompensePointATP = 500;
		t->nombreTours = 5;
		t->nombrePointATP = malloc(5*sizeof(int));
		
		t->nombrePointATP[0] = 20;
		t->nombrePointATP[1] = 45;
		t->nombrePointATP[2] = 90;
		t->nombrePointATP[3] = 180;
		t->nombrePointATP[4] = 300;
	}
	else if( typeTournois == 1000 )
	{
		t->recompensePointATP = 1000;
		t->nombreTours = 6;
		t->nombrePointATP = malloc(6*sizeof(int));
		
		t->nombrePointATP[0] = 20;
		t->nombrePointATP[1] = 45;
		t->nombrePointATP[2] = 90;
		t->nombrePointATP[3] = 180;
		t->nombrePointATP[4] = 360;
		t->nombrePointATP[5] = 600;
	}
	else
	{
		t->recompensePointATP = 2000;
		t->nombreTours = 7;
		t->nombrePointATP = malloc(7*sizeof(int));
		
		t->nombrePointATP[0] = 30;
		t->nombrePointATP[1] = 45;
		t->nombrePointATP[2] = 90;
		t->nombrePointATP[3] = 180;
		t->nombrePointATP[4] = 360;
		t->nombrePointATP[5] = 700;
		t->nombrePointATP[6] = 1200;
	}
	
	int i;
	
	char_init(&t->nom);
	char_remplir(&t->nom,nom,tailleNomTournois);
	
	t->annee = edition;
	t->numero = num;
	
	t->terrain = terrain;
	
	t->match = malloc(6*sizeof(MatchImportant_t));
	
	for( i = 0; i < 6; i++)
		t->match[i].estVide = 1;
	
	return t;
}

/// \warning non urgent Les variable "enregistrer" et "liste" ne sont plus vraiment utile...
void masters250(Joueur_t* tmp,ListeTournois_t* liste,Tournois_t* t,int** proba,Joueur_t* tabJoueur,int enregistrer,int annee)
{
	int i,j;
	
	int alea;
	
	int* tour;
	int* tourSuivant;
	
	tour = malloc(16*sizeof(int));
	t->match = NULL;
	
	for(i = 0; i < 16; i++)
		tour[i] = -1;
		
	alea = rand()%4; // Nombre aleatoire entre 0 et 15
	
	tour[alea] = tmp[0].id;
	tour[8 + alea] = tmp[1].id;
	tour[4 + alea] = tmp[2].id;
	tour[12 + alea] = tmp[3].id;
	
	int ok;
	
	for(i = 4; i < 16; i++)
	{
		ok = 0;
		alea = rand()%(16 - i) + 1;
		
		for(j = 0; j < 16; j++)
		{
			if(tour[j] == -1)
			{
				ok++;
			}
			if(ok == alea)
			{
				tour[j] = tmp[i].id;
				break;
			}
		}
	}
	
	//printf("Master 250\n");
	
	for(i = 0; i < 4; i++)
	{
		int cpt = 0;
		
		tourSuivant = malloc(puiss(2 , 4 - i - 1)*sizeof(int));
		
		for(j = 0; j < puiss(2 , 4 - i); j = j + 2)
		{
			tourSuivant[cpt] = match(get_joueur_by_id(tabJoueur,tour[j]),get_joueur_by_id(tabJoueur,tour[j+1]),-1,t->terrain,proba,annee);
			
			Joueur_t* a = get_joueur_pointeur_by_id(tabJoueur,tour[j]);
			Joueur_t* b = get_joueur_pointeur_by_id(tabJoueur,tour[j+1]);
			
			if(tourSuivant[cpt] == a->id) // Si b perd
				mise_a_jour_point_ATP(b,t,i);
			else // Si a perd
				mise_a_jour_point_ATP(a,t,i);
			
			cpt++;
		}
		
		free(tour);
		tour = malloc(cpt*sizeof(int));
		
		for(j = 0; j < cpt; j++)
		{
			tour[j] = tourSuivant[j];
			//if(enregistrer == 1)
				//printf(" %d",tour[j]);
		}
		//if(enregistrer == 1)
				//printf(" %d",tour[j]);
		free(tourSuivant);
	}
	
	if(enregistrer == 1)
		t->idVainqueur = tour[0];
	
	Joueur_t* vain = get_joueur_pointeur_by_id(tabJoueur,tour[0]);
	
	vain->nombrePointATP -= vain->pointAnneePrecedente[t->numero];
	vain->pointAnneePrecedente[t->numero] = t->recompensePointATP;
	vain->nombrePointATP += t->recompensePointATP;
	
	if(vain->recordPointATP < vain->nombrePointATP)
	{
		vain->recordPointATP = vain->nombrePointATP;
	}
	
	vain->nbTournoisRemporte.tab[3] = vain->nbTournoisRemporte.tab[3] + 1;
	
	//if(enregistrer == 1)
		//printf(" VAINQUEUR %d\n",tour[0]);
	
	//affiche_match_important(t);
	free(tour);
}


/// \warning Les variable "enregistrer" et "liste" ne sont plus vraiment utile...

void masters500(Joueur_t* tmp,ListeTournois_t* liste,Tournois_t* t,int** proba,Joueur_t* tabJoueur,int annee)
{
	int i,j;
	
	int alea;
	
	int* tour;
	int* tourSuivant;
	
	tour = malloc(32*sizeof(int));
	t->match = NULL;
	
	for(i = 0; i < 32; i++)
		tour[i] = -1;
		
	alea = rand()%8; // Nombre aleatoire entre 0 et 15
	
	tour[alea] = tmp[0].id;
	tour[16 + alea] = tmp[1].id;
	tour[8 + alea] = tmp[2].id;
	tour[24 + alea] = tmp[3].id;
	
	int ok;
	
	for(i = 4; i < 32; i++)
	{
		ok = 0;
		alea = rand()%(32 - i) + 1;
		
		for(j = 0; j < 32; j++)
		{
			if(tour[j] == -1)
			{
				ok++;
			}
			if(ok == alea)
			{
				tour[j] = tmp[i].id;
				break;
			}
		}
	}
	
	//printf("Master 500\n");
	
	for(i = 0; i < 5; i++)
	{
		int cpt = 0;
		
		tourSuivant = malloc(puiss(2 , 5 - i - 1)*sizeof(int));
		
		for(j = 0; j < puiss(2 , 5 - i); j = j + 2)
		{
			tourSuivant[cpt] = match(get_joueur_by_id(tabJoueur,tour[j]),get_joueur_by_id(tabJoueur,tour[j+1]),-1,t->terrain,proba,annee);
			
			Joueur_t* a = get_joueur_pointeur_by_id(tabJoueur,tour[j]);
			Joueur_t* b = get_joueur_pointeur_by_id(tabJoueur,tour[j+1]);
			
			if(tourSuivant[cpt] == a->id) // Si b perd
				mise_a_jour_point_ATP(b,t,i);
			else // Si a perd
				mise_a_jour_point_ATP(a,t,i);
			
			cpt++;
		}
		
		free(tour);
		tour = malloc(cpt*sizeof(int));
		
		for(j = 0; j < cpt; j++)
		{
			tour[j] = tourSuivant[j];
			//printf(" %d",tour[j]);
		}
		//printf("\n");
		free(tourSuivant);
	}
	
	t->idVainqueur = tour[0];
	
	Joueur_t* vain = get_joueur_pointeur_by_id(tabJoueur,tour[0]);
	
	vain->nombrePointATP -= vain->pointAnneePrecedente[t->numero];
	vain->pointAnneePrecedente[t->numero] = t->recompensePointATP;
	vain->nombrePointATP += t->recompensePointATP;
	
	if(vain->recordPointATP < vain->nombrePointATP)
	{
		vain->recordPointATP = vain->nombrePointATP;
	}
	
	vain->nbTournoisRemporte.tab[2] = vain->nbTournoisRemporte.tab[2] + 1;
	//printf(" VAINQUEUR %d\n",tour[0]);
	
	//affiche_match_important(t);
	free(tour);
}

/// \warning Les variable "enregistrer" et "liste" ne sont plus vraiment utile...
void masters1000(Joueur_t* tmp,ListeTournois_t* liste,Tournois_t* t,int** proba,Joueur_t* tabJoueur,int annee)
{
	int i,j;
	
	int alea;
	
	int* tour;
	int* tourSuivant;
	
	tour = malloc(64*sizeof(int));
	t->match = NULL;
	
	for(i = 0; i < 64; i++)
		tour[i] = -1;
		
	alea = rand()%16; // Nombre aleatoire entre 0 et 15
	
	tour[alea] = tmp[0].id;
	tour[32 + alea] = tmp[1].id;
	tour[16 + alea] = tmp[2].id;
	tour[48 + alea] = tmp[3].id;
	
	int ok = 0;
	
	for(i = 4; i < 64; i++)
	{
		ok = 0;
		alea = rand()%(64 - i) + 1;
		
		for(j = 0; j < 64; j++)
		{
			if(tour[j] == -1)
			{
				ok++;
			}
			if(ok == alea)
			{
				tour[j] = tmp[i].id;
				break;
			}
		}
	}
	
	//printf("Master 1000\n");
		
	for(i = 0; i < 6; i++)
	{
		int cpt = 0;
		
		tourSuivant = malloc(puiss(2 , 6 - i - 1)*sizeof(int));
		
		for(j = 0; j < puiss(2 , 6 - i); j = j + 2)
		{
			tourSuivant[cpt] = match(get_joueur_by_id(tabJoueur,tour[j]),get_joueur_by_id(tabJoueur,tour[j+1]),-1,t->terrain,proba,annee);
			
			Joueur_t* a = get_joueur_pointeur_by_id(tabJoueur,tour[j]);
			Joueur_t* b = get_joueur_pointeur_by_id(tabJoueur,tour[j+1]);
			
			if(tourSuivant[cpt] == a->id) // Si b perd
				mise_a_jour_point_ATP(b,t,i);
			else // Si a perd
				mise_a_jour_point_ATP(a,t,i);
			cpt++;
		}
		
		free(tour);
		tour = malloc(cpt*sizeof(int));
		
		for(j = 0; j < cpt; j++)
		{
			tour[j] = tourSuivant[j];
			// printf(" %d",tour[j]);
		}
		//printf("\n");
		free(tourSuivant);
	}
	
	t->idVainqueur = tour[0];
	
	Joueur_t* vain = get_joueur_pointeur_by_id(tabJoueur,tour[0]);
	
	vain->nombrePointATP -= vain->pointAnneePrecedente[t->numero];
	vain->pointAnneePrecedente[t->numero] = t->recompensePointATP;
	vain->nombrePointATP += t->recompensePointATP;
	
	if(vain->recordPointATP < vain->nombrePointATP)
	{
		vain->recordPointATP = vain->nombrePointATP;
	}
	vain->nbTournoisRemporte.tab[1] = vain->nbTournoisRemporte.tab[1] + 1;
	//printf(" VAINQUEUR %d\n",tour[0]);
	
	//affiche_match_important(t);
	free(tour);
}


void masters2000(Joueur_t* tabJoueur,ListeTournois_t* liste,Tournois_t* t,int** proba,int annee,int nomTournois)
{
	int i,j;
	int alea;
	
	int* tour;
	int* tourSuivant;
	
	tour = malloc(NB_JOUEUR*sizeof(int));
	t->match = NULL;
	
	for(i = 0; i < NB_JOUEUR; i++)
		tour[i] = -1;
	
	alea = rand()%8; // Nombre aleatoire entre 0 et 7
	tour[alea] = tabJoueur[0].id; // On met l'id du numero 1 mondial
	tour[64 + alea] = tabJoueur[1].id; // etc ...
	tour[32 + alea] = tabJoueur[2].id;
	tour[96 + alea] = tabJoueur[3].id;
	tour[16 + alea] = tabJoueur[4].id;
	tour[80 + alea] = tabJoueur[5].id;
	tour[48 + alea] = tabJoueur[6].id;
	tour[112 + alea] = tabJoueur[7].id;
	tour[8 + alea] = tabJoueur[8].id;
	tour[72 + alea] = tabJoueur[9].id;
	tour[40 + alea] = tabJoueur[10].id;
	tour[104 + alea] = tabJoueur[11].id;
	tour[24 + alea] = tabJoueur[12].id;
	tour[88 + alea] = tabJoueur[13].id;
	tour[56 + alea] = tabJoueur[14].id;
	tour[120 + alea] = tabJoueur[15].id;
	
	int ok = 0;
	
	for(i = 16; i < NB_JOUEUR; i++)
	{
		ok = 0;
		alea = rand()%(NB_JOUEUR - i) + 1;
		
		for(j = 0; j < NB_JOUEUR; j++)
		{
			if(tour[j] == -1)
			{
				ok++;
			}
			if(ok == alea)
			{
				tour[j] = tabJoueur[i].id;
				break;
			}
		}
	}
	
	int y = 0;
	while(1) // on se deplace jusqua trouver un tournois vide
	{
		if(liste[y].annee == -1) break;
		y++;
	}
	liste[y].annee = annee;
	
	//printf("Grand chelem\n");
	
	for(i = 0; i < 7; i++)
	{
		int cpt = 0;
		
		tourSuivant = malloc(puiss(2 , 7 - i - 1)*sizeof(int));
		
		for(j = 0; j < puiss(2 , 7 - i); j = j + 2)
		{
			tourSuivant[cpt] = match(get_joueur_by_id(tabJoueur,tour[j]),get_joueur_by_id(tabJoueur,tour[j+1]),nomTournois,t->terrain,proba,annee);
			
			Joueur_t* a = get_joueur_pointeur_by_id(tabJoueur,tour[j]);
			Joueur_t* b = get_joueur_pointeur_by_id(tabJoueur,tour[j+1]);
			
			if(a->type == 1 || b->type == 1) // Si il y a un grand joueur
			{
				int z = 0;
	
				while(1)
				{
					if(liste[y].match[z].estVide == 1) break;
					z++;
				}
				
				if(a->type == 1 && b->type == 1)
				{	
					if(tourSuivant[cpt] == a->id) // a gagne b perd
					{
						liste[y].match[z].idGagnant = a->id;
						liste[y].match[z].idPerdant = b->id;
						
						liste[y].match[z].tour = i;
						
						liste[y].match[z].estVide = 0;
						
						if(i == 6)
						{
							liste[y].idFinaliste = b->id;
						}
					}
					else // b gagne a perd
					{
						liste[y].match[z].idGagnant = b->id;
						liste[y].match[z].idPerdant = a->id;
					
						liste[y].match[z].tour = i;
						
						liste[y].match[z].estVide = 0;
						
						if(i == 6)
						{
							liste[y].idFinaliste = a->id;
						}
					}
				}
				else if(a->type == 1) // a est le grand joueur
				{
					if(tourSuivant[cpt] != a->id) // Si a perd 
					{
						liste[y].match[z].idGagnant = b->id;
						liste[y].match[z].idPerdant = a->id;
						
						liste[y].match[z].tour = i;
						
						liste[y].match[z].estVide = 0;
						
						if(i == 6)
						{
							liste[y].idFinaliste = a->id;
						}
					}
					if(tourSuivant[cpt] == a->id && i == 6) // Si a gagne en Finale
					{
						liste[y].match[z].idGagnant = a->id;
						liste[y].match[z].idPerdant = b->id;
						
						liste[y].match[z].tour = i;
						
						liste[y].match[z].estVide = 0;
						
						if(i == 6)
						{
							liste[y].idFinaliste = b->id;
						}
					}
				}
				else // b est le grand joueur
				{
					if(tourSuivant[cpt] != b->id) // Si b perd
					{
						liste[y].match[z].idGagnant = a->id;
						liste[y].match[z].idPerdant = b->id;
						
						liste[y].match[z].tour = i;
						
						liste[y].match[z].estVide = 0;
						
						if(i == 6)
						{
							liste[y].idFinaliste = b->id;
						}
					}
					if(tourSuivant[cpt] == b->id && i == 6) // Si b gagne en Finale
					{
						liste[y].match[z].idGagnant = b->id;
						liste[y].match[z].idPerdant = a->id;
						
						liste[y].match[z].tour = i;
						
						liste[y].match[z].estVide = 0;
						
						liste[y].idFinaliste = a->id;
					}
				}
			}
			if( i == 6 && a->type != 1 && b->type != 1)
			{
				int z = 0;
	
				while(1)
				{
					if(liste[y].match[z].estVide == 1) break;
					z++;
				}
				
				if(tourSuivant[cpt] != b->id) // Si b perd
				{
					liste[y].match[z].idGagnant = a->id;
					liste[y].match[z].idPerdant = b->id;
					
					liste[y].match[z].tour = i;
					
					liste[y].match[z].estVide = 0;
					
					liste[y].idFinaliste = b->id;
				}
				if(tourSuivant[cpt] != a->id) // Si a perd
				{
					liste[y].match[z].idGagnant = b->id;
					liste[y].match[z].idPerdant = a->id;
					
					liste[y].match[z].tour = i;
					
					liste[y].match[z].estVide = 0;
					
					liste[y].idFinaliste = a->id;
				}
			}
			
			if(tourSuivant[cpt] == a->id) // Si b perd
				mise_a_jour_point_ATP(b,t,i);
			else // Si a perd
				mise_a_jour_point_ATP(a,t,i);
			
			cpt++;
		} 
		
		free(tour);
		tour = malloc(cpt*sizeof(int));
		
		for(j = 0; j < cpt; j++)
		{
			tour[j] = tourSuivant[j];
			//printf(" %d",tour[j]);
		}
		//printf("\n");
		free(tourSuivant);
	}
	
	
	t->idVainqueur = tour[0];
	
	Joueur_t* vain = get_joueur_pointeur_by_id(tabJoueur,tour[0]);
	
	vain->nombrePointATP -= vain->pointAnneePrecedente[t->numero];
	vain->pointAnneePrecedente[t->numero] = t->recompensePointATP;
	vain->nombrePointATP += t->recompensePointATP;
	
	if(vain->recordPointATP < vain->nombrePointATP)
	{
		vain->recordPointATP = vain->nombrePointATP;
	}
	vain->nbTournoisRemporte.tab[0] = vain->nbTournoisRemporte.tab[0] + 1;
	//printf(" VAINQUEUR %d\n",tour[0]);
	
	//affiche_match_important(t);
	free(tour);
	ajouter_liste_tournois(t,liste,y);
}

void mise_a_jour_point_ATP(Joueur_t* perdant,Tournois_t* tournois,int tour)
{
	perdant->nombrePointATP -= perdant->pointAnneePrecedente[tournois->numero];
	perdant->pointAnneePrecedente[tournois->numero] = tournois->nombrePointATP[tour];
	perdant->nombrePointATP += tournois->nombrePointATP[tour];
	
	if(perdant->recordPointATP < perdant->nombrePointATP)
		perdant->recordPointATP = perdant->nombrePointATP;
}

void affiche_tableau_competition(int* t) // FONCTION DE DEBOGUAGE
{
	int i;
	
	for(i=0;i<NB_JOUEUR;i++)
	{
		if(i%2 == 0)
			printf("| ");
		printf("%d ",t[i]);
		
		if(i==32)
			printf("\n");
		if(i==64)
			printf("\n");
		if(i==96)
			printf("\n");
	}
}


/// \brief Prend 2 grands joueurs et retourne le vainqueur en fonction des probabilitees
int match_2_grd_joueur(Joueur_t j1,Joueur_t j2,int nomTournois,int typeTerrain,int** proba,int annee)
{
	int P = proba[j1.id-1][j2.id-1]; // proba que J1 gagne contre J2
	
	int alea = rand()%100; // Nombre aleatoire
	alea++;	
	
	// Si J1 est sur son terrain favori
	P = P + j1.terrainFavori[typeTerrain-1];
		
	// Si J2 est sur son terrain favori
	P = P - j2.terrainFavori[typeTerrain-1];
	
	// Si J1 est dans sa periode FORTE
	if( est_dans_periode_forte(j1,annee) )
		P = P + j1.probaPeriodeForte.tab[typeTerrain-1];
		
	// Si J2 est dans sa periode FORTE
	if( est_dans_periode_forte(j2,annee) )
		P = P - j2.probaPeriodeForte.tab[typeTerrain-1];
		
	// Si J1 est dans sa periode FAIBLE
	if( est_dans_periode_faible(j1,annee) )
		P = P - j1.probaPeriodeFaible.tab[typeTerrain-1];
		
	// Si J2 est dans sa periode FAIBLE
	if( est_dans_periode_faible(j2,annee) )
		P = P + j2.probaPeriodeFaible.tab[typeTerrain-1];
	
	if( nomTournois != -1 )
	{
		P = P + j1.tournoisFavori[nomTournois];
		
		if( j2.tournoisFavori < 0 )
			P = P + j2.tournoisFavori[nomTournois];
		else
			P = P - j2.tournoisFavori[nomTournois];
	}
	
	if( P >= 100 )
		return j1.id;
	else if( P <= 0)
		return j2.id;
	else
	{
		if( alea <= P )
			return j1.id;
		else
			return j2.id;
	}
}

/// \brief Prend 1 grand joueur et un joueur normal et retourne le vainqueur en fonction des probabilitees
int match_1_grd_joueur(Joueur_t j1,Joueur_t j2,int nomTournois,int typeTerrain,int annee) // J1 est le grand joueur
{
	int P;
	int alea = rand()%100; // Nombre aleatoire
	alea++;
	
	
	if( j2.rang > 20 ) // Si j1 affronte un hors TOP 20
		P = GRD_VS_NORM;
	else
		P = GRD_VS_TOP20;
	
	
	// Si J1 est dans sa periode FORTE
	if( est_dans_periode_forte(j1,annee) )
		P = P + PERIODE_FORT_PROBA;

	// Si J1 est dans sa periode FAIBLE
	if( est_dans_periode_faible(j1,annee) )
		P = P - PERIODE_FAIBLE_PROBA;
		
	// Si J1 est sur son terrain favori
	if( j1.terrainFavori[typeTerrain - 1] > 0 )
		P = P + 10;
	
	// Si J1 est sur son terrain faible
	if( (j1.terrainFavori[typeTerrain - 1] < 0) && (!est_dans_periode_forte(j1,annee)) )
		P = P - 5;
	
		
	if( nomTournois != -1 )
	{
		if( j1.tournoisFavori[nomTournois] > 0 )
			P = P + 10;
	}
		
	if( P >= 100 )
		return j1.id;
	else if( P <= 0 )
		return j2.id;
	else
	{
		if( alea <= P )
			return j1.id;
		else
			return j2.id;
	}
}

/// \brief Prend 2 joueurs normaux et retourne le vainqueur en fonction des probabilitees
int match_0_grd_joueur(Joueur_t j1,Joueur_t j2)
{	
	int alea = rand()%100; // Nombre aleatoire
	alea++;	
	
	if( j1.rang <= 20 && j2.rang <= 20 ) // Si les 2 joueurs sont bien classes
	{
		if( alea <= 50 )
			return j1.id;
		else
			return j2.id;
	}
	else // Si les 2 joueur sont hors top 20
	{
		if( j1.rang + 20 <= j2.rang ) // Si les joueurs on une difference de plus de 20 au rang
		{
			if( alea <= NORM_20_ECART )
				return j1.id;
			else
				return j2.id;
		}
		else
		{
			if( alea <= 50 )
				return j1.id;
			else
				return j2.id;
		}
	} 
}

/// \brief Fonction qui lance la bonne fonction de match en fonction des types de joueurs (grand ou normaux) (match_aux)
int match(Joueur_t j1,Joueur_t j2,int nomTournois,int typeTerrain,int** proba,int annee)
{
	int idGagnant = 1;
	int alea;
	
	if(j1.type == 1 && j2.type == 1) // Si les 2 joueurs sont des grands joueurs
	{
		return match_2_grd_joueur(j1,j2,nomTournois,typeTerrain,proba,annee);
	}
	else if(j1.type == 1 || j2.type == 1) // Si l'un des 2 joueurs est un grand joueur
	{
		if(j1.type == 1) // Si c'est J1 le grand joueur
		{
			return match_1_grd_joueur(j1,j2,nomTournois,typeTerrain,annee);
		}
		else // Si c'est J2 le grand joueur
		{
			return match_1_grd_joueur(j2,j1,nomTournois,typeTerrain,annee);
		}
	}
	else // 0 grand joueur
	{
		if(j1.rang > j2.rang)
		{
			return match_0_grd_joueur(j1,j2);
		}
		else
		{
			return match_0_grd_joueur(j2,j1);
		}
	}
	return idGagnant;
}


int puiss(int a,int b)
{
	int i;
	int resultat = 1;
	
	for(i = 0;i < b;i++)
	{
		resultat = resultat * a;
	}
	return resultat;
}

Joueur_t get_joueur_by_id(Joueur_t* t,int id)
{
	int i;
	
	for(i=0;i<NB_JOUEUR;i++)
	{
		if(t[i].id == id)
			return t[i];
	}
	
	printf("PROBLEME DANS GET JOUEUR BY ID\n");
	return t[0];
}


void ajouter_liste_tournois(Tournois_t* t1,ListeTournois_t* liste,int y)
{
	liste[y].type = GRAND_CHELEM;
	
	int year = t1->annee;
	liste[y].annee = year;
	
	char_init(&liste[y].nom);
	char_copier_contenu(&t1->nom,&liste[y].nom);
	
	int winner = t1->idVainqueur;
	liste[y].idVainqueur = winner;
}

Joueur_t* get_joueur_pointeur_by_id(Joueur_t* tabJoueur,int id)
{
	int i;
	
	for(i = 0; i < NB_JOUEUR; i++)
	{
		if(id == tabJoueur[i].id)
		{
			return &tabJoueur[i];
		}
	}
	
	printf("Probleme dans la fonction get joueur pointeur by id ===> %d\n",id);
	
	return &tabJoueur[0];
}


void trier_joueur(Joueur_t* tab)
{
	int i;
	int ind;
	
	int debut = 0;
	
	Joueur_t tmp;
	
	for(i = 0; i < NB_JOUEUR; i++)
	{
		ind = indice_meilleur_joueur(tab,debut);
		tmp = tab[i];
		tab[i] = tab[ind];
		tab[ind] = tmp;
		debut++;
		tab[i].rang = i;
	}
}

int indice_meilleur_joueur(Joueur_t* tab,int debut)
{
	int i;
	int max = -1;
	int indice = debut;
	
	for(i = debut; i < NB_JOUEUR; i++)
	{
		if(tab[i].nombrePointATP > max)
		{
			max = tab[i].nombrePointATP;
			indice = i;
		}
	}
	
	return indice;
}


void set_meilleur_rang(Joueur_t* tab)
{
	int i;
	
	for(i = 0; i < NB_JOUEUR; i++)
	{
		if(tab[i].meilleurRang > i)
		{
			tab[i].meilleurRang = i;
		}
	}
	
	for(i = 0; i < tab[i].tempsParClassement.tailleTab; i++) 
	{
		if(tab[i].type == 1)
		{
			tab[i].tempsParClassement.tab[i] = tab[i].tempsParClassement.tab[i] + 1;
		}
	}
}


int est_dans_periode_forte(Joueur_t a,int annee)
{
	int i;
	
	if(a.periodeForte.tailleTab < 2)
	{
		return 0;
	}
	
	for(i = 0; i < a.periodeForte.tailleTab; i = i + 2)
	{
		if((a.periodeForte.tab[i] <= annee) && (a.periodeForte.tab[i+1] >= annee))
		{
			return 1;
		}
	}
	
	return 0;
}


int est_dans_periode_faible(Joueur_t a,int annee)
{
	int i;
	
	if(a.periodeFaible.tailleTab < 2)
	{
		return 0;
	}
	
	for(i = 0; i < a.periodeFaible.tailleTab; i = i + 2)
	{
		if(a.periodeFaible.tab[i] <= annee && a.periodeFaible.tab[i+1] >= annee)
		{
			return 1;
		}
	}
	
	return 0;
}


void sauvegarder_liste_tournois(ListeTournois_t* liste,char* nomFichier)
{
	int i;
	
	for(i = 0; nomFichier[i] != '\0'; i++)
	{
		;
	}
	nomFichier[i] = '.';
	nomFichier[i+1] = 't';
	nomFichier[i+2] = 'x';
	nomFichier[i+3] = 't';
	nomFichier[i+4] = '\0';
	
	
	FILE* output = NULL;
	
	output = fopen(nomFichier,"w"); 
	
	fprintf(output,"--------------------\n");
	
	for(i = 0; i < 80; i++)
	{
		fprintf(output,"Tournois\n");
		
		int j;
		for(j = 0; j < liste[i].nom.tailleTab; j++)
			fprintf(output,"%c",liste[i].nom.tab[j]);
			
		fprintf(output,"  %d\n",liste[i].annee);
		fprintf(output,"Vainqueur %d Finaliste %d\n",liste[i].idVainqueur,liste[i].idFinaliste);
		
		int k;
		
		for(k = 0; liste[i].match[k].estVide != 1; k++)
		{
			if(k == 6) break;
		}
		
		fprintf(output,"Match_Important %d\n",k);
		
		j = 0;
		
		while(liste[i].match[j].estVide == 0)
		{
			fprintf(output,"gagnant %d perdant %d tour %d\n",liste[i].match[j].idGagnant,liste[i].match[j].idPerdant,liste[i].match[j].tour);
			j++;
			if(j == 6) break;
		}
		
		fprintf(output,"--------------------\n");
	}
}


int lire_fichier_liste_tournois(char* nomFichier,ListeTournois_t* liste)
{
	int i,j;
	int year = 1999;
	char buffer[50];
	char tmp[20];
	int idVainqueur,idFinaliste;
	int nbMatch,idGagnant,idPerdant,tour;
	
	FILE* fic = fopen(nomFichier,"r");
	
	if(fic == NULL)
	{
		printf("Le fichier %s n'existe pas\n",nomFichier);
		return -1;
	}
	
	for(i = 0; i < 50; i++)
	{
		buffer[i] = '\0';
	}
	
	for(i = 0; i < 80; i++)
	{
		if(i%4 == 0) year++;
		
		while(1)
		{
			fscanf(fic,"%s",buffer);
			if(buffer[0] == 'V' && buffer[1] == 'a' && buffer[2] == 'i') break;
		}
		
		fscanf(fic,"%d %s %d",&idVainqueur,tmp,&idFinaliste);
		
		liste[i].annee = year;
		liste[i].idVainqueur = idVainqueur;
		liste[i].idFinaliste = idFinaliste;
		
		if(i%4 == 0)
		{
			char_init(&liste[i].nom);
			char_remplir(&liste[i].nom,"Open D'Australie",16);
		}
		if(i%4 == 1)
		{
			char_init(&liste[i].nom);
			char_remplir(&liste[i].nom,"Roland Garros",13);
		}
		if(i%4 == 2)
		{
			char_init(&liste[i].nom);
			char_remplir(&liste[i].nom,"Wimbledon",9);
		}
		if(i%4 == 3)
		{
			char_init(&liste[i].nom);
			char_remplir(&liste[i].nom,"US OPEN",7);
		}
		
		
		  
		fscanf(fic,"%s %d",tmp,&nbMatch);
		
		int k;
		
		for(k = 0; k < nbMatch; k++)
		{
			fscanf(fic,"%s %d",tmp,&idGagnant);
			fscanf(fic,"%s %d",tmp,&idPerdant);
			fscanf(fic,"%s %d",tmp,&tour);
			
			liste[i].match[k].estVide = 0;
			liste[i].match[k].idGagnant = idGagnant;
			liste[i].match[k].idPerdant = idPerdant;
			liste[i].match[k].tour = tour;
		}
	}
	
	/*int df,aa,zz,ee,rr,tt;
	for(df = 0; df < 80; df++)
	{
		for(aa = 0; liste[df].match[aa].estVide == 0; aa++)
		{
			printf("gagnant %d  perdant %d    tour %d\n",liste[df].match[aa].idGagnant,liste[df].match[aa].idPerdant,liste[df].match[aa].tour);
		}
	}*/
	
	return 0;
}







