#include "ihmarbitre.h"
#include "ui_ihmarbitre.h"
#include <QDebug>

/**
 * @file ihmarbitre.cpp
 *
 * @brief Définition de la classe IHMArbitre
 * @author
 * @version 1.0
 *
 */

/**
 * @brief Constructeur de la classe IHMArbitre
 *
 * @fn IHMArbitre::IHMArbitre
 * @param parent L'adresse de l'objet parent, si nullptr IHMArbitre sera la
 * fenêtre principale de l'application
 */
IHMArbitre::IHMArbitre(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMArbitre)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

#ifdef TEST_IHMARBITRE
    creerRaccourcisClavier();
#endif

    afficherEcran(IHMArbitre::AccueilRencontre);

#ifdef PLEIN_ECRAN
    showFullScreen();
// showMaximized();
#endif
}

/**
 * @brief Destructeur de la classe IHMArbitre
 *
 * @fn IHMArbitre::~IHMArbitre
 * @details Libère les ressources de l'application
 */
IHMArbitre::~IHMArbitre()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Méthode qui permet d'afficher un numéro d'écran de la pile
 * QStackedWidget
 *
 * @fn IHMArbitre::afficherEcran
 * @param ecran le numéro d'écran à afficher
 */
void IHMArbitre::afficherEcran(IHMArbitre::Ecran ecran)
{
    qDebug() << Q_FUNC_INFO << "ecran" << ecran;
    ui->ecrans->setCurrentIndex(ecran);
}

/**
 * @brief Méthode qui permet d'afficher l'écran suivant dans la pile
 * QStackedWidget
 *
 * @fn IHMArbitre::afficherEcranSuivant
 */
void IHMArbitre::afficherEcranSuivant()
{
    int ecranCourant = IHMArbitre::Ecran(ui->ecrans->currentIndex());
    int ecranSuivant = (ecranCourant + 1) % int(IHMArbitre::NbEcrans);
    afficherEcran(IHMArbitre::Ecran(ecranSuivant));
}

/**
 * @brief Méthode qui permet d'afficher l'écran précédent dans la pile
 * QStackedWidget
 *
 * @fn IHMArbitre::afficherEcranPrecedent
 */
void IHMArbitre::afficherEcranPrecedent()
{
    int ecranCourant   = ui->ecrans->currentIndex();
    int ecranPrecedent = (ecranCourant - 1) % int(IHMArbitre::NbEcrans);
    if(ecranPrecedent == -1)
        ecranPrecedent = int(IHMArbitre::NbEcrans) - 1;
    afficherEcran(IHMArbitre::Ecran(ecranPrecedent));
}

/**
 * @brief Méthode qui permet de fermer la fenêtre principale de l'application
 *
 * @fn IHMArbitre::fermerApplication
 */
void IHMArbitre::fermerApplication()
{
    this->close();
    qDebug() << Q_FUNC_INFO;
}

#ifdef TEST_IHMARBITRE
/**
 * @brief Méthode qui initialise les raccourcis clavier
 *
 * @fn IHMArbitre::creerRaccourcisClavier
 */
void IHMArbitre::creerRaccourcisClavier()
{
    // Ctrl-Q pour quitter
    QAction* quitter = new QAction(this);
    quitter->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    addAction(quitter);
    connect(quitter, SIGNAL(triggered()), this, SLOT(fermerApplication()));

    // Flèche droite pour écran suivant
    QAction* actionAllerDroite = new QAction(this);
    actionAllerDroite->setShortcut(QKeySequence(Qt::Key_Right));
    addAction(actionAllerDroite);
    connect(actionAllerDroite,
            SIGNAL(triggered()),
            this,
            SLOT(afficherEcranSuivant()));

    // Flèche gauche pour écran précédent
    QAction* actionAllerGauche = new QAction(this);
    actionAllerGauche->setShortcut(QKeySequence(Qt::Key_Left));
    addAction(actionAllerGauche);
    connect(actionAllerGauche,
            SIGNAL(triggered()),
            this,
            SLOT(afficherEcranPrecedent()));
}
#endif
