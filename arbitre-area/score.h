#ifndef SCORE_H
#define SCORE_H

class Score
{
  private:
    int idPartie;
    int nbSetClubA;
    int nbSetClubB;
    int pointsJoueurClubA;
    int pointsJoueurClubB;

  public:
    Score();
    Score(int idPartie,
          int nbSetClubA,
          int nbSetClubB,
          int pointsJoueurClubA,
          int pointsJoueurClubB);
    ~Score();
    int  getIdPartie() const;
    int  getNbSetClubA() const;
    int  getNbSetClubB() const;
    int  getPointJoueurClubA() const;
    int  getPointJoueurClubB() const;
    void setNbSetClubA(int nbSetClubA);
    void setNbSetClubB(int nbSetClubB);
    void setPointJoueurClubA(int pointsJoueurClubA);
    void setPointJoueurClubB(int pointsJoueurClubB);
};

#endif // SCORE_H
