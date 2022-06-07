#include "rencontre.h"
#include "equipe.h"
#include <QDebug>

/**
 * @file rencontre.cpp
 * @brief Définition de la classe Rencontre
 * @version
 * @author
 */

Rencontre::Rencontre() :
    parties()
{
    qDebug() << Q_FUNC_INFO;
    equipes.push_back(new Equipe());
    equipes.push_back(new Equipe());
}

Rencontre::Rencontre(QString nomEquipeA, QString nomEquipeW) :
    parties()
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

QVector<Partie> Rencontre::getParties() const
{
    return this->parties;
}

Partie Rencontre::getPartie(unsigned int cases) const
{
    return parties[cases];
}

Partie* Rencontre::getPointeurPartie(unsigned int cases)
{
    return &(parties[cases]);
}

int Rencontre::getIdentifiantPartieGauche()
{
    return identifiantPartieGauche;
}

void Rencontre::setIdentifiantPartieGauche(int identifiantPartieGauche)
{
    identifiantPartieGauche = identifiantPartieGauche;
}

void Rencontre::setPartiesSimple(QString nomJoueurA1, QString prenomJoueurA1, QString nomJoueurW1, QString prenomJoueurW2)
{
    parties.push_back(Partie(parties.size(), false, nomJoueurA1, prenomJoueurA1, nomJoueurW1, prenomJoueurW2));
}

void Rencontre::setPartiesDouble(QString nomJoueurA1, QString prenomJoueurA1, QString nomJoueurA2, QString prenomJoueurA2, QString nomJoueurW1, QString prenomJoueurW1, QString nomJoueurW2, QString prenomJoueurW2)
{
    parties.push_back(Partie(parties.size(), true, nomJoueurA1, prenomJoueurA1, nomJoueurA2, prenomJoueurA2, nomJoueurW1, prenomJoueurW1, nomJoueurW2, prenomJoueurW2));
}

void Rencontre::actualiserPartie(QByteArray idPartieScore, QByteArray scoreJG, QByteArray scoreJD, QByteArray nbSetJG, QByteArray nbSetJD, QByteArray net)
{
    qDebug() << Q_FUNC_INFO << "";
    parties[idPartieScore.toUInt()].setSetJoueurG(nbSetJG.toUInt());
    parties[idPartieScore.toUInt()].setSetJoueurD(nbSetJD.toUInt());
    parties[idPartieScore.toUInt()].setScoreJoueurG(scoreJG.toUInt());
    parties[idPartieScore.toUInt()].setScoreJoueurD(scoreJD.toUInt());
    if(net.toUInt())
    {
        parties[idPartieScore.toUInt()].setNombreNET((parties[idPartieScore.toUInt()].getNombreNET() + 1));
    }
    if((nbSetJG.toUInt() + nbSetJD.toUInt()) != parties[idPartieScore.toUInt()].getNombreSet())
    {
        parties[idPartieScore.toUInt()].setNombreSet(nbSetJG.toUInt() + nbSetJD.toUInt());
        parties[idPartieScore.toUInt()].setNombreNET(0);
    }
}
