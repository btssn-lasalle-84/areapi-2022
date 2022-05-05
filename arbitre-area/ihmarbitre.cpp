#include "ihmarbitre.h"
#include "ui_ihmarbitre.h"
#include "communicationbluetooth.h"
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

    initialiserPageAccueil();

    communicationBluetooth = new CommunicationBluetooth(this);
    installerGestionEvenements();
    connect(communicationBluetooth,
            SIGNAL(netDetecte()),
            this,
            SLOT(declencherNet()));

    afficherEcran(IHMArbitre::Accueil);
    // afficherEcran(IHMArbitre::AccueilRencontre);

#ifdef PLEIN_ECRAN
    showFullScreen();
// showMaximized();
#endif

    communicationBluetooth->demarrerRecherche();
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

void IHMArbitre::demarrer()
{
    afficherEcran(Ecran::AccueilRencontre);
}

void IHMArbitre::afficherNetTrouve()
{
    afficherEtatBluetooth(ui->labelEtatModuleNet, Trouve);
    ui->pushButtonModuleNet->setText("Connecter");
}

void IHMArbitre::afficherEcranTrouve()
{
    afficherEtatBluetooth(ui->labelEtatModuleEcran, Trouve);
    ui->pushButtonModuleEcran->setText("Connecter");
}

void IHMArbitre::afficherScoreTrouve()
{
    afficherEtatBluetooth(ui->labelEtatModuleScore, Trouve);
    ui->pushButtonModuleScore->setText("Connecter");
}

void IHMArbitre::afficherConnexionNet()
{
    afficherEtatBluetooth(ui->labelEtatModuleNet, Connecte);
    ui->pushButtonModuleNet->setText("Déconnecter");
}

void IHMArbitre::afficherConnexionEcran()
{
    afficherEtatBluetooth(ui->labelEtatModuleEcran, Connecte);
    ui->pushButtonModuleEcran->setText("Déconnecter");
}

void IHMArbitre::afficherConnexionScore()
{
    afficherEtatBluetooth(ui->labelEtatModuleScore, Connecte);
    ui->pushButtonModuleScore->setText("Déconnecter");
}

void IHMArbitre::afficherDeconnexionNet()
{
    afficherEtatBluetooth(ui->labelEtatModuleNet, Trouve);
    ui->pushButtonModuleNet->setText("Connecter");
}

void IHMArbitre::afficherDeconnexionEcran()
{
    afficherEtatBluetooth(ui->labelEtatModuleEcran, Trouve);
    ui->pushButtonModuleEcran->setText("Connecter");
}

void IHMArbitre::afficherDeconnexionScore()
{
    afficherEtatBluetooth(ui->labelEtatModuleScore, Trouve);
    ui->pushButtonModuleScore->setText("Connecter");
}

void IHMArbitre::gererConnexionNet()
{
    if(ui->pushButtonModuleNet->text() == "Connecter")
    {
        communicationBluetooth->connecter(CommunicationBluetooth::Module::Net);
    }
    else if(ui->pushButtonModuleNet->text() == "Détecter")
    {
        communicationBluetooth->arreterRecherche();
        communicationBluetooth->demarrerRecherche();
    }
    else if(ui->pushButtonModuleNet->text() == "Déconnecter")
    {
        communicationBluetooth->deconnecter(
          CommunicationBluetooth::Module::Net);
    }
}
void IHMArbitre::gererConnexionEcran()
{
    if(ui->pushButtonModuleEcran->text() == "Connecter")
    {
        communicationBluetooth->connecter(
          CommunicationBluetooth::Module::Ecran);
    }
    else if(ui->pushButtonModuleEcran->text() == "Détecter")
    {
        communicationBluetooth->arreterRecherche();
        communicationBluetooth->demarrerRecherche();
    }
    else if(ui->pushButtonModuleEcran->text() == "Déconnecter")
    {
        communicationBluetooth->deconnecter(
          CommunicationBluetooth::Module::Ecran);
    }
}

void IHMArbitre::gererConnexionScore()
{
    if(ui->pushButtonModuleScore->text() == "Connecter")
    {
        communicationBluetooth->connecter(
          CommunicationBluetooth::Module::Score);
    }
    else if(ui->pushButtonModuleScore->text() == "Détecter")
    {
        communicationBluetooth->arreterRecherche();
        communicationBluetooth->demarrerRecherche();
    }
    else if(ui->pushButtonModuleScore->text() == "Déconnecter")
    {
        communicationBluetooth->deconnecter(
          CommunicationBluetooth::Module::Score);
    }
}
void IHMArbitre::installerGestionEvenements()
{
    connect(ui->pushButtonDemarrer,
            SIGNAL(clicked(bool)),
            this,
            SLOT(demarrer()));
    connect(communicationBluetooth,
            SIGNAL(moduleNetTrouve()),
            this,
            SLOT(afficherNetTrouve()));
    connect(ui->pushButtonModuleNet,
            SIGNAL(clicked(bool)),
            this,
            SLOT(gererConnexionNet()));
}

void IHMArbitre::declencherNet()
{
    qDebug() << Q_FUNC_INFO << "NET";
}

void IHMArbitre::initialiserPageAccueil()
{
    afficherEtatBluetooth(ui->labelEtatModuleEcran, Absent);
    ui->pushButtonModuleEcran->setText("Détecter");
    afficherEtatBluetooth(ui->labelEtatModuleNet, Absent);
    ui->pushButtonModuleNet->setText("Détecter");
    afficherEtatBluetooth(ui->labelEtatModuleScore, Absent);
    ui->pushButtonModuleScore->setText("Détecter");
}

void IHMArbitre::afficherEtatBluetooth(QLabel* module, EtatModule etat)
{
    QImage* image;
    QPixmap pixmap;

    image = new QImage();
    switch(etat)
    {
        case Absent:
            image->load(":/images/rouge.png");
            break;
        case Trouve:
            image->load(":/images/orange.png");
            break;
        case Connecte:
            image->load(":/images/vert.png");
            break;
        default:
            break;
    }

    pixmap = QPixmap::fromImage(*image);
    module->setPixmap(pixmap);

    delete image;
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
