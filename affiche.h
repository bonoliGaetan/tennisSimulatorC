#include "fonction.h"

void affiche_nom_joueur(Joueur_t* j)
{
	int i;
	
	if(j->type == 0) 
	{
		printf("%d",j->id);
		return ;
	}
	else
	{
		for(i = 0; i < j->nom.tailleTab; i++)
			if(j->nom.tab[i] == ' ') { i++; break;}
		
		int k;
		
		for(k = i; k < j->nom.tailleTab; k++)
			printf("%c",j->nom.tab[k]);
	}
}


void affiche_liste_joueur(Joueur_t* tabJoueur)
{
	int i,j;
	printf("+---------------------------------------------------------------+\n");
	
	for(i=0;i<NB_JOUEUR;i++)
	{
		if(tabJoueur[i].type != 1)
		{
			for(j=0;j<tabJoueur[i].nom.tailleTab;j++)
			{
				printf("%c",tabJoueur[i].nom.tab[j]);
			}
			printf(" ID => %d ",tabJoueur[i].id);
			printf("     Point ATP => %d    Nombre de Point max = %d",tabJoueur[i].nombrePointATP,tabJoueur[i].recordPointATP);
			printf("   Rang max = %d\n\n",tabJoueur[i].meilleurRang+1);
			couleur("31");
			couleur("1");
			printf("        ATP 2000 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[0]);
			couleur("37");
			couleur("0");
			printf("        ATP 1000 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[1]);
			printf("        ATP 500 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[2]);
			printf("        ATP 250 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[3]);
			printf("+---------------------------------------------------------------+\n");
		}
	}
}

void affiche_liste_grand_joueur(Joueur_t* tabJoueur)
{
	int i,j;
	
	printf("\n\n+---------------------------------------------------------------+\n");
	
	for(i=0;i<NB_JOUEUR;i++)
	{
		if(tabJoueur[i].type == 1)
		{
			for(j=0;j<tabJoueur[i].nom.tailleTab;j++)
			{
				printf("%c",tabJoueur[i].nom.tab[j]);
			}
			couleur("32");
			couleur("1");
			printf("\n\n        Temps passe N 1 = %d",tabJoueur[i].tempsParClassement.tab[0]);
			couleur("0");
			couleur("33");
			printf("\n        Temps passe N 2 = %d",tabJoueur[i].tempsParClassement.tab[1]);
			couleur("37");
			printf("\n        Temps passe N 3 = %d",tabJoueur[i].tempsParClassement.tab[2]);
			printf("\n        Temps passe N 4 = %d",tabJoueur[i].tempsParClassement.tab[3]);
			printf("\n        Temps passe N 5 = %d",tabJoueur[i].tempsParClassement.tab[4]);
			printf("\n        Temps passe N 6 = %d\n\n",tabJoueur[i].tempsParClassement.tab[5]);
			printf(" ID => %d ",tabJoueur[i].id);
			printf("     Point ATP => %d    Nombre de Point max = %d",tabJoueur[i].nombrePointATP,tabJoueur[i].recordPointATP);
			printf("   Rang max = %d\n\n",tabJoueur[i].meilleurRang+1);
			couleur("31");
			couleur("1");
			printf("        ATP 2000 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[0]);
			couleur("37");
			couleur("0");
			printf("        ATP 1000 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[1]);
			printf("        ATP 500 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[2]);
			printf("        ATP 250 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[3]);
			printf("+---------------------------------------------------------------+\n");
		}
		
	}
	couleur("37");
}


void affiche_1_grand_joueur(Joueur_t* tabJoueur,int idJoueur)
{
	int i,j;
	
	Joueur_t joueur = get_joueur_by_id(tabJoueur,idJoueur);
	
	printf("\n\n+---------------------------------------------------------------+\n");
	
	if(joueur.type == 1)
	{
		for(j=0;j<joueur.nom.tailleTab;j++)
		{
			printf("%c",joueur.nom.tab[j]);
		}
		couleur("32");
		couleur("1");
		printf("\n\n        Temps passe N 1 = %d",joueur.tempsParClassement.tab[0]);
		couleur("0");
		couleur("33");
		printf("\n        Temps passe N 2 = %d",joueur.tempsParClassement.tab[1]);
		couleur("37");
		printf("\n        Temps passe N 3 = %d",joueur.tempsParClassement.tab[2]);
		printf("\n        Temps passe N 4 = %d",joueur.tempsParClassement.tab[3]);
		printf("\n        Temps passe N 5 = %d",joueur.tempsParClassement.tab[5]);
		printf("\n        Temps passe N 6 = %d\n\n",joueur.tempsParClassement.tab[6]);
		printf(" ID => %d ",joueur.id);
		printf("     Point ATP => %d    Nombre de Point max = %d",joueur.nombrePointATP,joueur.recordPointATP);
		printf("   Rang max = %d\n\n",joueur.meilleurRang+1);
		couleur("31");
			couleur("1");
			printf("        ATP 2000 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[0]);
			couleur("37");
			couleur("0");
			printf("        ATP 1000 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[1]);
			printf("        ATP 500 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[2]);
			printf("        ATP 250 gagne = %d\n",tabJoueur[i].nbTournoisRemporte.tab[3]);
		printf("+---------------------------------------------------------------+\n");
	}
		
	
	couleur("37");
} 


void affiche_tableau_parcour_GC_1_joueur(ListeTournois_t* liste, Joueur_t* tabJoueur, int  idJoueur)
{
	int cptTournois = 0;
	
	printf("\n");
	
	int cpt = 0,fin = 0;
	int nombre = 0;
	int annees = 1999;
	
	int tour = 0;
	
	Joueur_t* joueur = get_joueur_pointeur_by_id(tabJoueur,idJoueur);
	
	if(joueur->type == 0)
	{
		printf("Le Joueur selectionne est un petit Joueur\n Veuillez selectionne un grand Joueur\n");
		return ;
	}
	
	printf("\n                              ");
	
	couleur("1");
	affiche_nom_joueur(joueur);
	printf("\n\n");
	
	printf("\n           Open D'Australie      Roland Garros        Wimbledon           US OPEN     ");
	
	cptTournois = 0;
	
	
	while(cptTournois < 80)
	{
		if(nombre%4 == 0)
		{
			annees++;
			couleur("1");
			printf("\n>> %d : ",annees);
		}
		
		nombre++;
		
		int cptMatch = 0;
		
		if(liste[cptTournois].idVainqueur == joueur->id)
		{
			tour = 7;
		}
		else 
		{
			while(liste[cptTournois].match[cptMatch].estVide != 1)
			{
				if(liste[cptTournois].match[cptMatch].idPerdant == joueur->id)
				{
					tour = liste[cptTournois].match[cptMatch].tour;
					break;
				}
				
				cptMatch++;
				
				if(cptMatch == 6) break;
			}
		}
		
		if(tour < 3)   couleur("36");
		else if(tour == 3)   couleur("34");
		else if(tour == 4)   couleur("35");
		else if(tour == 5)   couleur("33");
		else if(tour == 6)   couleur("31");
		else   couleur("32");
		
		if(tour == 0)   printf("     Tour 1     ");
		else if(tour == 1)   printf("     Tour 2     ");
		else if(tour == 2)   printf("     Tour 3     ");
		else if(tour == 3)   printf("  1/8 de Finale ");
		else if(tour == 4)   printf(" Quart de Finale");
		else if(tour == 5)   printf("   Demi Finale  ");
		else if(tour == 6)   printf("     Finale     ");
		else   printf("    Vainqueur   ");
		
		printf("    ");
		couleur("37");
		cptTournois++;
	}
	

	printf("\n");
	couleur("0");
}


void affiche_tableau_parcour_en_GC_detaille(ListeTournois_t* liste,Joueur_t* tabJoueur, int idJoueur)
{
	int nombre = 0;
	int annees = 1999;
	int cpt = 0,i;
	
	int joueurUltime[4];
	int tourUltime[4];
	
	printf("           Open D'Australie         Roland Garros           Wimbledon               US OPEN\n");
	
	ListeTournois_t* tmp = liste; 
	
	Joueur_t* joueur = get_joueur_pointeur_by_id(tabJoueur,idJoueur);
	
	for(i = 0; i < 4; i++)
	{
		tourUltime[i] = 0;
		joueurUltime[i] = 0;
	}
	
	
	int cptTournois = 0;
	
	while(cptTournois < 80)
	{
		nombre++;
		int cptMatch = 0;
		
		
		if(liste[cptTournois].idVainqueur == joueur->id)
		{
			tourUltime[cpt] = 7;
			joueurUltime[cpt] = liste[cptTournois].idFinaliste;
		}
		else
		{
			while(liste[cptTournois].match[cptMatch].estVide == 0)
			{
				if(liste[cptTournois].match[cptMatch].idPerdant == joueur->id)
				{
					tourUltime[cpt] = liste[cptTournois].match[cptMatch].tour;
					joueurUltime[cpt] = liste[cptTournois].match[cptMatch].idGagnant;
					break;
				}
				cptMatch++;
			}
		}
		cpt++;
		
		if(nombre%4 == 0)
		{
			// afficher le tour et les joueurs ultime
			annees++;
			couleur("1");
			printf("\n>> %d :  ",annees);
			
			for(i = 0; i < 4; i++)
			{
				if(tourUltime[i] < 3)   couleur("36");
				else if(tourUltime[i] == 3)   couleur("34");
				else if(tourUltime[i] == 4)   couleur("35");
				else if(tourUltime[i] == 5)   couleur("33");
				else if(tourUltime[i] == 6)   couleur("31");
				else   couleur("32");
				
				if(tourUltime[i] == 0)   printf("     Tour 1     ");
				else if(tourUltime[i] == 1)   printf("     Tour 2     ");
				else if(tourUltime[i] == 2)   printf("     Tour 3     ");
				else if(tourUltime[i] == 3)   printf("  1/8 de Finale ");
				else if(tourUltime[i] == 4)   printf(" Quart de Finale");
				else if(tourUltime[i] == 5)   printf("   Demi Finale  ");
				else if(tourUltime[i] == 6)   printf("     Finale     ");
				else   printf("   Vainqueur    ");
				
				printf("       ");
			}
			printf("\n           ");
			couleur("37");
			
			for(i = 0; i < 4; i++)
			{
				
				Joueur_t* j = get_joueur_pointeur_by_id(tabJoueur,joueurUltime[i]);
				
				if(j->type == 1)
				{
					int i,k,borne1,borne2,tailleNom,vide;
					
					for(i = 0; i < j->nom.tailleTab; i++) 
						if(j->nom.tab[i] == ' ') { i++; break;}
					
					tailleNom = j->nom.tailleTab - i;
					
					vide = 16 - tailleNom;
					
					if(vide % 2 == 0) {borne1 = vide / 2; borne2 = vide / 2;}
					if(vide % 2 != 0) {borne1 = (vide / 2); borne2 = (vide / 2) + 1;}
					
					for(k = 0; k < borne1; k++) printf(" ");
					for(k = i; k < j->nom.tailleTab; k++) printf("%c",j->nom.tab[k]);
					for(k = 0; k < borne2; k++) printf(" ");
				}
				else
				{
					if(j->id < 100)   printf("       %d       ",j->id);
					else   printf("       %d      ",j->id);
				}
				printf("       ");
			}
			printf("\n");
			
			for(i = 0; i < 4; i++)
			{
				tourUltime[i] = 0;
				joueurUltime[i] = 0;
			}
			
			cpt = 0;
		}
		
		cptTournois++;
	}
	
	couleur("0");
	couleur("37");
	printf("\n");
}


void affiche_tableau_vainqueur_et_final_GC_1_joueur(ListeTournois_t* liste, Joueur_t* tabJoueur, int  idJoueur)
{
	int cpt = 0,fin = 0;
	int nombre = 0;
	int annees = 1999;
	
	Joueur_t* joueur = get_joueur_pointeur_by_id(tabJoueur,idJoueur);
	
	couleur("1");
	affiche_nom_joueur(joueur);
	printf("\n\n");
	couleur("0");
	
	int cptTournois = 0;
	
	while(cptTournois < 80)
	{
		if(nombre%4 == 0)
		{ 
			annees++;
			couleur("1");
			printf("\n>> %d : ",annees);
			couleur("0");
		}
		nombre++;
		
		if(liste[cptTournois].idVainqueur == joueur->id) // si le joueur en question a remporte le tournois
		{
			couleur("1");
			couleur("32");
			
			int k;
			for(k = 0; k < liste[cptTournois].nom.tailleTab; k++)
				printf("%c",liste[cptTournois].nom.tab[k]);
			
			couleur("37");
			cpt++;
				
			couleur("0");
			printf("    ");
		}
		else if(liste[cptTournois].idFinaliste == joueur->id) // Si le joueur est finaliste
		{
			fin++;
			couleur("1");
			couleur("31");
			int k;
			for(k = 0; k < liste[cptTournois].nom.tailleTab; k++)
				printf("%c",liste[cptTournois].nom.tab[k]);
			couleur("37");
			couleur("0");
			printf("    ");
		}
		else
		{
			if(liste[cptTournois].nom.tab[0] == 'O')
				printf("                    ");
			else if(liste[cptTournois].nom.tab[0] == 'R')
				printf("                 ");
			else if(liste[cptTournois].nom.tab[0] == 'W')
				printf("             ");	
		}
		
		cptTournois++;
	}
	printf("\n\n-------------------------------------------------------------");
	printf("\nVAINQUEUR => %d\nFINALE => %d\n",cpt,fin);
}



void affiche_tableau_vainqueur_GC_1_joueur(ListeTournois_t* liste, Joueur_t* tabJoueur, int  idJoueur)
{
	int cpt = 1;
	int oa = 0,rg = 0,wim = 0, us = 0;
	int nombre = 0;
	int annees = 1999;
	
	Joueur_t* joueur = get_joueur_pointeur_by_id(tabJoueur,idJoueur);
	
	printf("                              ");
	
	couleur("1");
	affiche_nom_joueur(joueur);
	printf("\n\n");
	couleur("0");
	
	int cptTournois = 0;
	
	while(cptTournois < 80)
	{
		
		if(nombre%4 == 0)
		{ 
			annees++;
			couleur("1");
			printf("\n>> %d : ",annees);
			couleur("0");
		}
		nombre++;
		
		if(liste[cptTournois].idVainqueur == joueur->id) // si le joueur en question a remporte le tournois
		{
			couleur("1");
			int k;
			
			if(liste[cptTournois].nom.tab[0] == 'O')
				couleur("36");
			else if(liste[cptTournois].nom.tab[0] == 'R')
				couleur("31");
			else if(liste[cptTournois].nom.tab[0] == 'W')
				couleur("32");
			else if(liste[cptTournois].nom.tab[0] == 'U')
				couleur("33");
			
			for(k = 0; k < liste[cptTournois].nom.tailleTab; k++)
				printf("%c",liste[cptTournois].nom.tab[k]);
			
			couleur("37");
			cpt++;
			// afficher le joueur ultime
			if(liste[cptTournois].nom.tab[0] == 'O')
				oa++;
			else if(liste[cptTournois].nom.tab[0] == 'R')
				rg++;
			else if(liste[cptTournois].nom.tab[0] == 'W')
				wim++;
			else
				us++;
				
			couleur("0");
			printf("    ");
		}
		else
		{
			if(liste[cptTournois].nom.tab[0] == 'O')
				printf("                    ");
			else if(liste[cptTournois].nom.tab[0] == 'R')
				printf("                 ");
			else if(liste[cptTournois].nom.tab[0] == 'W')
				printf("             ");	
		}
		
		cptTournois++;
	}
	printf("\nTOTAL => %d\n",cpt);
}



void affiche_liste_GC_vainqueur_1_joueur(ListeTournois_t* liste, Joueur_t* tabJoueur,int  idJoueur)
{
	int cpt = 1;
	
	int oa = 0,rg = 0,wim = 0, us = 0;
	
	Joueur_t* joueur = get_joueur_pointeur_by_id(tabJoueur,idJoueur);
	
	if(joueur->type == 0) 
	{
		printf("Choisissez un grand joueur\n");
		return ;
	}
	
	printf("-----\n");
	int i;
	for(i=0;i<joueur->nom.tailleTab;i++)
		printf("%c",joueur->nom.tab[i]);
	printf("\n\n");
	
	int nombre = 0;
	int cptTournois = 0;
	
	while(cptTournois < 80)
	{
		if(liste[cptTournois].idVainqueur == joueur->id) // si le joueur en question a remporte le tournois
		{
			couleur("1");
			couleur("32");
			printf(" =>[%d]<=  ",cpt);
			int k;
			
			if(liste[cptTournois].nom.tab[0] == 'O')
				couleur("36");
			else if(liste[cptTournois].nom.tab[0] == 'R')
				couleur("31");
			else if(liste[cptTournois].nom.tab[0] == 'W')
				couleur("32");
			else if(liste[cptTournois].nom.tab[0] == 'U')
				couleur("33");
			
			for(k = 0; k < liste[cptTournois].nom.tailleTab; k++)
				printf("%c",liste[cptTournois].nom.tab[k]);
			
			couleur("37");
			printf(" %d   ",liste[cptTournois].annee);
			cpt++;
			// afficher le joueur ultime
			if(liste[cptTournois].nom.tab[0] == 'O')
				oa++;
			else if(liste[cptTournois].nom.tab[0] == 'R')
				rg++;
			else if(liste[cptTournois].nom.tab[0] == 'W')
				wim++;
			else
				us++;
			
			Joueur_t j = get_joueur_by_id(tabJoueur,liste[cptTournois].idFinaliste);
			
			if(liste[cptTournois].nom.tab[0] == 'O')
				couleur("36");
			else if(liste[cptTournois].nom.tab[0] == 'R')
			{
				printf("   ");
				couleur("31");
			}
			else if(liste[cptTournois].nom.tab[0] == 'W')
			{
				printf("       ");
				couleur("32");
			}
			else if(liste[cptTournois].nom.tab[0] == 'U')
			{
				printf("         ");
				couleur("33");
			}
				
			if(j.type == 1) // si c'est un grand joueur
			{
				char_affiche(&j.nom,0);
			}
			else
				printf("%d",j.id);
			
			printf("   ");
			couleur("0");
			printf("\n");
		}
	
		cptTournois++;
	}
	
	printf("\n");
	couleur("1");
	couleur("33");
	printf(" Open D'Australie (%d)\n",oa);
	printf(" Rolland Garros (%d)\n",rg);
	printf(" Wimbledon (%d)\n",wim);
	printf(" US OPEN (%d)\n",us);
	couleur("0");
	couleur("37");
}


void affiche_nombre_GC_1_joueur(ListeTournois_t* liste,Joueur_t* tabJoueur,int idJoueur)
{
	int cpt = 0;
	
	int oa = 0,rg = 0,wim = 0, us = 0;
	
	Joueur_t* joueur = get_joueur_pointeur_by_id(tabJoueur,idJoueur);
	
	int i;
	
	for(i = 0; i < joueur->nom.tailleTab; i++)
	{
		printf("%c",joueur->nom.tab[i]);
	}printf("\n");
	
	int cptTournois = 0;
	
	while(cptTournois < 80)
	{
		if(liste[cptTournois].idVainqueur == joueur->id) // si le joueur en question a remporte le tournois
		{
			cpt++;
			
			if(liste[cptTournois].nom.tab[0] == 'O')
				oa++;
			else if(liste[cptTournois].nom.tab[0] == 'R')
				rg++;
			else if(liste[cptTournois].nom.tab[0] == 'W')
				wim++;
			else
				us++;
		}
		cptTournois++;
	}
	
	couleur("1");
	couleur("35");
	printf("Nombre de GC ==> %d <==\n",cpt);
	couleur("33");
	printf(" Open D'Australie (%d)\n",oa);
	printf(" Rolland Garros (%d)\n",rg);
	printf(" Wimbledon (%d)\n",wim);
	printf(" US OPEN (%d)\n",us);
	couleur("0");
	couleur("37");
	printf("\n");
}


void affiche_nombre_GC(ListeTournois_t* liste,Joueur_t* tabJoueur)
{
	int i;
	int k;
	
	printf("\n------------------------------\n");
	
	for(k = 0; k < NB_JOUEUR; k++)
	{
		if(tabJoueur[k].type == 1)
		{
			int cpt = 0;
			int oa = 0,rg = 0,wim = 0, us = 0;
			
			for(i = 0; i < tabJoueur[k].nom.tailleTab; i++)
			{
				printf("%c",tabJoueur[k].nom.tab[i]);
			}printf("\n");
			
			int cptTournois = 0;
			
			while(cptTournois < 80)
			{
				if(liste[cptTournois].idVainqueur == tabJoueur[k].id) // si le joueur en question a remporte le tournois
				{
					cpt++;
					
					if(liste[cptTournois].nom.tab[0] == 'O')
						oa++;
					else if(liste[cptTournois].nom.tab[0] == 'R')
						rg++;
					else if(liste[cptTournois].nom.tab[0] == 'W')
						wim++;
					else
						us++;
				}
				cptTournois++;
			}
			
			
			couleur("1");
			couleur("35");
			printf("Nombre de GC ==> %d <==\n",cpt);
			couleur("33");
			printf(" Open D'Australie (%d)\n",oa);
			printf(" Rolland Garros (%d)\n",rg);
			printf(" Wimbledon (%d)\n",wim);
			printf(" US OPEN (%d)\n",us);
			couleur("0");
			couleur("37");
			printf("\n------------------------------\n");
		}
	}
}


void menu(ListeTournois_t* listeTournois,Joueur_t* tabJoueur,int alt)
{
	char rep;
	
	while(1)
	{
		couleur("0");
		system("clear");
		
		printf(":::::::::::::::: **************** MENU **************** ::::::::::::::::\n\n");
		printf("\n");
		printf("   a => Parcour d'1 joueur en GC (sans nom)\n     z => Parcour d'1 joueur en GC (avec nom)\n");
		printf("   e => Finale & Victoire d'1 joueur en GC\n      r => Tableau des GC remporte par 1 joueur (nom des GC)\n\n\n");
		
		printf("   1 => Liste des GC remporte par un joueur (avec nom de l'adversaire ultime)\n");
		printf("   2 => Nombre de GC remporter par 1 joueur (liste composee de 4 GC)\n");
		printf("   3 => Nombre de GC remporter par tous les grands joueur (liste composee de 4 GC)\n");
		if(alt != 1) printf("   4 => La liste des stats d'1 Grand Joueur\n");
		if(alt != 1) printf("   5 => La liste des stats de tous les Grands Joueur\n\n");
		if(alt != 1) printf("   s,S => Sauvegarder la liste des tournois\n");
		printf(" Q q 0 => QUITTER\n\n");
		
		printf("\n\n   ================>  Choix : ");
		scanf(" %c",&rep);
		
		if(rep == '0' || rep == 'q' || rep == 'Q' ) break;
		
		int r;
		
		if(rep == 'a')
		{
			printf("\n\n   Selectionnez le grand Joueur :\n");
			printf("   1 => Federer   2 => Nadal   3 => Djokovic   4 => Wawrinka\n");
			printf("   5 => Murray   6 => Del Portro\n Reponse : ");
			scanf(" %d",&r);
			affiche_tableau_parcour_GC_1_joueur(listeTournois,tabJoueur,r);
			printf("\n");
		}
		if(rep == 'z')
		{
			printf("\n\nSelectionnez le grand Joueur :\n");
			printf(" 1 => Federer   2 => Nadal   3 => Djokovic   4 => Wawrinka\n");
			printf(" 5 => Murray   6 => Del Portro\n Reponse : ");
			scanf(" %d",&r);
			affiche_tableau_parcour_en_GC_detaille(listeTournois,tabJoueur,r);
			printf("\n");
		}
		if(rep == 'e')
		{
			printf("\n\nSelectionnez le grand Joueur :\n");
			printf(" 1 => Federer   2 => Nadal   3 => Djokovic   4 => Wawrinka\n");
			printf(" 5 => Murray   6 => Del Portro\n Reponse : ");
			scanf(" %d",&r);
			affiche_tableau_vainqueur_et_final_GC_1_joueur(listeTournois,tabJoueur,r);
			printf("\n");
		}
		if(rep == 'r')
		{
			printf("\n\nSelectionnez le grand Joueur :\n");
			printf(" 1 => Federer   2 => Nadal   3 => Djokovic   4 => Wawrinka\n");
			printf(" 5 => Murray   6 => Del Portro\n Reponse : ");
			scanf(" %d",&r);
			affiche_tableau_vainqueur_GC_1_joueur(listeTournois,tabJoueur,r);
			printf("\n");
		}
		if(rep == '1')
		{
			printf("\n\nSelectionnez le grand Joueur :\n");
			printf(" 1 => Federer   2 => Nadal   3 => Djokovic   4 => Wawrinka\n");
			printf(" 5 => Murray   6 => Del Portro\n Reponse : ");
			scanf(" %d",&r);
			affiche_liste_GC_vainqueur_1_joueur(listeTournois,tabJoueur,r);
			printf("\n");
		}
		if(rep == '2')
		{
			printf("\n\nSelectionnez le grand Joueur :\n");
			printf(" 1 => Federer   2 => Nadal   3 => Djokovic   4 => Wawrinka\n");
			printf(" 5 => Murray   6 => Del Portro\n Reponse : ");
			scanf(" %d",&r);
			affiche_nombre_GC_1_joueur(listeTournois,tabJoueur,r);
			printf("\n");
		}
		if(rep == '3')
		{
			affiche_nombre_GC(listeTournois,tabJoueur);
		}
		if(rep == '4' && alt == 0)
		{
			printf("\n\nSelectionnez le grand Joueur :\n");
			printf(" 1 => Federer   2 => Nadal   3 => Djokovic   4 => Wawrinka\n");
			printf(" 5 => Murray   6 => Del Portro\n Reponse : ");
			scanf(" %d",&r);
			affiche_1_grand_joueur(tabJoueur,r);
			printf("\n");
		}
		if(rep == '5' && alt == 0)
		{
			affiche_liste_grand_joueur(tabJoueur);
		}
		if((rep == 'S' || rep == 's') && alt == 0)
		{
			char nomFic[1000];
			printf("Quel nom donner a ce fichier ?\n");
			scanf(" %s",nomFic);
			sauvegarder_liste_tournois(listeTournois,nomFic);
		}
		
		couleur("0");
		printf("\n\n    Appuyer sur une touche pour continuer : ");
		scanf(" %c",&rep);
		
		if(rep == '0' || rep == 'q' || rep == 'Q')
			return ;
	}
}


