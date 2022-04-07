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
};

#endif // RENCONTRE_H
