#ifndef JOUEUR_H
#define JOUEUR_H

/**
 * @file joueur.h
 *
 * @brief Déclaration de la classe Joueur
 * @author
 * @version 1.0
 *
 */

#include <QString>

/**
 * @class Joueur
 * @brief Déclaration de la classe Joueur
 * @details
 */
class Joueur
{
  private:
    QString nom;
    QString prenom;
    QString lettre;
    int     classement;

  public:
    Joueur();
    Joueur(QString nom, QString prenom, QString lettre, int classement);
    Joueur(const Joueur& joueur);
    ~Joueur();

    Joueur& operator=(const Joueur& joueur);

    QString getNom() const;
    QString getPrenom() const;
    QString getLettre() const;
    int     getClassement() const;

    void setNom(const QString& nom);
    void setPrenom(const QString& prenom);
    void setLettre(const QString& lettre);
    void setClassement(const int& classement);
};

#endif // JOUEUR_H
