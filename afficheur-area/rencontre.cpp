#include "rencontre.h"
#include "equipe.h"
#include <QDebug>

/**
 * @file rencontre.cpp
 * @brief Définition de la classe Rencontre
 * @version
 * @author
 */

Rencontre::Rencontre() : equipes(), parties()
{
    qDebug() << Q_FUNC_INFO;
}

Rencontre::Rencontre(QString nomEquipeA, QString nomEquipeW)
{
    qDebug() << Q_FUNC_INFO << nomEquipeA << nomEquipeW;
    equipes.push_back(new Equipe(nomEquipeA));
    equipes.push_back(new Equipe(nomEquipeW));
}

Rencontre::~Rencontre()
{
    for(int i = 0; i < equipes.size(); i++)
    {
        if(equipes[i] != nullptr)
            delete equipes[i];
    }
    qDebug() << Q_FUNC_INFO;
}

Equipe* Rencontre::getEquipeA() const
{
    if(equipes.size() == Rencontre::NbEquipes)
    {
        qDebug() << Q_FUNC_INFO << equipes[NomEquipe::EquipeA]
                 << equipes[NomEquipe::EquipeA]->getNom();
        return equipes[NomEquipe::EquipeA];
    }
    return nullptr;
}

Equipe* Rencontre::getEquipeW() const
{
    if(equipes.size() == Rencontre::NbEquipes)
    {
        qDebug() << Q_FUNC_INFO << equipes[NomEquipe::EquipeW]
                 << equipes[NomEquipe::EquipeW]->getNom();
        return equipes[NomEquipe::EquipeW];
    }
    return nullptr;
}
