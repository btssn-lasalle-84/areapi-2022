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
    chargerRencontresASuppr();
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
    /**
     * @todo Afficher un net
     */
    ui->buttonValiderNet->show();
    ui->labelNet->show();
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
            SLOT(demarrerPartieSimple()));
    connect(ui->buttonSelectionnerRencontreDouble,
            SIGNAL(clicked(bool)),
            this,
            SLOT(demarrerPartieDouble()));
    connect(ui->buttonSupprimerRencontre,
            SIGNAL(clicked(bool)),
            this,
            SLOT(supprimerRencontre()));
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
            SLOT(ajoutPointG()));
    connect(ui->buttonAjoutPointJD,
            SIGNAL(clicked(bool)),
            this,
            SLOT(ajoutPointD()));
    connect(ui->buttonRetraitPointJG,
            SIGNAL(clicked(bool)),
            this,
            SLOT(retraitPointG()));
    connect(ui->buttonRetraitPointJD,
            SIGNAL(clicked(bool)),
            this,
            SLOT(retraitPointD()));
    connect(ui->buttonCreerRencontre,
            SIGNAL(clicked(bool)),
            this,
            SLOT(creerRencontre()));
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
    ui->comboBoxListeRencontres->clear();
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

void IHMArbitre::chargerRencontresASuppr()
{
    QString requete = "SELECT Rencontre.*, a.nomClub, b.nomClub FROM Rencontre "
                      "INNER JOIN Club a ON (a.idClub = Rencontre.idClubA) "
                      "INNER JOIN Club b ON (b.idClub = Rencontre.idClubW);";
    bool retour;

    rencontres.clear();
    ui->comboBoxListeRencontresASupprimer->clear();
    retour = bdd->recuperer(requete, rencontres);
    qDebug() << Q_FUNC_INFO << rencontres;
    if(retour)
    {
        for(int i = 0; i < rencontres.size(); ++i)
        {
            ui->comboBoxListeRencontresASupprimer->addItem(
              rencontres.at(i).at(COLONNE_nomClubA) + " vs " +
              rencontres.at(i).at(COLONNE_nomClubW));
        }
    }
}

void IHMArbitre::chargerPartiesSimples()
{
    if(ui->comboBoxListeRencontres->currentIndex() == -1)
    {
        ui->comboBoxListePartiesSimples->setCurrentIndex(-1);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << ui->comboBoxListeRencontres->currentIndex();

        chargerJoueurs();
        ui->comboBoxListePartiesSimples->clear();
        QVector<int> sequenceJoueursEquipeA(
          { 0, 1, 2, 3, 0, 1, 3, 2, 0, 2, 3, 1 });
        QVector<int> sequenceJoueursEquipeW(
          { 0, 1, 2, 3, 1, 0, 2, 3, 2, 0, 1, 3 });
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
}

void IHMArbitre::chargerPartiesDoubles()
{
    if(ui->comboBoxListeRencontres->currentIndex() == -1)
    {
        ui->comboBoxListeJoueurA->setCurrentIndex(-1);
        ui->comboBoxListeJoueurB->setCurrentIndex(-1);
        ui->comboBoxListeJoueurW->setCurrentIndex(-1);
        ui->comboBoxListeJoueurX->setCurrentIndex(-1);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << ui->comboBoxListeRencontres->currentIndex();

        chargerJoueurs();
        ui->comboBoxListeJoueurA->clear();
        ui->comboBoxListeJoueurB->clear();
        for(int i = 0; i < 4; ++i)
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
        for(int i = 0; i < 4; ++i)
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

void IHMArbitre::envoiTrameScore()
{
    int idPartie      = 1;
    int etatPartie    = 1;
    int tempsMort     = 1;
    int nbSetGagnesJG = 1;
    int nbSetGagnesJD = 2;
    int tourService   = 0;
    int nbNet         = 5;

    QString trameScore =
      DEBUT_TRAME ";SCORE;" + QString::number(idPartie) + ";" +
      ui->labelScoreJD->text() + ";" + ui->labelScoreJG->text() + ";" +
      QString::number(etatPartie) + ";" + QString::number(tempsMort) + ";" +
      QString::number(nbSetGagnesJG) + ";" + QString::number(nbSetGagnesJD) +
      ";" + QString::number(tourService) + ";" + QString::number(nbNet) +
      ";\r\n";

    qDebug() << trameScore;

    communicationBluetooth->envoyer(communicationBluetooth->Score, trameScore);
    communicationBluetooth->envoyer(communicationBluetooth->Ecran, trameScore);
}

void IHMArbitre::demarrerRencontre()
{
    if(ui->comboBoxListeRencontres->currentIndex() == -1)
        return;
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

void IHMArbitre::demarrerPartieSimple()
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
    ui->buttonAjoutPointJG->hide();
    ui->buttonAjoutPointJD->hide();
    ui->buttonRetraitPointJG->hide();
    ui->buttonRetraitPointJD->hide();
    ui->buttonDebutFinPartie->setText("Démarrer la partie");
    afficherEcran(IHMArbitre::Partie);
}

void IHMArbitre::demarrerPartieDouble()
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
    ui->buttonAjoutPointJG->hide();
    ui->buttonAjoutPointJD->hide();
    ui->buttonRetraitPointJG->hide();
    ui->buttonRetraitPointJD->hide();
    ui->buttonDebutFinPartie->setText("Démarrer la partie");
    afficherEcran(IHMArbitre::Partie);
}

void IHMArbitre::supprimerRencontre()
{
    QVector<QStringList> idClub;

    QStringList club =
      ui->comboBoxListeRencontresASupprimer->currentText().split(" vs ");
    if(ui->comboBoxListeRencontresASupprimer->currentText() != "")
    {
        QString requeteRechercheRencontre =
          "SELECT Rencontre.idRencontre FROM Rencontre "
          "INNER JOIN Club a ON (a.idClub = Rencontre.idClubA) "
          "INNER JOIN Club b ON (b.idClub = Rencontre.idClubW)"
          "WHERE a.nomClub = '" +
          club.at(0) + "' AND b.nomClub = '" + club.at(1) + "';";
        bool retourIdClub = bdd->recuperer(requeteRechercheRencontre, idClub);
        qDebug() << Q_FUNC_INFO << "retourIdClub =" << retourIdClub;
        if(retourIdClub)
        {
            QString requeteSupprRencontre =
              "DELETE FROM Rencontre WHERE idRencontre = '" +
              (idClub.at(0).at(0)) + "';";
            bool retourSuppressionRencontre =
              bdd->executer(requeteSupprRencontre);
            qDebug() << Q_FUNC_INFO << "retourSuppressionRencontre ="
                     << retourSuppressionRencontre;
            chargerRencontres();
            chargerRencontresASuppr();
            chargerPartiesSimples();
            chargerPartiesDoubles();
        }
    }
}

void IHMArbitre::creerRencontre()
{
    qDebug() << Q_FUNC_INFO << "Créer une rencontre";
    QStringList date = ui->dateEdit->text().split("/");

    QString requeteCreerRencontre =
      "INSERT INTO Rencontre"
      "(idClubA, idClubW, nbPartiesGagnantes, estFinie, horodatage)"
      "VALUES ('" +
      QString::number(ui->comboBoxChoixClubA->currentIndex() + 1) + "', '" +
      QString::number(ui->comboBoxChoixClubW->currentIndex() + 1) + "', '" +
      QString::number(NB_SET_GAGNANTS) + "', '0', '" + date.at(2) + "/" +
      date.at(1) + "/" + date.at(0) + " " + ui->timeEdit->text() + ":00')";
    qDebug() << Q_FUNC_INFO << requeteCreerRencontre;
    bdd->executer(requeteCreerRencontre);
    chargerRencontres();
    chargerRencontresASuppr();
}

void IHMArbitre::echangerJoueur()
{
    qDebug() << Q_FUNC_INFO << "changement de côté";
    QString stockageString = ui->labelScoreJD->text();
    ui->labelScoreJD->setText(ui->labelScoreJG->text());
    ui->labelScoreJG->setText(stockageString);
    stockageString = ui->labelJoueurDroite->text();
    ui->labelJoueurDroite->setText(ui->labelJoueurGauche->text());
    ui->labelJoueurGauche->setText(stockageString);
    int stockageSet   = nbSetGagneJoueurG;
    nbSetGagneJoueurG = nbSetGagneJoueurD;
    nbSetGagneJoueurD = stockageSet;
}

void IHMArbitre::initialisationNouvellePartie()
{
    nbSetGagneJoueurG = 0;
    nbSetGagneJoueurD = 0;
    ui->ButtonEchangerJoueur->hide();
    ui->buttonAjoutPointJG->show();
    ui->buttonAjoutPointJD->show();
    ui->buttonRetraitPointJG->show();
    ui->buttonRetraitPointJD->show();
    ui->buttonDebutFinPartie->hide();
    ui->buttonDebutFinPartie->setText("Fin de set");
    ui->buttonValiderNet->hide();
    ui->labelNet->hide();
    partieEnCours = true;
    aDejaEchanger = false;
    nbSetJouer++;
}

void IHMArbitre::initialisationFinPartie()
{
    afficherEcran(IHMArbitre::Rencontre);
    ui->ButtonEchangerJoueur->show();
    ui->labelScoreJD->setText("0");
    ui->labelScoreJG->setText("0");
    partieEnCours = false;
    nbSetJouer    = 0;
    ui->buttonDebutFinPartie->setText("Début de Partie");
    envoiTrameScore();
}

void IHMArbitre::demarrerPartie()
{
    /**
     * @todo Modifier pour ajouter les 3 set gagnant
     */
    QString AffichagePointD = ui->labelScoreJD->text();
    QString AffichagePointG = ui->labelScoreJG->text();
    int     pointD          = AffichagePointD.toInt();
    int     pointG          = AffichagePointG.toInt();
    if(!partieEnCours)
    {
        qDebug() << Q_FUNC_INFO << "Demarrage de la partie";
        initialisationNouvellePartie();
        envoiTrameScore();
        // communicationBluetooth->connecter(communicationBluetooth->Net);
    }
    else
    {
        if(pointD == 3 || pointG == 3)
        {
            qDebug() << Q_FUNC_INFO << "Fin de la partie  " << nbSetJouer;
            qDebug() << Q_FUNC_INFO << "Partie : " << nbSetJouer;
            if(pointD > pointG)
            {
                nbSetGagneJoueurD++;
            }
            else
            {
                nbSetGagneJoueurG++;
            }
            initialisationFinPartie();
        }
        else if(nbSetJouer == 4)
        {
            qDebug() << Q_FUNC_INFO << "Partie : " << nbSetJouer;
            if(pointD > pointG)
            {
                nbSetGagneJoueurD++;
            }
            else
            {
                nbSetGagneJoueurG++;
            }
            ui->labelScoreJD->setText("0");
            ui->labelScoreJG->setText("0");
            ui->buttonAjoutPointJG->show();
            ui->buttonAjoutPointJD->show();
            ui->buttonDebutFinPartie->hide();
            ui->buttonDebutFinPartie->setText("Fin de Partie");
            nbSetJouer++;
            envoiTrameScore();
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "Partie : " << nbSetJouer;
            if(pointD > pointG)
            {
                nbSetGagneJoueurD++;
            }
            else
            {
                nbSetGagneJoueurG++;
            }
            ui->labelScoreJD->setText("0");
            ui->labelScoreJG->setText("0");
            ui->buttonAjoutPointJG->show();
            ui->buttonAjoutPointJD->show();
            ui->buttonDebutFinPartie->hide();
            echangerJoueur();
            nbSetJouer++;
            envoiTrameScore();
        }
    }
    qDebug() << Q_FUNC_INFO << "G :" << nbSetGagneJoueurG
             << "D :" << nbSetGagneJoueurD;
}

void IHMArbitre::ajoutPointG()
{
    qDebug() << Q_FUNC_INFO << "Ajout d'un point gauche";
    QString AffichagePointG = ui->labelScoreJG->text();
    QString AffichagePointD = ui->labelScoreJD->text();
    int     pointG          = AffichagePointG.toInt();
    int     pointD          = AffichagePointD.toInt();
    pointG++;
    qDebug() << Q_FUNC_INFO << pointG << pointD;
    if((pointG >= 11) || (pointD >= 11))
    {
        if((pointG >= pointD) && ((pointG - pointD) >= 2))
        {
            ui->buttonAjoutPointJD->hide();
            ui->buttonAjoutPointJG->hide();
            ui->buttonDebutFinPartie->show();
        }
        else if((pointD >= pointG) && ((pointD - pointG) >= 2))
        {
            ui->buttonAjoutPointJD->hide();
            ui->buttonAjoutPointJG->hide();
            ui->buttonDebutFinPartie->show();
        }
    }
    ui->labelScoreJG->setText(QString::number(pointG));
    if(nbSetJouer == 5 && !aDejaEchanger && pointG == 5)
    {
        echangerJoueur();
        aDejaEchanger = true;
    }
    envoiTrameScore();
}

void IHMArbitre::ajoutPointD()
{
    qDebug() << Q_FUNC_INFO << "Ajout d'un point droite";
    QString AffichagePointD = ui->labelScoreJD->text();
    QString AffichagePointG = ui->labelScoreJG->text();
    int     pointD          = AffichagePointD.toInt();
    int     pointG          = AffichagePointG.toInt();
    pointD++;
    if((pointG >= 11) || (pointD >= 11))
    {
        if((pointG >= pointD) && ((pointG - pointD) >= 2))
        {
            ui->buttonAjoutPointJD->hide();
            ui->buttonAjoutPointJG->hide();
            ui->buttonDebutFinPartie->show();
        }
        else if((pointD >= pointG) && ((pointD - pointG) >= 2))
        {
            ui->buttonAjoutPointJD->hide();
            ui->buttonAjoutPointJG->hide();
            ui->buttonDebutFinPartie->show();
        }
    }
    ui->labelScoreJD->setText(QString::number(pointD));
    if(nbSetJouer == 5 && !aDejaEchanger && pointD == 5)
    {
        echangerJoueur();
        aDejaEchanger = true;
    }
    envoiTrameScore();
}

void IHMArbitre::retraitPointG()
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
    ui->buttonAjoutPointJG->show();
    ui->buttonAjoutPointJD->show();
    ui->buttonDebutFinPartie->hide();
    if(nbSetJouer == 5 && aDejaEchanger && pointG == 4)
    {
        echangerJoueur();
        aDejaEchanger = false;
    }
    envoiTrameScore();
}

void IHMArbitre::retraitPointD()
{
    qDebug() << Q_FUNC_INFO << "Retrait d'un point droite";
    QString AffichagePointD = ui->labelScoreJD->text();
    int     pointD          = AffichagePointD.toInt();
    pointD--;
    if(pointD < 0)
    {
        ui->labelScoreJD->setText("0");
        pointD = 0;
    }
    else
    {
        ui->labelScoreJD->setText(QString::number(pointD));
    }
    ui->buttonAjoutPointJG->show();
    ui->buttonAjoutPointJD->show();
    ui->buttonDebutFinPartie->hide();
    if(nbSetJouer == 5 && aDejaEchanger && pointD == 4)
    {
        echangerJoueur();
        aDejaEchanger = false;
    }
    envoiTrameScore();
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
