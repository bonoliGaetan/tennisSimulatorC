#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#include "int.h"

typedef struct
{
	char* tab;
	int tailleTab;
}Tab_Char;



/// --------------------------------------------------------------
/// \brief => LISTE DES FONCTIONS
/// --------------------------------------------------------------


/// \init => Doit etre appelle en 1er avant tout autre appelle de fonction
/// \malloc => Malloc le tab et met le tailleTab a la nouvelle valeur. Ne marche que si tab est NULL
/// \concatener_chaine_char => Fonction qui concatene 1 chaine et 1 tableau passe en parametre
/// \vider => Free tab et met tailleTab a 0
/// \remplir => Remplie tab avec une chaine de caractere passe en parametre
/// \copier_contenu Copie le contenue de "tab1" dans "tab2" et l'ecrase si il y a quelque chose dans "tab2"
/// \affiche Affiche le tableau passe en parametre et si sautLigne != 0, saute une ligne apres l'affichage
/// \comparer_chaine_char => Compare un tableau avec une chaine de caractere passe en parametre (0 = Faux       1 = Vrai)
/// \comparer_char_char Compare un tab avec un autre tab (0 = Faux       1 = Vrai)




/// --------------------------------------------------------------
/// \brief => IMPLEMENTATION FONCTIONS
/// --------------------------------------------------------------


void char_init(Tab_Char* tab)
{
	tab->tab = NULL;
	tab->tailleTab = 0;
}


void char_malloc(Tab_Char* tab,int taille)
{
	if(tab->tab != NULL)
	{
		if(DEBUG)
		{
			couleur("31");
			couleur("1");
			printf("Char malloc : La chaine n'est deja remplie...\n");
			couleur("0");
			couleur("37");
		}
		return ;
	}
	
	int i;
	tab->tailleTab = taille;
	tab->tab = malloc(taille*sizeof(char));
}


void char_concatener_chaine_char(Tab_Char* tab,char* chaine, int tailleChaine)
{
	int i;
	
	if(tab->tailleTab == 0)
	{
		if(DEBUG)
		{
			couleur("31");
			couleur("1");
			printf("Concatener Tab Char : La chaine est n'est pas encore remplie...\n");
			couleur("0");
			couleur("37");
		}
		return ;
	}
	else
	{
		int ancienneTaille = tab->tailleTab;
		char* tmp = malloc(tab->tailleTab * sizeof(char));
		
		for(i = 0; i < tab->tailleTab; i++) 
			tmp[i] = tab->tab[i];
		
		free(tab->tab);
		tab->tailleTab += tailleChaine;
		tab->tab = malloc(tab->tailleTab * sizeof(char));
		
		for(i = 0; i < ancienneTaille; i++)
			tab->tab[i] = tmp[i];
		
		free(tmp);
		int j = 0;
		for(i = ancienneTaille; i < tab->tailleTab; i++)
			tab->tab[i] = chaine[j++];
	}
	
	
	return ;
}


void char_vider(Tab_Char* tab)
{
	free(tab->tab);
	tab->tailleTab = 0;
}


void char_remplir(Tab_Char* tab, char* chaine, int tailleChaine)
{
	int i;
	
	if(tab->tailleTab != 0)
	{
		if(DEBUG)
		{
			couleur("31");
			couleur("1");
			printf("Remplir : La chaine est deja remplie...\n");
			couleur("0");
			couleur("37");
		}
		return ;
	}
	else
	{
		tab->tab = malloc(tailleChaine*sizeof(char));
		tab->tailleTab = tailleChaine;
		
		for(i = 0; i < tailleChaine; i++)
		{
			if(chaine[i] == '_')
				tab->tab[i] = ' ';
			else
				tab->tab[i] = chaine[i];
		}
	}
}


void char_copier_contenu(Tab_Char* tab1, Tab_Char* tab2)
{
	int i;
	
	if(tab1->tailleTab == 0)
	{
		if(DEBUG)
		{
			couleur("31");
			couleur("1");
			printf("Copier contenue : La chaine a copier est vide...\n");
			couleur("0");
			couleur("37");
		}
		return ;
	}
	
	
	if(tab2->tailleTab != 0)
	{
		free(tab2->tab);
	}
	
	tab2->tab = malloc(tab1->tailleTab * sizeof(char));
	tab2->tailleTab = tab1->tailleTab;
	
	for(i = 0; i < tab1->tailleTab; i++)
	{
		tab2->tab[i] = tab1->tab[i];
	}
}



void char_affiche(Tab_Char* tab, int sautLigne)
{
	int i;
	
	if(tab->tailleTab == 0)
	{
		if(DEBUG)
		{
			couleur("31");
			couleur("1");
			printf("Affiche : La chaine est vide...\n");
			couleur("0");
			couleur("37");
		}
		return ;
	}
	
	for(i = 0; i < tab->tailleTab; i++) printf("%c",tab->tab[i]);
	if(sautLigne) printf("\n");
}


int char_comparer_chaine_char(Tab_Char* tab, char* chaine, int tailleChaine)
{
	if(tab->tailleTab != tailleChaine)	return 0;
	
	int i;
	
	for(i = 0; i < tab->tailleTab; i++)
	{
		if(tab->tab[i] != chaine[i])	return 0;
	}
	return 1;
}


int char_comparer_char_char(Tab_Char* tab1, Tab_Char* tab2)
{
	if(tab1->tailleTab != tab2->tailleTab)	return 0;
	
	int i;
	
	for(i = 0; i < tab1->tailleTab; i++)
	{
		if(tab1->tab[i] != tab2->tab[i])	return 0;
	}
	return 1;
}









