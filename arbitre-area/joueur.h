#ifndef JOUEUR_H
#define JOUEUR_H

#include<QString>

class joueur
{
private:
    int nbLicence;
    int idClub;
    QString nom;
    QString prenom;

public:
    joueur();
    joueur(int nbLicence, int idClub, QString nom, QString prenom);
    int getNbLicence() const;
    int getIdClub() const;
    QString getNom() const;
    QString getPrenom() const;
    void setNom(QString nom);
    void setPrenom(QString prenom);
};

#endif // JOUEUR_H
