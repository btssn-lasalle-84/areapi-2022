#include "rencontre.h"

Rencontre::Rencontre() : idRencontre(0), idClubA(0), idClubB(0), estFinie(true), horodatage("20221223 00:00:00.00")
{

}

Rencontre::Rencontre(int idRencontre, int idClubA, int idClubB, bool estFinie, QString horodatage) : idRencontre(idRencontre), idClubA(idClubA), idClubB(idClubB), estFinie(estFinie), horodatage(horodatage)
{

}

Rencontre::~Rencontre()
{

}

int Rencontre::getIdRencontre() const
{
    return this->idRencontre;
}

int Rencontre::getIdClubA() const
{
    return this->idClubA;
}

int Rencontre::getIdClubB() const
{
    return this->idClubB;
}

bool Rencontre::getFinie() const
{
    return this->estFinie;
}

void Rencontre::setFinie(bool estFinie)
{
    this->estFinie = estFinie;
}

QString Rencontre::getHorodatage() const
{
    return this->horodatage;
}

void Rencontre::setHorodatage(QString horodatage)
{
    this->horodatage = horodatage;
}
