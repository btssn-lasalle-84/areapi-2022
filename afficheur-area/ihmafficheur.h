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

/**
 * @def PLEIN_ECRAN
 * @brief Pour le mode kiosque Télévision
 */
#define PLEIN_ECRAN

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
    QVector<QLabel*>  labelsJoueurA;
    QVector<QLabel*>  labelsJoueurB;
    QVector<QLabel*>  labelsJoueurC;
    QVector<QLabel*>  labelsJoueurD;
    QVector<QLabel*>  labelsJoueurW;
    QVector<QLabel*>  labelsJoueurX;
    QVector<QLabel*>  labelsJoueurY;
    QVector<QLabel*>  labelsJoueurZ;
    Rencontre*        rencontre;

    void initialiserIHM();
    void initialiserReception();
    void initialiserEquipes(QString clubA, QString clubW);
    void initialiserJoueurA(QString nom, QString prenom);
    void initialiserJoueurB(QString nom, QString prenom);
    void initialiserJoueurC(QString nom, QString prenom);
    void initialiserJoueurD(QString nom, QString prenom);
    void initialiserJoueurW(QString nom, QString prenom);
    void initialiserJoueurX(QString nom, QString prenom);
    void initialiserJoueurY(QString nom, QString prenom);
    void initialiserJoueurZ(QString nom, QString prenom);
    void initialiserPartieSimple1(QString nomJoueurA, QString prenomJoueurA, QString nomJoueurW, QString prenomJoueurW);
    void initialiserPartieSimple2(QString nomJoueurB, QString prenomJoueurB, QString nomJoueurX, QString prenomJoueurX);
    void initialiserPartieSimple3(QString nomJoueurC, QString prenomJoueurC, QString nomJoueurY, QString prenomJoueurY);
    void initialiserPartieSimple4(QString nomJoueurD, QString prenomJoueurD, QString nomJoueurZ, QString prenomJoueurZ);
    void initialiserPartieSimple5(QString nomJoueurA, QString prenomJoueurA, QString nomJoueurX, QString prenomJoueurX);
    void initialiserPartieSimple6(QString nomJoueurB, QString prenomJoueurB, QString nomJoueurW, QString prenomJoueurW);
    void initialiserPartieSimple7(QString nomJoueurD, QString prenomJoueurD, QString nomJoueurY, QString prenomJoueurY);
    void initialiserPartieSimple8(QString nomJoueurC, QString prenomJoueurC, QString nomJoueurZ, QString prenomJoueurZ);
    void initialiserPartieSimple9(QString nomJoueurA, QString prenomJoueurA, QString nomJoueurY, QString prenomJoueurY);
    void initialiserPartieSimple10(QString nomJoueurC, QString prenomJoueurC, QString nomJoueurW, QString prenomJoueurW);
    void initialiserPartieSimple11(QString nomJoueurD, QString prenomJoueurD, QString nomJoueurX, QString prenomJoueurX);
    void initialiserPartieSimple12(QString nomJoueurB, QString prenomJoueurB, QString nomJoueurZ, QString prenomJoueurZ);

  public:
    IHMAfficheur(QWidget* parent = nullptr);
    ~IHMAfficheur();

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

void initialiserPartieSimple(QString nomModule,
                                           QByteArray idPartie,
                                           QByteArray JoueurA,
                                           QByteArray ClassementJoueurA,
                                           QByteArray JoueurB,
                                           QByteArray ClassementJoueurW);
};

#endif // IHMAFFICHEUR_H
