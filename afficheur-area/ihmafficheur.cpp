#include "ihmafficheur.h"
#include "ui_ihmafficheur.h"
#include "receptiontrame.h"
#include "rencontre.h"
#include "equipe.h"
#include <QDebug>

/**
 * @file ihmafficheur.cpp
 *
 * @brief Définition de la classe IHMAfficheur
 * @author Enzo LADRIERE
 * @version 1.0
 *
 */

/**
 * @brief Constructeur de la classe IHMAfficheur
 *
 * @fn IHMAfficheur::IHMAfficheur
 * @param parent L'adresse de l'objet parent, si nullptr IHMAfficheur sera la
 * fenêtre principale de l'application
 */
IHMAfficheur::IHMAfficheur(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMAfficheur), receptionTrame(nullptr),
    rencontre(nullptr)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    initialiserIHM();
    initialiserReception();

#ifdef PLEIN_ECRAN
    // showFullScreen();
    showMaximized();
#endif // PLEIN_ECRAN
}

/**
 * @brief Destructeur de la classe IHMAfficheur
 *
 * @fn IHMAfficheur::~IHMAfficheur
 * @details Libère les ressources de l'application
 */
IHMAfficheur::~IHMAfficheur()
{
    delete ui;
    if(rencontre != nullptr)
        delete rencontre;
    qDebug() << Q_FUNC_INFO;
}

void IHMAfficheur::initialiserRencontre(QString    nomModule,
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
                                        QByteArray PrenomJoueurZ)
{
    qDebug() << Q_FUNC_INFO << nomModule;
    // crée une rencontre et les deux équipes
    if(rencontre == nullptr)
    {
        rencontre =
          new Rencontre(QString(NomClubA.data()), QString(NomClubW.data()));
        // ajoute les joueurs dans les équipes
        Equipe* equipeA = rencontre->getEquipeA();
        equipeA->ajouterJoueur(QString(NomJoueurA.data()),
                               QString(PrenomJoueurA.data()),
                               "A",
                               0);
        equipeA->ajouterJoueur(QString(NomJoueurB.data()),
                               QString(PrenomJoueurB.data()),
                               "B",
                               0);
        equipeA->ajouterJoueur(QString(NomJoueurC.data()),
                               QString(PrenomJoueurC.data()),
                               "C",
                               0);
        equipeA->ajouterJoueur(QString(NomJoueurD.data()),
                               QString(PrenomJoueurD.data()),
                               "D",
                               0);
        // Exemple : récupère les joueurs de l'équipe A
        /*
        qDebug() << Q_FUNC_INFO << equipeA->getNbJoueurs();
        Joueur* unJoueur = nullptr;
        unJoueur         = equipeA->getJoueur("A");
        qDebug() << Q_FUNC_INFO << unJoueur->getPrenom() << unJoueur->getNom()
                 << unJoueur->getLettre();
        */
        Equipe* equipeW = rencontre->getEquipeW();
        equipeW->ajouterJoueur(QString(NomJoueurW.data()),
                               QString(PrenomJoueurW.data()),
                               "W",
                               0);
        equipeW->ajouterJoueur(QString(NomJoueurX.data()),
                               QString(PrenomJoueurX.data()),
                               "X",
                               0);
        equipeW->ajouterJoueur(QString(NomJoueurY.data()),
                               QString(PrenomJoueurY.data()),
                               "Y",
                               0);
        equipeW->ajouterJoueur(QString(NomJoueurZ.data()),
                               QString(PrenomJoueurZ.data()),
                               "Z",
                               0);
        // Exemple : récupère les joueurs de l'équipe W
        /*
        qDebug() << Q_FUNC_INFO << equipeW->getNbJoueurs();
        unJoueur = equipeW->getJoueur("W");
        qDebug() << Q_FUNC_INFO << unJoueur->getPrenom() << unJoueur->getNom()
                 << unJoueur->getLettre();
        */
        initialiserEquipes(QString(NomClubA.data()), QString(NomClubW.data()));
        initialiserJoueurA(QString(NomJoueurA.data()),
                           QString(PrenomJoueurA.data()));
        initialiserJoueurB(QString(NomJoueurB.data()),
                           QString(PrenomJoueurB.data()));
        initialiserJoueurC(QString(NomJoueurC.data()),
                           QString(PrenomJoueurC.data()));
        initialiserJoueurD(QString(NomJoueurD.data()),
                           QString(PrenomJoueurD.data()));
        initialiserJoueurW(QString(NomJoueurW.data()),
                           QString(PrenomJoueurW.data()));
        initialiserJoueurX(QString(NomJoueurX.data()),
                           QString(PrenomJoueurX.data()));
        initialiserJoueurY(QString(NomJoueurY.data()),
                           QString(PrenomJoueurY.data()));
        initialiserJoueurZ(QString(NomJoueurZ.data()),
                           QString(PrenomJoueurZ.data()));
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Erreur rencontre en cours !";
    }
}

void IHMAfficheur::initialiserPartieSimple()
{
    qDebug() << Q_FUNC_INFO;
}

void IHMAfficheur::initialiserIHM()
{
    qDebug() << Q_FUNC_INFO;
}

void IHMAfficheur::initialiserReception()
{
    qDebug() << Q_FUNC_INFO;
    receptionTrame = new ReceptionTrame(this);

    connect(receptionTrame,
            SIGNAL(nouvelleTrameRencontre(QString,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray,
                                          QByteArray)),
            this,
            SLOT(initialiserRencontre(QString,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray,
                                      QByteArray)));
}

void IHMAfficheur::initialiserEquipes(QString clubA, QString clubW)
{
    qDebug() << Q_FUNC_INFO << clubA << clubW;
    ui->clubA->setText(clubA);
    ui->clubW->setText(clubW);
    /**
     * @todo Initialiser les parties DOUBLE dans l'IHM
     */
}

void IHMAfficheur::initialiserJoueurA(QString nom, QString prenom)
{
    labelsJoueurA.push_back(ui->joueurPartie1CoteG);
    labelsJoueurA.push_back(ui->joueurPartie5CoteG);
    labelsJoueurA.push_back(ui->joueurPartie11CoteG);
    qDebug() << Q_FUNC_INFO << nom << prenom;
    for(int i = 0; i < labelsJoueurA.size(); ++i)
    {
        labelsJoueurA[i]->setText(nom + " " + prenom);
    }
}

void IHMAfficheur::initialiserJoueurB(QString nom, QString prenom)
{
    labelsJoueurB.push_back(ui->joueurPartie2CoteG);
    labelsJoueurB.push_back(ui->joueurPartie6CoteG);
    labelsJoueurB.push_back(ui->joueurPartie14CoteG);
    qDebug() << Q_FUNC_INFO << nom << prenom;
    for(int i = 0; i < labelsJoueurB.size(); ++i)
    {
        labelsJoueurB[i]->setText(nom + " " + prenom);
    }
}

void IHMAfficheur::initialiserJoueurC(QString nom, QString prenom)
{
    labelsJoueurC.push_back(ui->joueurPartie3CoteG);
    labelsJoueurC.push_back(ui->joueurPartie8CoteG);
    labelsJoueurC.push_back(ui->joueurPartie12CoteG);
    qDebug() << Q_FUNC_INFO << nom << prenom;
    for(int i = 0; i < labelsJoueurC.size(); ++i)
    {
        labelsJoueurC[i]->setText(nom + " " + prenom);
    }
}

void IHMAfficheur::initialiserJoueurD(QString nom, QString prenom)
{
    labelsJoueurD.push_back(ui->joueurPartie4CoteG);
    labelsJoueurD.push_back(ui->joueurPartie7CoteG);
    labelsJoueurD.push_back(ui->joueurPartie13CoteG);
    qDebug() << Q_FUNC_INFO << nom << prenom;
    for(int i = 0; i < labelsJoueurD.size(); ++i)
    {
        labelsJoueurD[i]->setText(nom + " " + prenom);
    }
}

void IHMAfficheur::initialiserJoueurW(QString nom, QString prenom)
{
    labelsJoueurW.push_back(ui->joueurPartie1CoteD);
    labelsJoueurW.push_back(ui->joueurPartie6CoteD);
    labelsJoueurW.push_back(ui->joueurPartie12CoteD);
    qDebug() << Q_FUNC_INFO << nom << prenom;
    for(int i = 0; i < labelsJoueurW.size(); ++i)
    {
        labelsJoueurW[i]->setText(nom + " " + prenom);
    }
}

void IHMAfficheur::initialiserJoueurX(QString nom, QString prenom)
{
    labelsJoueurX.push_back(ui->joueurPartie2CoteD);
    labelsJoueurX.push_back(ui->joueurPartie5CoteD);
    labelsJoueurX.push_back(ui->joueurPartie13CoteD);
    qDebug() << Q_FUNC_INFO << nom << prenom;
    for(int i = 0; i < labelsJoueurX.size(); ++i)
    {
        labelsJoueurX[i]->setText(nom + " " + prenom);
    }
}

void IHMAfficheur::initialiserJoueurY(QString nom, QString prenom)
{
    labelsJoueurY.push_back(ui->joueurPartie3CoteD);
    labelsJoueurY.push_back(ui->joueurPartie7CoteD);
    labelsJoueurY.push_back(ui->joueurPartie11CoteD);
    qDebug() << Q_FUNC_INFO << nom << prenom;
    for(int i = 0; i < labelsJoueurY.size(); ++i)
    {
        labelsJoueurY[i]->setText(nom + " " + prenom);
    }
}

void IHMAfficheur::initialiserJoueurZ(QString nom, QString prenom)
{
    labelsJoueurZ.push_back(ui->joueurPartie4CoteD);
    labelsJoueurZ.push_back(ui->joueurPartie8CoteD);
    labelsJoueurZ.push_back(ui->joueurPartie14CoteD);
    qDebug() << Q_FUNC_INFO << nom << prenom;
    for(int i = 0; i < labelsJoueurZ.size(); ++i)
    {
        labelsJoueurZ[i]->setText(nom + " " + prenom);
    }
}
