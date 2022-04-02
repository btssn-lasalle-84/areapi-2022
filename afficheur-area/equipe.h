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

/**
 * @class Equipe
 * @brief Déclaration de la classe Equipe
 * @details
 */
class Equipe
{
  private:
    QString nom;

  public:
    Equipe();
    Equipe(const Equipe& equipe);
    ~Equipe();

    Equipe& operator=(const Equipe& equipe);

    QString getNom() const;
    void    setNom(const QString& nom);
};

#endif // EQUIPE_H
