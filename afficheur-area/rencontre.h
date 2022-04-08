#ifndef RENCONTRE_H
#define RENCONTRE_H

#include <QVector>
#include "equipe.h"
#include "partie.h"

class Rencontre
{
    private:
        Equipe equipeA;
        Equipe equipeW;
        QVector<Partie> parties;


    public:
        Rencontre();
        Rencontre(const Rencontre& rencontre);
        ~Rencontre();

        Rencontre& operator=(const Rencontre& rencontre);
};

#endif // RENCONTRE_H
