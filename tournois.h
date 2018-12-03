#define HERBE 1
#define TERRE_BATTUE 2
#define DUR 3
#define MOQUETTE 4

#define OA 1001
#define RG 1002
#define WIM 1003
#define US 1004

#include "joueur.h"

typedef struct MatchImportant_t
{
	/// \brief Pour savoir si le match actuel est vide (variable indiquant la fin du tableau de match)  
	/// 1 = VRAI    0 = FAUX
	int estVide;
	
	int idGagnant;
	int idPerdant;
	
	int tour;
	
}MatchImportant_t;


/// \brief Structure qui sert uniquement a faire fonctionner le programme (on enregistre rien)
typedef struct 
{
	int numero;
	int annee;
	
	/// \brief nom du tournois
	Tab_Char nom;
	
	int recompensePointATP;
	int terrain;
	
	/// \brief Contient le nombre de points gagner a tous les stades de la competition.
	int* nombrePointATP;
	int nombreTours;
	
	/// \warning Ne sert a rien... a supprimer
	int idVainqueur;
	
	MatchImportant_t* match;
	
}Tournois_t;


/// \brief Structure ou l'on enregistre tous les informations importantes
typedef struct
{
	/// \brief nombre de point ATP que fais gagner le tournois
	int type; 
	int annee;
	
	/// \brief nom du tournois
	Tab_Char nom;
	
	int idVainqueur;
	int idFinaliste;
	
	/// \brief liste des match important du tournois
	MatchImportant_t* match;
}ListeTournois_t;
