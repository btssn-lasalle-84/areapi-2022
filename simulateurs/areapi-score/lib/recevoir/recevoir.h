#ifndef __RECEVOIR_H__
#define __RECEVOIR_H__

#define DEBUG_RECEVOIR

//////////////////////////////////////////////////

#include <Arduino.h>

/*
MOBILE_AREA;2    ;ID_PARTIE;POINTS_JOUEUR_A;POINTS_JOUEUR_B;NB_MANCHES_GAGNEES_JOUEUR_A;NB_MANCHES_GAGNEES_JOUEUR_B\r\n

$AREA      ;SCORE;idPartie ;scoreJG        ;scoreJD        ;etatPartie;tempsMort;nbSetJG;nbSetJD;tourService;net\r\n

idPartie : int (identifiant de la partie)
scoreJG : int (joueur à gauche de l’arbitre)
scoreJD : int (joueur à droite de l’arbitre)
etatPartie : bool (1 si la partie est en cours sinon 0)
tempsMort : bool (1 si le temps mort est en cours sinon 0)
nbSetJ1 : int (max 5)
nbSetJ2 : int (max 5)
tourService : int (G ou D)
net : int (nombre de nets)

Exemple : $AREA;SCORE;1;2;5;1;0;1;2;G;5\r\n

*/

#define ENTETE_TRAME                "$AREA"
#define CHAMP_TYPE_TRAME            1
#define CHAMP_POSITION              2
#define ID_PARTIE                   2
#define POINTS_JOUEUR_A             3
#define POINTS_JOUEUR_B             4
#define ETAT_PARTIE                 5
#define TEMPS_MORT                  6
#define MANCHES_JOUEUR_A            7
#define MANCHES_JOUEUR_B            8

#define NB_CHAMPS_PARTIE_SIMPLE     7

enum TypeTrame
{
    INCONNUE = -1,
    SCORE = 2
};

enum PositionJoueur
{
    INVALIDE = -1,
    GAUCHE = 0,
    DROITE = 1
};

/*enum EtatPartie
{
    DEMARREE,
    TERMINEE,
    INCONNU
};*/

//////////////////////////////////////////////////

void initBluetooth(String nomIot);
void initAfficheurs();
bool lireTrame();
bool decoderTrame();
void gererScore(int idPartie, int pointJoueurA, int pointJoueurB, int mancheJoueurA, int mancheJoueurB);
void effacerScore();
String extraireChamp(unsigned int numeroChamp);
int compterParametres();
void envoyerTrameHeartBeat();

void testerAfficheurs();

#endif
