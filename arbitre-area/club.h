#ifndef CLUB_H
#define CLUB_H

#include <QString>

class Club {
private:
  int idClub;
  QString nomClub;

public:
  Club();
  Club(int idClub, QString nomClub);
  ~Club();
  int getIdClub() const;
  QString getNomClub() const;
  void setIdClub(int idClub);
  void setnomClub(QString nomClub);
};

#endif // CLUB_H
