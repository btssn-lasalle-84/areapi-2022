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
    QMainWindow(parent), ui(new Ui::IHMAfficheur)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    receptionTrame = new ReceptionTrame(this);

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
    showFullScreen();
    // showMaximized();
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
