#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString>

class Joueur
{
private:
    int numeroLicence;
    int idClub;
    QString nom;
    QString prenom;

public:
    Joueur();
    Joueur(int numeroLicence, int idClub, QString nom, QString prenom);
    ~Joueur();
    int getNumeroLicence() const;
    int getIdClub() const;
    QString getNom() const;
    QString getPrenom() const;
    void setNom(QString nom);
    void setPrenom(QString prenom);
};

#endif // JOUEUR_H
