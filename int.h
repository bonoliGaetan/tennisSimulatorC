#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define DEBUG 1

#define couleur(param) printf("\033[%sm",param)

/// \todo => TODO : faire une fonction "agrandir_tab" (qui n'ecrase pas)

typedef struct
{
	int* tab;
	int tailleTab;
}Tab_Int;


/// --------------------------------------------------------------
/// \brief => LISTE DES FONCTIONS
/// --------------------------------------------------------------

/// \init => Doit etre appelle en 1er avant tout autre appelle de fonction
/// \malloc => Malloc le tab et met le tailleTab a la nouvelle valeur. Ne marche que si tab est NULL
/// \remplir => Remplie tab avec un tableau de type int
/// \push_back => Met un nombre a la fin de tab
/// \init_a_une_valeur => Remplie toutes les cases de tab de la valeur passe en parametre
/// \vider => Free tab et met tailleTab a 0
/// \est_dans_tab => Dis si oui ou non la valeur passe en parametre est dans tab
/// \affiche => Affiche le tableau sans saut de ligne et si le parametre != 0, saute une ligne apres l'affichage




/// --------------------------------------------------------------
/// \brief => IMPLEMENTATION FONCTIONS
/// --------------------------------------------------------------


void int_init(Tab_Int* tab)
{
	/// \warning => On ne verifie pas si tab est != NULL
	tab->tailleTab = 0;
	tab->tab = NULL;
}

void int_malloc(Tab_Int* tab,int taille)
{
	if(tab->tab != NULL)
	{
		if(DEBUG)
		{
			couleur("31");
			couleur("1");
			printf("Int malloc : La chaine n'est deja remplie...\n");
			couleur("0");
			couleur("37");
		}
		return ;
	}
	
	int i;
	tab->tailleTab = taille;
	tab->tab = malloc(taille*sizeof(int));
}


void int_remplir(Tab_Int* tab, int* nb, int tailleNb)
{
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
		int i;
		tab->tab = malloc(tailleNb*sizeof(char));
		tab->tailleTab = tailleNb;
		
		for(i = 0; i < tailleNb; i++)
		{
			tab->tab[i] = nb[i];
		}
	}
}

void int_push_back(Tab_Int* tab, int nb)
{
	if(tab->tailleTab == 0)
	{
		tab->tab = malloc(sizeof(int));
		tab->tab[0] = nb;
		tab->tailleTab = 1;
		return ;
	}
	
	int i;
	int* tmp = malloc((tab->tailleTab) * sizeof(int));
	
	for(i = 0; i < tab->tailleTab; i++)
	{
		tmp[i] = tab->tab[i];
	}
	
	free(tab->tab);
	tab->tailleTab = tab->tailleTab + 1;
	
	tab->tab = malloc((tab->tailleTab) * sizeof(int));
	
	for(i = 0; i < tab->tailleTab - 1; i++)
	{
		tab->tab[i] = tmp[i];
	}
	tab->tab[i] = nb;
}

void int_init_a_une_valeur(Tab_Int* tab, int valeur)
{
	int i;
	
	if(tab->tailleTab == 0)
	{
		if(DEBUG)
		{
			couleur("31");
			couleur("1");
			printf("Remplir d'1 valeur : La chaine n'est pas encore remplie...\n");
			couleur("0");
			couleur("37");
		}
		return ;
	}
	
	for(i = 0; i < tab->tailleTab; i++)
	{
		tab->tab[i] = valeur;
	}
}

void int_vider(Tab_Int* tab)
{
	free(tab->tab);
	tab->tailleTab = 0;
}


int int_est_dans_tab(Tab_Int* tab, int nb)
{
	if(tab->tailleTab == 0)
	{
		if(DEBUG)
		{
			couleur("31");
			couleur("1");
			printf("Est dans tab : La chaine est vide...\n");
			couleur("0");
			couleur("37");
		}
		return 1;
	}
	
	int i;
	
	for(i = 0; i < tab->tailleTab; i++)
	{
		if(tab->tab[i] == nb)  return 1;
	}
	
	return 0;
}


void int_affiche(Tab_Int* tab, int sautLigne)
{
	if(tab->tailleTab == 0)
	{
		if(DEBUG)
		{
			couleur("31");
			couleur("1");
			printf("Int Affiche : La chaine est vide...\n");
			couleur("0");
			couleur("37");
		}
		return ;
	}
	
	int i;
	
	for(i = 0; i < tab->tailleTab; i++)
	{
		printf("%d ",tab->tab[i]);
	}
	
	if(sautLigne)
	{
		printf("\n");
	}
}






