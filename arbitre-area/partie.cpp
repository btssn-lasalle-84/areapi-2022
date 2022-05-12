#include "partie.h"

Partie::Partie() :
    idPartie(1), idRencontre(1), idJoueurA(1), idJoueurB(2), idJoueurW(3),
    idJoueurX(4), nbPointsSet(11), typePartie(1)
{
}
Partie::Partie(int idPartie,
               int idRencontre,
               int idJoueurA,
               int idJoueurB,
               int idJoueurW,
               int idJoueurX,
               int typePartie) :
    idPartie(idPartie),
    idRencontre(idRencontre), idJoueurA(idJoueurA), idJoueurB(idJoueurB),
    idJoueurW(idJoueurW), idJoueurX(idJoueurX), nbPointsSet(11),
    typePartie(typePartie)
{
}
Partie::~Partie()
{
}
int Partie::getIdPartie() const
{
    return this->idPartie;
}
int Partie::getIdRencontre() const
{
    return this->idRencontre;
}
int Partie::getIdJoueurA() const
{
    return this->idJoueurA;
}
int Partie::getIdJoueurB() const
{
    return this->idJoueurB;
}
int Partie::getIdJoueurW() const
{
    return this->idJoueurW;
}
int Partie::getIdJoueurX() const
{
    return this->idJoueurX;
}
int Partie::getNbPointsSet() const
{
    return this->nbPointsSet;
}
int Partie::getTypePartie() const
{
    return this->typePartie;
}
void Partie::setNbPointsSet(int nbPointsSet)
{
    this->nbPointsSet = nbPointsSet;
}
