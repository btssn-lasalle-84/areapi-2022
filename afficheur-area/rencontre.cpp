#include "rencontre.h"

Rencontre::Rencontre() :
    equipeA(), equipeW(),parties()
{

}

Rencontre::Rencontre(const Rencontre& rencontre) :
    equipeA(rencontre.equipeA), equipeW(rencontre.equipeW), parties(rencontre.parties)
{
}

Rencontre::~Rencontre()
{
}

Rencontre& Rencontre::operator=(const Rencontre& rencontre)
{
    if(this != &rencontre)
    {
        this->equipeA = rencontre.equipeA;
        this->equipeW = rencontre.equipeW;
        this->parties = rencontre.parties;
    }

    return *this;
}
