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
    initialiserCommunicationBluetooth();
    installerGestionEvenements();
    initialiserBDD();
    chargerRencontres();
    chargerClubs();

    // Pour les tests
    afficherEcran(IHMArbitre::Accueil);
    // afficherEcran(IHMArbitre::Rencontre);
    // afficherEcran(IHMArbitre::Partie);

#ifdef PLEIN_ECRAN
    showFullScreen();
// showMaximized();
#endif

    // communicationBluetooth->demarrerRecherche();
    communicationBluetooth->demarrerRechercheService();
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
    afficherEcran(Ecran::Rencontre);
}

void IHMArbitre::afficherNetTrouve()
{
    afficherEtatBluetooth(ui->labelEtatModuleNet, Trouve);
}

void IHMArbitre::afficherEcranTrouve()
{
    afficherEtatBluetooth(ui->labelEtatModuleEcran, Trouve);
}

void IHMArbitre::afficherScoreTrouve()
{
    afficherEtatBluetooth(ui->labelEtatModuleScore, Trouve);
}

void IHMArbitre::afficherConnexionNet()
{
    qDebug() << Q_FUNC_INFO;
    afficherEtatBluetooth(ui->labelEtatModuleNet, Connecte);
}

void IHMArbitre::afficherConnexionEcran()
{
    qDebug() << Q_FUNC_INFO;
    afficherEtatBluetooth(ui->labelEtatModuleEcran, Connecte);
}

void IHMArbitre::afficherConnexionScore()
{
    qDebug() << Q_FUNC_INFO;
    afficherEtatBluetooth(ui->labelEtatModuleScore, Connecte);
}

void IHMArbitre::afficherDeconnexionNet()
{
    afficherEtatBluetooth(ui->labelEtatModuleNet, Trouve);
}

void IHMArbitre::afficherDeconnexionEcran()
{
    afficherEtatBluetooth(ui->labelEtatModuleEcran, Trouve);
}

void IHMArbitre::afficherDeconnexionScore()
{
    afficherEtatBluetooth(ui->labelEtatModuleScore, Trouve);
}

void IHMArbitre::detecter()
{
    // communicationBluetooth->arreterRecherche();
    communicationBluetooth->arreterRechercheService();
    // communicationBluetooth->demarrerRecherche();
    communicationBluetooth->demarrerRechercheService();
}

void IHMArbitre::declencherNet(int nbNets)
{
    qDebug() << Q_FUNC_INFO << "NET" << nbNets;
}

void IHMArbitre::demarrerRencontreSimple()
{
    // aucune rencontre sélectionnée ?
    if(ui->comboBoxListeRencontres->currentIndex() == -1)
        return;
    qDebug() << Q_FUNC_INFO << ui->comboBoxListeRencontres->currentText();
    // aucune partie simple sélectionnée ?
    /**
     * @todo Compléter le test de vérification
     */
    if(ui->comboBoxListePartiesSimples->currentIndex() == -1)
        return;
    qDebug() << Q_FUNC_INFO << ui->comboBoxListePartiesSimples->currentText();
    QVector<int> sequenceJoueursEquipeA({ 0, 1, 2, 3, 0, 1, 3, 2, 0, 2, 3, 1 });
    QVector<int> sequenceJoueursEquipeW({ 0, 1, 2, 3, 1, 0, 2, 3, 2, 0, 1, 3 });

    ui->labelJoueurGauche->setText(
      joueursEquipeA
        .at(sequenceJoueursEquipeA.at(
          ui->comboBoxListePartiesSimples->currentIndex()))
        .at(0) +
      " " +
      joueursEquipeA
        .at(sequenceJoueursEquipeA.at(
          ui->comboBoxListePartiesSimples->currentIndex()))
        .at(1));

    ui->labelJoueurDroite->setText(
      joueursEquipeW
        .at(sequenceJoueursEquipeW.at(
          ui->comboBoxListePartiesSimples->currentIndex()))
        .at(0) +
      " " +
      joueursEquipeW
        .at(sequenceJoueursEquipeW.at(
          ui->comboBoxListePartiesSimples->currentIndex()))
        .at(1));
    afficherEcran(IHMArbitre::Partie);
}

void IHMArbitre::demarrerRencontreDouble()
{
    if(ui->comboBoxListeRencontres->currentIndex() == -1)
        return;
    qDebug() << Q_FUNC_INFO << ui->comboBoxListeRencontres->currentText();
    /**
     * @todo Compléter le test de vérification
     */
    ui->labelJoueurGauche->setText(ui->comboBoxListeJoueurA->currentText() +
                                   " / " +
                                   ui->comboBoxListeJoueurB->currentText());

    ui->labelJoueurDroite->setText(ui->comboBoxListeJoueurW->currentText() +
                                   " / " +
                                   ui->comboBoxListeJoueurX->currentText());
    afficherEcran(IHMArbitre::Partie);
}

// Méthodes privées

void IHMArbitre::initialiserCommunicationBluetooth()
{
    communicationBluetooth = new CommunicationBluetooth(this);
}

void IHMArbitre::initialiserBDD()
{
    bdd = BaseDeDonnees::getInstance("QSQLITE");
    if(bdd->estOuvert() == false)
    {
        bdd->ouvrir("areapi.sqlite");
        qDebug() << Q_FUNC_INFO << "Ouverture BDD" << bdd;
    }
}

void IHMArbitre::installerGestionEvenements()
{
    connect(ui->pushButtonDetecterModules,
            SIGNAL(clicked(bool)),
            this,
            SLOT(detecter()));
    connect(ui->pushButtonDemarrer,
            SIGNAL(clicked(bool)),
            this,
            SLOT(demarrer()));
    connect(communicationBluetooth,
            SIGNAL(moduleEcranTrouve()),
            this,
            SLOT(afficherEcranTrouve()));
    connect(communicationBluetooth,
            SIGNAL(moduleNetTrouve()),
            this,
            SLOT(afficherNetTrouve()));
    connect(communicationBluetooth,
            SIGNAL(moduleScoreTrouve()),
            this,
            SLOT(afficherScoreTrouve()));
    connect(communicationBluetooth,
            SIGNAL(moduleEcranConnecte()),
            this,
            SLOT(afficherConnexionEcran()));
    connect(communicationBluetooth,
            SIGNAL(moduleNetConnecte()),
            this,
            SLOT(afficherConnexionNet()));
    connect(communicationBluetooth,
            SIGNAL(moduleScoreConnecte()),
            this,
            SLOT(afficherConnexionScore()));
    connect(communicationBluetooth,
            SIGNAL(moduleEcranDeconnecte()),
            this,
            SLOT(afficherDeconnexionEcran()));
    connect(communicationBluetooth,
            SIGNAL(moduleNetDeconnecte()),
            this,
            SLOT(afficherDeconnexionNet()));
    connect(communicationBluetooth,
            SIGNAL(moduleScoreDeconnecte()),
            this,
            SLOT(afficherDeconnexionScore()));
    connect(communicationBluetooth,
            SIGNAL(netDetecte(int)),
            this,
            SLOT(declencherNet(int)));
    connect(ui->buttonSelectionnerRencontreSimple,
            SIGNAL(clicked(bool)),
            this,
            SLOT(demarrerRencontreSimple()));
    connect(ui->buttonSelectionnerRencontreDouble,
            SIGNAL(clicked(bool)),
            this,
            SLOT(demarrerRencontreDouble()));
    connect(ui->comboBoxListeRencontres,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(chargerPartiesSimples()));
    connect(ui->comboBoxListeRencontres,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(chargerPartiesDoubles()));
    connect(ui->buttonSelectionnerRencontre,
            SIGNAL(clicked(bool)),
            this,
            SLOT(demarrerRencontre()));
    connect(ui->ButtonEchangerJoueur,
            SIGNAL(clicked(bool)),
            this,
            SLOT(echangerJoueur()));
    connect(ui->buttonDebutFinPartie,
            SIGNAL(clicked(bool)),
            this,
            SLOT(demarrerPartie()));
    connect(ui->buttonAjoutPointJG,
            SIGNAL(clicked(bool)),
            this,
            SLOT(AjoutPointG()));
    connect(ui->buttonAjoutPointJD,
            SIGNAL(clicked(bool)),
            this,
            SLOT(AjoutPointD()));
    connect(ui->buttonRetraitPointJG,
            SIGNAL(clicked(bool)),
            this,
            SLOT(RetraitPointG()));
    connect(ui->buttonRetraitPointJD,
            SIGNAL(clicked(bool)),
            this,
            SLOT(RetraitPointD()));
}

void IHMArbitre::initialiserPageAccueil()
{
    afficherEtatBluetooth(ui->labelEtatModuleEcran, Absent);
    afficherEtatBluetooth(ui->labelEtatModuleNet, Absent);
    afficherEtatBluetooth(ui->labelEtatModuleScore, Absent);
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

void IHMArbitre::chargerRencontres()
{
    QString requete = "SELECT Rencontre.*, a.nomClub, b.nomClub FROM Rencontre "
                      "INNER JOIN Club a ON (a.idClub = Rencontre.idClubA) "
                      "INNER JOIN Club b ON (b.idClub = Rencontre.idClubW);";
    bool retour;

    rencontres.clear();
    retour = bdd->recuperer(requete, rencontres);
    qDebug() << Q_FUNC_INFO << rencontres;
    if(retour)
    {
        for(int i = 0; i < rencontres.size(); ++i)
        {
            ui->comboBoxListeRencontres->addItem(
              rencontres.at(i).at(COLONNE_nomClubA) + " vs " +
              rencontres.at(i).at(COLONNE_nomClubW));
        }
        chargerPartiesSimples();
        chargerPartiesDoubles();
    }
}

void IHMArbitre::chargerPartiesSimples()
{
    if(ui->comboBoxListeRencontres->currentIndex() == -1)
        return;

    qDebug() << Q_FUNC_INFO << ui->comboBoxListeRencontres->currentIndex();

    chargerJoueurs();
    ui->comboBoxListePartiesSimples->clear();
    QVector<int> sequenceJoueursEquipeA({ 0, 1, 2, 3, 0, 1, 3, 2, 0, 2, 3, 1 });
    QVector<int> sequenceJoueursEquipeW({ 0, 1, 2, 3, 1, 0, 2, 3, 2, 0, 1, 3 });
    for(int i = 0; i < sequenceJoueursEquipeA.size(); ++i)
    {
        /**
         * @todo Définir les noms de colonnes et intégrer les prénoms
         */
        ui->comboBoxListePartiesSimples->addItem(
          joueursEquipeA.at(sequenceJoueursEquipeA.at(i)).at(0) + " vs " +
          joueursEquipeW.at(sequenceJoueursEquipeW.at(i)).at(0));
    }
}

void IHMArbitre::chargerPartiesDoubles()
{
    if(ui->comboBoxListeRencontres->currentIndex() == -1)
        return;

    qDebug() << Q_FUNC_INFO << ui->comboBoxListeRencontres->currentIndex();

    chargerJoueurs();
    ui->comboBoxListeJoueurA->clear();
    ui->comboBoxListeJoueurB->clear();
    for(int i = 0; i < joueursEquipeA.size(); ++i)
    {
        /**
         * @todo Définir les noms de colonnes
         */
        ui->comboBoxListeJoueurA->addItem(joueursEquipeA.at(i).at(0) + " " +
                                          joueursEquipeA.at(i).at(1));
        ui->comboBoxListeJoueurB->addItem(joueursEquipeA.at(i).at(0) + " " +
                                          joueursEquipeA.at(i).at(1));
    }

    ui->comboBoxListeJoueurW->clear();
    ui->comboBoxListeJoueurX->clear();
    for(int i = 0; i < joueursEquipeW.size(); ++i)
    {
        /**
         * @todo Définir les noms de colonnes
         */
        ui->comboBoxListeJoueurW->addItem(joueursEquipeW.at(i).at(0) + " " +
                                          joueursEquipeW.at(i).at(1));
        ui->comboBoxListeJoueurX->addItem(joueursEquipeW.at(i).at(0) + " " +
                                          joueursEquipeW.at(i).at(1));
    }
}

void IHMArbitre::chargerClubs()
{
    QString requete = "SELECT * FROM Club;";
    bool    retour;

    clubs.clear();
    retour = bdd->recuperer(requete, clubs);
    qDebug() << Q_FUNC_INFO << clubs;
    if(retour)
    {
        for(int i = 0; i < clubs.size(); ++i)
        {
            ui->comboBoxChoixClubA->addItem(clubs.at(i).at(COLONNE_nomClub));
            ui->comboBoxChoixClubW->addItem(clubs.at(i).at(COLONNE_nomClub));
        }
    }
}

void IHMArbitre::chargerJoueurs()
{
    QString requeteListeJoueurA =
      "SELECT nom, prenom FROM Joueur "
      "WHERE idClub = '" +
      rencontres.at(ui->comboBoxListeRencontres->currentIndex())
        .at(COLONNE_idClubA) +
      "'";
    joueursEquipeA.clear();
    bool retour = bdd->recuperer(requeteListeJoueurA, joueursEquipeA);
    qDebug() << Q_FUNC_INFO << joueursEquipeA;
    QString requeteListeJoueurW =
      "SELECT nom, prenom FROM Joueur "
      "WHERE idClub = '" +
      rencontres.at(ui->comboBoxListeRencontres->currentIndex())
        .at(COLONNE_idClubW) +
      "'";
    joueursEquipeW.clear();
    retour = bdd->recuperer(requeteListeJoueurW, joueursEquipeW);
    qDebug() << Q_FUNC_INFO << joueursEquipeW;
}

void IHMArbitre::demarrerRencontre()
{
    qDebug() << Q_FUNC_INFO << "La rencontre est choisie";
    QString trame =
      DEBUT_TRAME ";RENCONTRE;" +
      rencontres.at(ui->comboBoxListeRencontres->currentIndex())
        .at(COLONNE_nomClubA) +
      ";" +
      rencontres.at(ui->comboBoxListeRencontres->currentIndex())
        .at(COLONNE_nomClubW) +
      ";" + joueursEquipeA.at(0).at(0) + ";" + joueursEquipeA.at(0).at(1) +
      ";" + joueursEquipeA.at(1).at(0) + ";" + joueursEquipeA.at(1).at(1) +
      ";" + joueursEquipeA.at(2).at(0) + ";" + joueursEquipeA.at(2).at(1) +
      ";" + joueursEquipeA.at(3).at(0) + ";" + joueursEquipeA.at(3).at(1) +
      ";" + joueursEquipeW.at(0).at(0) + ";" + joueursEquipeW.at(0).at(1) +
      ";" + joueursEquipeW.at(1).at(0) + ";" + joueursEquipeW.at(1).at(1) +
      ";" + joueursEquipeW.at(2).at(0) + ";" + joueursEquipeW.at(2).at(1) +
      ";" + joueursEquipeW.at(3).at(0) + ";" + joueursEquipeW.at(3).at(1) +
      ";\r\n";

    qDebug() << Q_FUNC_INFO << trame;
    communicationBluetooth->envoyer(communicationBluetooth->Ecran, trame);
}

void IHMArbitre::echangerJoueur()
{
    qDebug() << Q_FUNC_INFO << "changement de côté";
    /**
     * @todo Echanger les emplacements des joueurs et les scores
     */
}

void IHMArbitre::demarrerPartie()
{
    qDebug() << Q_FUNC_INFO << "Demarrage de la partie";
    /**
     * @todo Lancer une partie
     */
}

void IHMArbitre::AjoutPointG()
{
    qDebug() << Q_FUNC_INFO << "Ajout d'un point gauche";
    QString AffichagePointG = ui->labelScoreJG->text();
    int     pointG          = AffichagePointG.toInt();
    pointG++;
    ui->labelScoreJG->setText(QString::number(pointG));
}

void IHMArbitre::AjoutPointD()
{
    qDebug() << Q_FUNC_INFO << "Ajout d'un point droite";
    QString AffichagePointD = ui->labelScoreJD->text();
    int     pointD          = AffichagePointD.toInt();
    pointD++;
    ui->labelScoreJD->setText(QString::number(pointD));
}

void IHMArbitre::RetraitPointG()
{
    qDebug() << Q_FUNC_INFO << "Retrait d'un point gauche";
    QString AffichagePointG = ui->labelScoreJG->text();
    int     pointG          = AffichagePointG.toInt();
    pointG--;
    if(pointG < 0)
    {
        ui->labelScoreJG->setText("0");
    }
    else
    {
        ui->labelScoreJG->setText(QString::number(pointG));
    }
}

void IHMArbitre::RetraitPointD()
{
    qDebug() << Q_FUNC_INFO << "Retrait d'un point droite";
    QString AffichagePointD = ui->labelScoreJD->text();
    int     pointD          = AffichagePointD.toInt();
    pointD--;
    if(pointD < 0)
    {
        ui->labelScoreJD->setText("0");
    }
    else
    {
        ui->labelScoreJD->setText(QString::number(pointD));
    }
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
