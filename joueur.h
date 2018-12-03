#define GRD_VS_TOP20 85
#define GRD_VS_NORM 90
#define NORM_20_ECART 75

#define PERIODE_FORT_PROBA 10
#define PERIODE_FAIBLE_PROBA 8
#include "char.h"


typedef struct 
{
	/// \brief 0 = Joueur normal      1 = Grand Joueur
	int type;
	
	int id;
	int rang;
	int nombrePointATP;
	
	int* pointAnneePrecedente;
	
	int recordPointATP;
	int meilleurRang;
	
	/// \brief Nombre de tournois remporte (nombre de GC, nombre de M_1000 etc ...)
	Tab_Int nbTournoisRemporte;
	
	// Si c'est un grand joueur ...
	
	Tab_Char nom;
	
	/// \brief Temps passe a la place de n1, n2, n3 etc ...
	Tab_Int tempsParClassement;
	
	int terrainFavori[4];
	
	/// \brief Periode fortes/faibles (il peut y en avoir plusieur)
	Tab_Int periodeForte;
	Tab_Int periodeFaible;
	
	/// \brief Proba differente a chaque periode forte/faible
	Tab_Int probaPeriodeForte;
	Tab_Int probaPeriodeFaible;
	
	/// \brief Les GC favori de chaque grands joueurs
	int tournoisFavori[4];
}Joueur_t;

