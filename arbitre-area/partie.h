#ifndef PARTIE_H
#define PARTIE_H

#define NBSETGAGNANTS 3

class Partie
{
  private:
    int idPartie;
    int idRencontre;
    int idJoueurA;
    int idJoueurB;
    int idJoueurW;
    int idJoueurX;
    int nbPointsSet;
    int typePartie;

  public:
    Partie();
    Partie(int idPartie,
           int idRencontre,
           int idJoueurA,
           int idJoueurB,
           int idJoueurW,
           int idJoueurX,
           int typePartie);
    ~Partie();
    int  getIdPartie() const;
    int  getIdRencontre() const;
    int  getIdJoueurA() const;
    int  getIdJoueurB() const;
    int  getIdJoueurW() const;
    int  getIdJoueurX() const;
    int  getNbPointsSet() const;
    int  getTypePartie() const;
    void setNbPointsSet(int nbPointsSet);
};

#endif // PARTIE_H
