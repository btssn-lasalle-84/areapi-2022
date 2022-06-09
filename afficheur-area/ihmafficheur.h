#ifndef IHMAFFICHEUR_H
#define IHMAFFICHEUR_H

/**
 * @file ihmafficheur.h
 *
 * @brief Déclaration de la classe IHMAfficheur
 * @author Enzo LADRIERE
 * @version 1.0
 *
 */

#include <QtWidgets>
#include <QVector>
#include <QMediaPlayer>
#include <QTimer>

/**
 * @def PLEIN_ECRAN
 * @brief Pour le mode kiosque Télévision
 */
#define PLEIN_ECRAN
#define ECRAN_VEILLE
#define NOMBRE_SET_GAGNANT      3
#define ID_PARTIE_DOUBLE_1      0
#define ID_PARTIE_DOUBLE_2      1
#define SECONDE_EN_MILLISECONDE 1000

//#define TEST_RELATIONS

namespace Ui
{
class IHMAfficheur;
}

class ReceptionTrame;
class Rencontre;

/**
 * @class IHMAfficheur
 * @brief Déclaration de la classe IHMAfficheur
 * @details Cette classe s'occupe de l'affichage sur l'écran Télévision
 */
class IHMAfficheur : public QMainWindow
{
    Q_OBJECT

  private:
    Ui::IHMAfficheur* ui; //!< la fenêtre graphique associée à cette classe
    ReceptionTrame*   receptionTrame;
    Rencontre*        rencontre;
    QVector<QLabel*>  labelsJoueurA;
    QVector<QLabel*>  labelsJoueurB;
    QVector<QLabel*>  labelsJoueurC;
    QVector<QLabel*>  labelsJoueurD;
    QVector<QLabel*>  labelsJoueurW;
    QVector<QLabel*>  labelsJoueurX;
    QVector<QLabel*>  labelsJoueurY;
    QVector<QLabel*>  labelsJoueurZ;
    int               pointsTotalEquipeA;
    int               pointsTotalEquipeW;
    bool              connecteurMinuteurActive;
    QMediaPlayer      player;
    QTimer            minuteurSponsors;
    QVector<QLabel*>  labelsSponsors;

    void
    initialiserIHM();
    void initialiserReception();
    void initialiserEquipes(QString clubA, QString clubW);
    void initialiserEquipeA(QString    nomModule,
                            QByteArray NomJoueurA,
                            QByteArray PrenomJoueurA,
                            QByteArray NomJoueurB,
                            QByteArray PrenomJoueurB,
                            QByteArray NomJoueurC,
                            QByteArray PrenomJoueurC,
                            QByteArray NomJoueurD,
                            QByteArray PrenomJoueurD);
    void initialiserEquipeW(QString    nomModule,
                            QByteArray NomJoueurW,
                            QByteArray PrenomJoueurW,
                            QByteArray NomJoueurX,
                            QByteArray PrenomJoueurX,
                            QByteArray NomJoueurY,
                            QByteArray PrenomJoueurY,
                            QByteArray NomJoueurZ,
                            QByteArray PrenomJoueurZ);
    void initialiserJoueurA(QString nom, QString prenom);
    void initialiserJoueurB(QString nom, QString prenom);
    void initialiserJoueurC(QString nom, QString prenom);
    void initialiserJoueurD(QString nom, QString prenom);
    void initialiserJoueurW(QString nom, QString prenom);
    void initialiserJoueurX(QString nom, QString prenom);
    void initialiserJoueurY(QString nom, QString prenom);
    void initialiserJoueurZ(QString nom, QString prenom);
    void initialiserPartieSimple1(QString nomJoueurA,
                                  QString prenomJoueurA,
                                  QString nomJoueurW,
                                  QString prenomJoueurW);
    void initialiserPartieDouble1(QString nomJoueurA1,
                                  QString prenomJoueurA1,
                                  QString nomJoueurA2,
                                  QString prenomJoueurA2,
                                  QString nomJoueurW1,
                                  QString prenomJoueurW1,
                                  QString nomJoueurW2,
                                  QString prenomJoueurW2);
    void initialiserJoueurs(QByteArray NomJoueurA, QByteArray NomJoueurD, QByteArray PrenomJoueurC, QByteArray NomJoueurC, QByteArray PrenomJoueurB, QByteArray NomJoueurB, QByteArray PrenomJoueurY, QByteArray NomJoueurY, QByteArray PrenomJoueurX, QByteArray NomJoueurX, QByteArray PrenomJoueurZ, QByteArray PrenomJoueurW, QByteArray NomJoueurZ, QByteArray NomJoueurW, QByteArray PrenomJoueurA, QByteArray PrenomJoueurD);
    void initialiserSponsors();

  public:
    IHMAfficheur(QWidget* parent = nullptr);
    ~IHMAfficheur();

    enum Ecran
    {
        EcranVeille = 0,
        EcranRencontre
    };

    void renitialiserScorePartieGauche();
    void actualiserHistoriqueRencontre(int idPartie);
    void actualiserAffichageSetsPartieGauche(QByteArray idPartieScore);
    void cacherPartiesDoubles();
    void ReafficherPartiesDouble(QByteArray JoueurW1, QByteArray JoueurW2, QByteArray idPartieDouble, QByteArray JoueurA2, QByteArray JoueurA1);
    void associerSignalSlotRencontre();
    void actualiserSetPartie(QByteArray scoreJG, QByteArray idPartieScore, QByteArray scoreJD);
    void demmarerMinuteur(QByteArray etatPartie, QByteArray idPartieScore);
    void arreterMinuteur(unsigned int id);
    bool estConnecteurMinuteurActive();
    void connecterMinuteurPartieEtIHM(QByteArray idPartieScore);

    void afficherSponsors(int i);
    
public slots:
    void initialiserRencontre(QString    nomModule,
                              QByteArray NomClubA,
                              QByteArray NomClubW,
                              QByteArray NomJoueurA,
                              QByteArray PrenomJoueurA,
                              QByteArray NomJoueurB,
                              QByteArray PrenomJoueurB,
                              QByteArray NomJoueurC,
                              QByteArray PrenomJoueurC,
                              QByteArray NomJoueurD,
                              QByteArray PrenomJoueurD,
                              QByteArray NomJoueurW,
                              QByteArray PrenomJoueurW,
                              QByteArray NomJoueurX,
                              QByteArray PrenomJoueurX,
                              QByteArray NomJoueurY,
                              QByteArray PrenomJoueurY,
                              QByteArray NomJoueurZ,
                              QByteArray PrenomJoueurZ);

    void initialiserPartieSimple(QString    nomModule,
                                 QByteArray idPartie,
                                 QByteArray JoueurA,
                                 QByteArray ClassementJoueurA,
                                 QByteArray JoueurB,
                                 QByteArray ClassementJoueurW);

    void initialiserPartieDouble(QString    nomModule,
                                 QByteArray idPartieDouble,
                                 QByteArray JoueurA1,
                                 QByteArray ClassementA1,
                                 QByteArray JoueurA2,
                                 QByteArray ClassementA2,
                                 QByteArray JoueurW1,
                                 QByteArray ClassementW1,
                                 QByteArray JoueurW2,
                                 QByteArray ClassementW2);

    void initialiserScorePartie(QString    nomModule,
                                QByteArray idPartieScore,
                                QByteArray scoreJG,
                                QByteArray scoreJD,
                                QByteArray etatPartie,
                                QByteArray tempsMort,
                                QByteArray nbSetJG,
                                QByteArray nbSetJD,
                                QByteArray tourService,
                                QByteArray net);
    void actualiserTempsCadreGauche(int idPartieScore);
    void activerDeroulementSponsors();
};

#endif // IHMAFFICHEUR_H
