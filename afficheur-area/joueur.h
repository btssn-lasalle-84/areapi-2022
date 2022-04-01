#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString>

class Joueur
{
    private:
        QString nom;
        QString prenom;
        QString lettre;
        int classement;

    public:
        Joueur();
        ~Joueur();
        Joueur(const Joueur &joueur);

        Joueur & operator=(const Joueur & joueur);

        QString getNom() const;
        QString getprenom() const;
        QString getLettre() const;
        int getClassement() const;

        void setNom(const QString &nom);
        void setPrenom(const QString &prenom);
        void setLettre(const QString &lettre);
        void setClassement(const int &classement);
};

#endif // JOUEUR_H
