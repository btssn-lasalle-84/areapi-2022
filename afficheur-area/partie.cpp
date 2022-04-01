#include "partie.h"

Partie::Partie() : nombreSet(0), scoreJoueurG(0), scoreJoueurD(0), setJoueurG(0), setJoueurD(0), nombreNET(0), pointConsecutif(0), joueurPointConsecutif("")
{

}

Partie::~Partie()
{
}

Partie::Partie(const Partie &partie)
{
    *this = partie;
}

Partie & Partie::operator=(const Partie & partie)
{
    if(this != &partie)
    {
        this->nombreSet = partie.nombreSet;
        this->scoreJoueurG = partie.scoreJoueurG;
        this->scoreJoueurD = partie.scoreJoueurD;
        this->setJoueurG = partie.setJoueurG;
        this->setJoueurD = partie.setJoueurD;
        this->nombreNET = partie.nombreNET;
        this->pointConsecutif = partie.pointConsecutif;
        this->joueurPointConsecutif = partie.joueurPointConsecutif;
    }

    return *this;
}

bool Partie::aGagne() const
{
    return true;
}

bool Partie::estPointConsecutif() const
{
    return true;
}

void Partie::ajouterPointJoueurG()
{
}

void Partie::ajouterPointJoueurD()
{
}

void Partie::gagneSetJoueurG()
{
}

void Partie::gagneSetJoueurD()
{
}

void Partie::ajouterNET()
{
}

void Partie::rajouterPointConsecutif()
{
}

unsigned int Partie::getScoreJoueurG() const
{
    return this->scoreJoueurG;
}
unsigned int Partie::getScoreJoueurD() const
{
    return this->scoreJoueurD;
}

unsigned int Partie::getSetJoueurG() const
{
    return this->setJoueurG;
}

unsigned int Partie::getSetJoueurD() const
{
    return this->setJoueurD;
}

unsigned int Partie::getNombreNET() const
{
    return this->nombreNET;
}

unsigned int Partie::getPointConsecutif() const
{
    return this->pointConsecutif;
}

QString Partie::getJoueurPointConsecutif() const
{
    return this->joueurPointConsecutif;
}

void Partie::setScoreJoueurG(unsigned int &scoreJoueurG)
{
    this->scoreJoueurG = scoreJoueurG;
}

void Partie::setScoreJoueurD(unsigned int &scoreJoueurD)
{
    this->scoreJoueurD = scoreJoueurD;
}

void Partie::setSetJoueurG(unsigned int &setJoueurG)
{
    this->setJoueurG = setJoueurG;
}

void Partie::setSetJoueurD(unsigned int &setJoueurD)
{
    this->setJoueurD = setJoueurD;
}

void Partie::setNombreNET(unsigned int &nombreNET)
{
    this->nombreNET = nombreNET;
}

void Partie::setPointConsecutif(unsigned int &pointConsecutif)
{
    this->pointConsecutif = pointConsecutif;
}

void Partie::setJoueurPointConsecutif(QString &joueurPointConsecutif)
{
    this->joueurPointConsecutif = joueurPointConsecutif;
}
