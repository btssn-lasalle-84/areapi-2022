#include "partie.h"

/**
 * @file partie.cpp
 *
 * @brief Définition de la classe Partie
 * @author
 * @version 1.0
 *
 */

Partie::Partie() :
    estDouble(0), nombreSet(0), scoreJoueurG(0), scoreJoueurD(0), setJoueurG(0),
    setJoueurD(0), nombreNET(0), pointConsecutif(0), joueurPointConsecutif(""), joueurs()
{
}

Partie::Partie(const Partie& partie) :
    nombreSet(partie.nombreSet), scoreJoueurG(partie.scoreJoueurG),
    scoreJoueurD(partie.scoreJoueurD), setJoueurG(partie.setJoueurG),
    setJoueurD(partie.setJoueurD), nombreNET(partie.nombreNET),
    pointConsecutif(partie.pointConsecutif),
    joueurPointConsecutif(partie.joueurPointConsecutif), joueurs(partie.joueurs)
{
}

Partie::~Partie()
{
}

Partie& Partie::operator=(const Partie& partie)
{
    if(this != &partie)
    {
        this->nombreSet             = partie.nombreSet;
        this->scoreJoueurG          = partie.scoreJoueurG;
        this->scoreJoueurD          = partie.scoreJoueurD;
        this->setJoueurG            = partie.setJoueurG;
        this->setJoueurD            = partie.setJoueurD;
        this->nombreNET             = partie.nombreNET;
        this->pointConsecutif       = partie.pointConsecutif;
        this->joueurPointConsecutif = partie.joueurPointConsecutif;
        this->joueurs               = partie.joueurs;
    }

    return *this;
}

bool Partie::aGagne() const
{
    return false;
}

bool Partie::estPointConsecutif() const
{
    return false;
}

void Partie::ajouterPointJoueurG()
{
    ++this->scoreJoueurG;
}

void Partie::ajouterPointJoueurD()
{
    ++this->scoreJoueurD;
}

void Partie::gagneSetJoueurG()
{
    ++this->setJoueurG;
}

void Partie::gagneSetJoueurD()
{
    ++this->setJoueurD;
}

void Partie::ajouterNET()
{
    ++this->nombreNET;
}

void Partie::rajouterPointConsecutif()
{
    ++this->pointConsecutif;
}

bool Partie::getEstDouble() const
{
    return this->estDouble;
}

unsigned int Partie::getNombreSet() const
{
    return this->nombreSet;
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

void Partie::setEstDouble(const bool &estDouble)
{
    this->estDouble = estDouble;
}

void Partie::setNombreSet(const unsigned int& nombreSet)
{
    this->nombreSet = nombreSet;
}

void Partie::setScoreJoueurG(const unsigned int& scoreJoueurG)
{
    this->scoreJoueurG = scoreJoueurG;
}

void Partie::setScoreJoueurD(const unsigned int& scoreJoueurD)
{
    this->scoreJoueurD = scoreJoueurD;
}

void Partie::setSetJoueurG(const unsigned int& setJoueurG)
{
    this->setJoueurG = setJoueurG;
}

void Partie::setSetJoueurD(const unsigned int& setJoueurD)
{
    this->setJoueurD = setJoueurD;
}

void Partie::setNombreNET(const unsigned int& nombreNET)
{
    this->nombreNET = nombreNET;
}

void Partie::setPointConsecutif(const unsigned int& pointConsecutif)
{
    this->pointConsecutif = pointConsecutif;
}

void Partie::setJoueurPointConsecutif(const QString& joueurPointConsecutif)
{
    this->joueurPointConsecutif = joueurPointConsecutif;
}
