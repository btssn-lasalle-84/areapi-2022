#ifndef EQUIPE_H
#define EQUIPE_H

/**
 * @file equipe.h
 *
 * @brief Déclaration de la classe Equipe
 * @author
 * @version 1.0
 *
 */

#include <QString>
#include <QVector>
#include "joueur.h"

/**
 * @class Equipe
 * @brief Déclaration de la classe Equipe
 * @details
 */
class Equipe
{
  private:
    QString nom;
    QVector<Joueur> joueurs;

  public:
    Equipe();
    Equipe(const Equipe& equipe);
    ~Equipe();

    Equipe& operator=(const Equipe& equipe);

    QString getNom() const;
    void    setNom(const QString& nom);
};

#endif // EQUIPE_H
