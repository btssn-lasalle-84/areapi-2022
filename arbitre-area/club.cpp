#include "club.h"

Club::Club() : idClub(1), nomClub("")
{

}
Club(int idClub, QString nomClub) : idClub(idClub), nomClub(nomClub)
{

}

int getIdClub()
{
    return this->idClub;
}

QString nomClub()
{
    return this->nomClub;
}

void setIdClub(int idClub)
{
    this->idClub = idClub;
}
void setnomClub(QString nomClub)
{
    this->nomClub = nomClub;
}
