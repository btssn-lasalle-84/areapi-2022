#include "ihmafficheur.h"
#include "ui_ihmafficheur.h"
#include "receptiontrame.h"
#include <QDebug>

#ifdef TEST_RELATIONS
#include "rencontre.h"
#include "equipe.h"
#endif

/**
 * @file ihmafficheur.cpp
 *
 * @brief Définition de la classe IHMAfficheur
 * @author
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
    QMainWindow(parent), ui(new Ui::IHMAfficheur), labelsJoueurA()
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    receptionTrame = new ReceptionTrame(this);
    connect(receptionTrame,
            SIGNAL(recevoirTrameRencontre()),
            this,
            SLOT(initialiserRencontre()));

    connect(receptionTrame,
            SIGNAL(recevoirTrameSimple()),
            this,
            SLOT(initialiserPartieSimple()));

#ifdef TEST_RELATIONS
    // crée une rencontre et les deux équipes
    rencontre = new Rencontre("PPC Avignon", "PPC Sorgues");
    // ajoute des joueurs dans une équipe
    Equipe* equipeA = rencontre->getEquipeA();
    equipeA->ajouterJoueur("GUIDARELLI", "Nicolas", "A", 0);
    equipeA->ajouterJoueur("SAULNIER", "Christian", "B", 0);
    // ajoute des joueurs dans une équipe
    Equipe* equipeW = rencontre->getEquipeW();
    equipeW->ajouterJoueur("BEAUMONT", "Jérôme", "W", 0);
    equipeW->ajouterJoueur("RUIZ", "Jean-michel", "X", 0);
    // récupère les joueurs d'une équipe
    qDebug() << Q_FUNC_INFO << equipeA->getNbJoueurs();
    Joueur* unJoueur = nullptr;
    unJoueur         = equipeA->getJoueur("A");
    qDebug() << Q_FUNC_INFO << unJoueur->getPrenom() << unJoueur->getNom()
             << unJoueur->getLettre();
    unJoueur = equipeA->getJoueur("B");
    qDebug() << Q_FUNC_INFO << unJoueur->getPrenom() << unJoueur->getNom()
             << unJoueur->getLettre();
    // de l'autre l'équipe
    unJoueur = equipeW->getJoueur("W");
    qDebug() << Q_FUNC_INFO << unJoueur->getPrenom() << unJoueur->getNom()
             << unJoueur->getLettre();
    unJoueur = equipeW->getJoueur("X");
    qDebug() << Q_FUNC_INFO << unJoueur->getPrenom() << unJoueur->getNom()
             << unJoueur->getLettre();
#endif // TEST_RELATIONS

#ifdef PLEIN_ECRAN
    //showFullScreen();
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
#ifdef TEST_RELATIONS
    delete rencontre;
#endif
    qDebug() << Q_FUNC_INFO;
}

void IHMAfficheur::initialiserRencontre()
{
    qDebug() << Q_FUNC_INFO;
    initialiserEquipes();
    initialiserJoueurA();
    initialiserJoueurB();
    initialiserJoueurC();
    initialiserJoueurD();
    initialiserJoueurW();
    initialiserJoueurX();
    initialiserJoueurY();
    initialiserJoueurZ();
}

void IHMAfficheur::initialiserPartieSimple()
{
    qDebug() << Q_FUNC_INFO;
}

void IHMAfficheur::initialiserEquipes()
{
    ui->clubA->setText(receptionTrame->getDecoupageTrame(2));
    ui->clubW->setText(receptionTrame->getDecoupageTrame(3));
}

void IHMAfficheur::initialiserJoueurA()
{
    labelsJoueurA.push_back(ui->joueurPartie1CoteG);
    labelsJoueurA.push_back(ui->joueurPartie5CoteG);
    labelsJoueurA.push_back(ui->joueurPartie11CoteG);
    for(int i = 0; i < labelsJoueurA.size(); ++i)
    {
        labelsJoueurA[i]->setText(receptionTrame->getDecoupageTrame(4) + " " +receptionTrame->getDecoupageTrame(5));
    }
}

void IHMAfficheur::initialiserJoueurB()
{
    labelsJoueurB.push_back(ui->joueurPartie2CoteG);
    labelsJoueurB.push_back(ui->joueurPartie6CoteG);
    labelsJoueurB.push_back(ui->joueurPartie14CoteG);
    for(int i = 0; i < labelsJoueurB.size(); ++i)
    {
        labelsJoueurB[i]->setText(receptionTrame->getDecoupageTrame(6) + " " +receptionTrame->getDecoupageTrame(7));
    }
}

void IHMAfficheur::initialiserJoueurC()
{
    labelsJoueurC.push_back(ui->joueurPartie3CoteG);
    labelsJoueurC.push_back(ui->joueurPartie8CoteG);
    labelsJoueurC.push_back(ui->joueurPartie12CoteG);
    for(int i = 0; i < labelsJoueurC.size(); ++i)
    {
        labelsJoueurC[i]->setText(receptionTrame->getDecoupageTrame(8) + " " +receptionTrame->getDecoupageTrame(9));
    }
}

void IHMAfficheur::initialiserJoueurD()
{
    labelsJoueurD.push_back(ui->joueurPartie4CoteG);
    labelsJoueurD.push_back(ui->joueurPartie7CoteG);
    labelsJoueurD.push_back(ui->joueurPartie13CoteG);
    for(int i = 0; i < labelsJoueurD.size(); ++i)
    {
        labelsJoueurD[i]->setText(receptionTrame->getDecoupageTrame(10) + " " +receptionTrame->getDecoupageTrame(11));
    }
}

void IHMAfficheur::initialiserJoueurW()
{
    labelsJoueurW.push_back(ui->joueurPartie1CoteD);
    labelsJoueurW.push_back(ui->joueurPartie6CoteD);
    labelsJoueurW.push_back(ui->joueurPartie12CoteD);
    for(int i = 0; i < labelsJoueurW.size(); ++i)
    {
        labelsJoueurW[i]->setText(receptionTrame->getDecoupageTrame(12) + " " +receptionTrame->getDecoupageTrame(13));
    }
}

void IHMAfficheur::initialiserJoueurX()
{
    labelsJoueurX.push_back(ui->joueurPartie2CoteD);
    labelsJoueurX.push_back(ui->joueurPartie5CoteD);
    labelsJoueurX.push_back(ui->joueurPartie13CoteD);
    for(int i = 0; i < labelsJoueurX.size(); ++i)
    {
        labelsJoueurX[i]->setText(receptionTrame->getDecoupageTrame(14) + " " +receptionTrame->getDecoupageTrame(15));
    }
}

void IHMAfficheur::initialiserJoueurY()
{
    labelsJoueurY.push_back(ui->joueurPartie3CoteD);
    labelsJoueurY.push_back(ui->joueurPartie7CoteD);
    labelsJoueurY.push_back(ui->joueurPartie11CoteD);
    for(int i = 0; i < labelsJoueurY.size(); ++i)
    {
        labelsJoueurY[i]->setText(receptionTrame->getDecoupageTrame(16) + " " +receptionTrame->getDecoupageTrame(17));
    }
}

void IHMAfficheur::initialiserJoueurZ()
{
    labelsJoueurZ.push_back(ui->joueurPartie4CoteD);
    labelsJoueurZ.push_back(ui->joueurPartie8CoteD);
    labelsJoueurZ.push_back(ui->joueurPartie12CoteD);
    for(int i = 0; i < labelsJoueurZ.size(); ++i)
    {
        labelsJoueurZ[i]->setText(receptionTrame->getDecoupageTrame(18) + " " +receptionTrame->getDecoupageTrame(19));
    }
}
