#include "equipe.h"
#include <QDebug>

/**
 * @file equipe.cpp
 *
 * @brief Définition de la classe Equipe
 * @author
 * @version 1.0
 *
 */

Equipe::Equipe() : nom(""), joueurs()
{
    qDebug() << Q_FUNC_INFO;
}

Equipe::Equipe(QString nom) : nom(nom), joueurs()
{
    qDebug() << Q_FUNC_INFO << this << nom;
}

Equipe::Equipe(const Equipe& equipe) : nom(equipe.nom)
{
    qDebug() << Q_FUNC_INFO << nom;
}

Equipe::~Equipe()
{
    qDebug() << Q_FUNC_INFO << this;
}

Equipe& Equipe::operator=(const Equipe& equipe)
{
    if(this != &equipe)
    {
        this->nom     = equipe.nom;
        this->joueurs = equipe.joueurs;
    }

    return *this;
}

QString Equipe::getNom() const
{
    return this->nom;
}

void Equipe::setNom(const QString& nom)
{
    this->nom = nom;
}

void Equipe::ajouterJoueur(QString nom,
                           QString prenom,
                           QString lettre,
                           int     classement)
{
    joueurs.push_back(Joueur(nom, prenom, lettre, classement));
}

Joueur* Equipe::getJoueur(QString lettre)
{
    qDebug() << Q_FUNC_INFO << "lettre" << lettre;
    for(int i = 0; i < joueurs.size(); i++)
    {
        if(joueurs[i].getLettre() == lettre)
        {
            qDebug() << Q_FUNC_INFO << &(joueurs[i]) << joueurs[i].getPrenom()
                     << joueurs[i].getNom();
            return &(joueurs[i]);
        }
    }
    return nullptr;
}

int Equipe::getNbJoueurs() const
{
    return joueurs.size();
}
