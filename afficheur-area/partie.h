#ifndef PARTIE_H
#define PARTIE_H

/**
 * @file partie.h
 *
 * @brief Déclaration de la classe Partie
 * @author
 * @version 1.0
 *
 */

#include <QObject>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QTime>

#define POINT_GAGNANT    11
#define POINT_DIFFERENCE 2

#define ID_INDEFINI -1

class ReceptionTrame;
class Joueur;

/**
 * @class Partie
 * @brief Déclaration de la classe Partie
 * @details
 */
class Partie : public QObject
{
    Q_OBJECT
  private:
    int              id;
    bool             estDouble;             //!<
    unsigned int     nombreSet;             //!<
    unsigned int     scoreJoueurG;          //!<
    unsigned int     scoreJoueurD;          //!<
    unsigned int     setJoueurG;            //!<
    unsigned int     setJoueurD;            //!<
    unsigned int     nombreNET;             //!<
    unsigned int     pointConsecutif;       //!<
    QString          joueurPointConsecutif; //!<
    QVector<Joueur*> joueurs;               //!<
    QTime            tempsPartie;           //!<
    QTimer           minuteur;              //!<

  public:
    Partie();
    Partie(int id, bool estDouble, QString nomJoueurA1, QString prenomJoueurA1, QString nomJoueurW1, QString prenomJoueurW1, QString nomJoueurA2 = "", QString prenomJoueurA2 = "", QString nomJoueurW2 = "", QString prenomJoueurW2 = "");
    Partie(const Partie& partie);
    ~Partie();
    Partie& operator=(const Partie& partie);

    bool    aGagneSet() const;
    bool    estPointConsecutif() const;
    void    ajouterPointJoueurG();
    void    ajouterPointJoueurD();
    void    gagneSetJoueurG();
    void    gagneSetJoueurD();
    void    ajouterNET();
    void    rajouterPointConsecutif();
    QString definirAffichageSets(unsigned int setGagne);
    void    incrementeTemps();
    bool    estMinuteurDemarrer();

    bool         getEstDouble() const;
    unsigned int getNombreSet() const;
    unsigned int getScoreJoueurG() const;
    unsigned int getScoreJoueurD() const;
    unsigned int getSetJoueurG() const;
    unsigned int getSetJoueurD() const;
    unsigned int getNombreNET() const;
    unsigned int getPointConsecutif() const;
    QString      getJoueurPointConsecutif() const;
    QTime*       getTempsPartie();
    QTimer*      getMinuteur();

    void setEstDouble(const bool& estDouble);
    void setNombreSet(const unsigned int& nombreSet);
    void setScoreJoueurG(const unsigned int& scoreJoueurG);
    void setScoreJoueurD(const unsigned int& scoreJoueurD);
    void setSetJoueurG(const unsigned int& setJoueurG);
    void setSetJoueurD(const unsigned int& setJoueurD);
    void setNombreNET(const unsigned int& nombreNET);
    void setPointConsecutif(const unsigned int& pointConsecutif);
    void setJoueurPointConsecutif(const QString& joueurPointConsecutif);

  public slots:
    void incrementerTempsPartieCadreGauche();

  signals:
    void tempsPartieCadreGauche(int id);
};

#endif // PARTIE_H
