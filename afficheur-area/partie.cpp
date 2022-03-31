#include "partie.h"

Partie::Partie() : nombreSet(0), scoreJoueurG(0), scoreJoueurD(0), setJoueurG(0), setJoueurD(0), nombreNET(0), pointConsecutif(0), joueurPointConsecutif("")
{

}

Partie::~Partie()
{
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

unsigned int getScoreJoueurG() const
{
    return 0;
}
unsigned int getScoreJoueurD() const
{
    return 0;
}

unsigned int getSetJoueurG() const
{
    return 0;
}

unsigned int getSetJoueurD() const
{
    return 0;
}

unsigned int getNombreNET() const
{
    return 0;
}

unsigned int getPointConsecutif() const
{
    return 0;
}

QString getJoueurPointConsecutif() const
{
    return "";
}

void setScoreJoueurG(unsigned int &scoreJoueurG)
{
}

void setScoreJoueurD(unsigned int &scoreJoueurD)
{
}

void setSetJoueurG(unsigned int &setJoueurG)
{
}

void setSetJoueurD(unsigned int &setJoueurD)
{
}

void setNombreNET(unsigned int &nombreNET)
{
}

void setPointConsecutif(unsigned int &pointConsecutif)
{
}

void setJoueurPointConsecutif(unsigned int &joueurPointConsecutif)
{
}
