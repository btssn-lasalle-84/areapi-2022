#include "club.h"

Club::Club() : idClub(1), nomClub("")
{

}

Club::Club(int idClub, QString nomClub) : idClub(idClub), nomClub(nomClub)
{

}

Club::~Club()
{

}

int Club::getIdClub()
{
    return this->idClub;
}

QString Club::getNomClub()
{
    return this->nomClub;
}

void Club::setIdClub(int idClub)
{
    this->idClub = idClub;
}

void Club::setnomClub(QString nomClub)
{
    this->nomClub = nomClub;
}
