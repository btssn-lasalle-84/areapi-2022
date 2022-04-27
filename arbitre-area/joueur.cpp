#include "joueur.h"

joueur::joueur() : nbLicence(0), idClub(0), nom(""), prenom("")
{

}

joueur::joueur(int nbLicence, int idClub, QString nom, QString prenom) : nbLicence(nbLicence), idClub(idClub), nom(nom), prenom(prenom)
{

}

int joueur::getNbLicence() const
{
    return this->nbLicence;
}

int joueur::getIdClub() const
{
    return this->idClub;
}

QString joueur::getNom() const
{
    return this->nom;
}

QString joueur::getPrenom() const
{
    return this->prenom;
}

void joueur::setNom(QString nom)
{
    this->nom = nom;
}

void joueur::setPrenom(QString prenom)
{
    this->prenom = prenom;
}
