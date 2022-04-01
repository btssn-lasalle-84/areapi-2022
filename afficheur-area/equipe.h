#ifndef EQUIPE_H
#define EQUIPE_H

#include <QString>

class Equipe
{
    private:
        QString nom;

    public:
        Equipe();
        ~Equipe();
        Equipe(const Equipe &equipe);

        Equipe & operator=(const Equipe & equipe);

        QString getNom() const;

        void setNom(const QString &nom);
};

#endif // EQUIPE_H
