#ifndef RENCONTRE_H
#define RENCONTRE_H

#include <QString>

class Rencontre
{
private:
    int idRencontre;
    int idClubA;
    int idClubB;
    bool estFinie;
    QString horodatage;

public:
    Rencontre();
    Rencontre(int idRencontre, int idClubA, int idClubB, bool estFinie, QString horodatage);
    ~Rencontre();
    int getIdRencontre();
    int getIdClubA();
    int getIdClubB();
    bool getFinie();
    void setFinie(bool estFinie);
    QString getHorodatage();
    void setHorodatage(QString horodatage);
};

#endif // RENCONTRE_H
