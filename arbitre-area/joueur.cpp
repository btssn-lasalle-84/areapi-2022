#include "joueur.h"

Joueur::Joueur() : numeroLicence(0), idClub(0), nom(""), prenom("")
{

}

Joueur::Joueur(int numeroLicence, int idClub, QString nom, QString prenom) : numeroLicence(numeroLicence), idClub(idClub), nom(nom), prenom(prenom)
{

}

Joueur::~Joueur()
{

}

int Joueur::getNumeroLicence() const
{
    return this->numeroLicence;
}

int Joueur::getIdClub() const
{
    return this->idClub;
}

QString Joueur::getNom() const
{
    return this->nom;
}

QString Joueur::getPrenom() const
{
    return this->prenom;
}

void Joueur::setNom(QString nom)
{
    this->nom = nom;
}

void Joueur::setPrenom(QString prenom)
{
    this->prenom = prenom;
}
