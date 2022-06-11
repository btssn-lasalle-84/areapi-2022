#ifndef RENCONTRE_H
#define RENCONTRE_H

/**
 * @file rencontre.h
 * @brief Déclaration de la classe Rencontre
 * @version
 * @author
 */

#include <QVector>
#include <QString>
#include "partie.h"

class Equipe;

/**
 * @class Rencontre
 * @brief Déclaration de la classe Rencontre
 * @details gère la rencontre entre deux équipes en plusieurs parties
 */
class Rencontre
{
  private:
    QVector<Equipe*>    equipes;
    QVector<Partie>     parties;
    int identifiantPartieGauche;

  public:
    Rencontre();
    Rencontre(QString nomEquipeA, QString nomEquipeW);
    ~Rencontre();

    Equipe*         getEquipeA() const;
    Equipe*         getEquipeW() const;
    QVector<Partie> getParties() const;
    Partie          getPartie(unsigned int cases) const;
    Partie*          getPointeurPartie(unsigned int cases);
    int             getIdentifiantPartieGauche();
    void            setIdentifiantPartieGauche(int identifiantPartieGauche);
    void            setPartiesSimple(QString nomJoueurA1, QString prenomJoueurA1,
                          QString nomJoueurW1, QString prenomJoueurW2);
    void            setPartiesDouble(QString nomJoueurA1, QString prenomJoueurA1,
                          QString nomJoueurA2, QString prenomJoueurA2,
                          QString nomJoueurW1, QString prenomJoueurW1,
                          QString nomJoueurW2, QString prenomJoueurW2);
    void            actualiserPartie(QByteArray idPartieScore, QByteArray scoreJG,
                          QByteArray scoreJD, QByteArray nbSetJG,
                          QByteArray nbSetJD, QByteArray net);

    enum NomEquipe
    {
        EquipeA = 0,
        EquipeW,
        NbEquipes
    };
};

#endif // RENCONTRE_H
