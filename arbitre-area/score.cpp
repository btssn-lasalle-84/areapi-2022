#include "score.h"

Score::Score() :
    idPartie(1), nbSetClubA(0), nbSetClubB(0), pointsJoueurClubA(0),
    pointsJoueurClubB(0)
{
}

Score::Score(int idPartie,
             int nbSetClubA,
             int nbSetClubB,
             int pointsJoueurClubA,
             int pointsJoueurClubB) :
    idPartie(idPartie),
    nbSetClubA(nbSetClubA), nbSetClubB(nbSetClubB),
    pointsJoueurClubA(pointsJoueurClubA), pointsJoueurClubB(pointsJoueurClubB)
{
}
Score::~Score()
{
}
int Score::getIdPartie() const
{
    return this->idPartie;
}

int Score::getNbSetClubA() const
{
    return this->nbSetClubA;
}

int Score::getNbSetClubB() const
{
    return this->nbSetClubB;
}

int Score::getPointJoueurClubA() const
{
    return this->pointsJoueurClubA;
}

int Score::getPointJoueurClubB() const
{
    return this->pointsJoueurClubB;
}

void Score::setNbSetClubA(int nbSetClubA)
{
    this->nbSetClubA = nbSetClubA;
}

void Score::setNbSetClubB(int nbSetClubB)
{
    this->nbSetClubB = nbSetClubB;
}

void Score::setPointJoueurClubA(int pointsJoueurClubA)
{
    this->pointsJoueurClubA = pointsJoueurClubA;
}

void Score::setPointJoueurClubB(int pointsJoueurClubB)
{
    this->pointsJoueurClubB = pointsJoueurClubB;
}
