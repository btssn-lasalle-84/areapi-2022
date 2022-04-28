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
    QVector<Equipe*> equipes;
    QVector<Partie>  parties;
    ReceptionTrame*  receptionTrame;

  public:
    Rencontre();
    Rencontre(QString nomEquipeA, QString nomEquipeW);
    ~Rencontre();

    Equipe* getEquipeA() const;
    Equipe* getEquipeW() const;

    QVector<Partie> getParties() const;

    void    ajouterPartieSimple();

    enum NomEquipe
    {
        EquipeA = 0,
        EquipeW,
        NbEquipes
    };
};

#endif // RENCONTRE_H
