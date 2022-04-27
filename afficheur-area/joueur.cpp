#include "joueur.h"
#include <QDebug>

/**
 * @file joueur.cpp
 *
 * @brief Définition de la classe Joueur
 * @author
 * @version 1.0
 *
 */

Joueur::Joueur() : nom(""), prenom(""), lettre(""), classement(0)
{
    qDebug() << Q_FUNC_INFO;
}

Joueur::Joueur(QString nom, QString prenom, QString lettre, int classement) :
    nom(nom), prenom(prenom), lettre(lettre), classement(classement)
{
    qDebug() << Q_FUNC_INFO << prenom << nom << lettre << classement;
}

Joueur::Joueur(const Joueur& joueur) :
    nom(joueur.nom), prenom(joueur.prenom), lettre(joueur.lettre),
    classement(joueur.classement)
{
    qDebug() << Q_FUNC_INFO << prenom << nom << lettre << classement;
}

Joueur::~Joueur()
{
    qDebug() << Q_FUNC_INFO;
}

Joueur& Joueur::operator=(const Joueur& joueur)
{
    if(this != &joueur)
    {
        this->nom        = joueur.nom;
        this->prenom     = joueur.prenom;
        this->lettre     = joueur.lettre;
        this->classement = joueur.classement;
        qDebug() << Q_FUNC_INFO << prenom << nom << lettre << classement;
    }

    return *this;
}

QString Joueur::getNom() const
{
    return this->nom;
}

QString Joueur::getPrenom() const
{
    return this->prenom;
}

QString Joueur::getLettre() const
{
    return this->lettre;
}

int Joueur::getClassement() const
{
    return this->classement;
}

void Joueur::setNom(const QString& nom)
{
    this->nom = nom;
}

void Joueur::setPrenom(const QString& prenom)
{
    this->prenom = prenom;
}

void Joueur::setLettre(const QString& lettre)
{
    this->lettre = lettre;
}

void Joueur::setClassement(const int& classement)
{
    this->classement = classement;
}
