#ifndef CLUB_H
#define CLUB_H

#include <QString>

class Club
{
private:
    int idClub;
    QString nomClub;

public:
    Club();
    Club(int idClub, QString nomClub);
    int getIdClub();
    QString nomClub();
    void setIdClub(int idClub);
    void setnomClub(QString nomClub);
};

#endif // CLUB_H
