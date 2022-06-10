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
    rencontre(nullptr), pointsTotalEquipeA(0), pointsTotalEquipeW(0), connecteurMinuteurActive(false)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    initialiserIHM();
    initialiserReception();
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

void IHMAfficheur::renitialiserScorePartieGauche()
{
    qDebug() << Q_FUNC_INFO;
    ui->scoreSet1JoueurGPartieG->setText("0");
    ui->scoreSet1JoueurDPartieG->setText("0");
    ui->statistiquesSet1PartieG->setText("");
    ui->scoreSet2JoueurGPartieG->setText("0");
    ui->scoreSet2JoueurDPartieG->setText("0");
    ui->statistiquesSet2PartieG->setText("");
    ui->scoreSet3JoueurGPartieG->setText("0");
    ui->scoreSet3JoueurDPartieG->setText("0");
    ui->statistiquesSet3PartieG->setText("");
    ui->scoreSet4JoueurGPartieG->setText("0");
    ui->scoreSet4JoueurDPartieG->setText("0");
    ui->statistiquesSet4PartieG->setText("");
    ui->scoreSet5JoueurGPartieG->setText("0");
    ui->scoreSet5JoueurDPartieG->setText("0");
    ui->statistiquesSet5PartieG->setText("");
    ui->nomJoueurGPartieG->setText("");
    ui->nomJoueurDPartieG->setText("");
    ui->classementJoueurGPartieG->setText("");
    ui->classementJoueurDPartieG->setText("");
    rencontre->setIdentifiantPartieGauche(-1);
    ui->tempsPartieGauche->setText("00:00:00");
    ui->affichageSetJoueurGPartieG->setText("0 | 0 | 0");
    ui->affichageSetJoueurDPartieG->setText("0 | 0 | 0");
}

void IHMAfficheur::actualiserHistoriqueRencontre(int idPartie)
{
    QString stringSetJoueurGauche = QString::number(rencontre->getPartie(idPartie).getSetJoueurG());
    QString stringSetJoueurDroite = QString::number(rencontre->getPartie(idPartie).getSetJoueurD());

    switch(idPartie)
    {
        case 0:

            ui->setGagnePartie1JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie1JoueurD->setText(stringSetJoueurDroite);

            break;

        case 1:

            ui->setGagnePartie2JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie2JoueurD->setText(stringSetJoueurDroite);

            break;

        case 2:

            ui->setGagnePartie3JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie3JoueurD->setText(stringSetJoueurDroite);

            break;

        case 3:

            ui->setGagnePartie4JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie4JoueurD->setText(stringSetJoueurDroite);

            break;

        case 4:

            ui->setGagnePartie5JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie5JoueurD->setText(stringSetJoueurDroite);

            break;

        case 5:

            ui->setGagnePartie6JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie6JoueurD->setText(stringSetJoueurDroite);

            break;

        case 6:

            ui->setGagnePartie7JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie7JoueurD->setText(stringSetJoueurDroite);

            break;

        case 7:

            ui->setGagnePartie8JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie8JoueurD->setText(stringSetJoueurDroite);

            break;

        case 8:

            ui->setGagnePartieDouble1JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartieDouble1JoueurD->setText(stringSetJoueurDroite);

            break;

        case 9:

            ui->setGagnePartieDouble2JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartieDouble2JoueurD->setText(stringSetJoueurDroite);

            break;

        case 10:

            ui->setGagnePartie11JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie11JoueurD->setText(stringSetJoueurDroite);

            break;

        case 11:

            ui->setGagnePartie12JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie12JoueurD->setText(stringSetJoueurDroite);

            break;

        case 12:

            ui->setGagnePartie13JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie13JoueurD->setText(stringSetJoueurDroite);

            break;

        case 13:

            ui->setGagnePartie14JoueurG->setText(stringSetJoueurGauche);
            ui->setGagnePartie14JoueurD->setText(stringSetJoueurDroite);

            break;
        default:
            break;
    }

    if(rencontre->getPartie(idPartie).getSetJoueurG() == NOMBRE_SET_GAGNANT)
    {
        ++pointsTotalEquipeA;
    }
    else if(rencontre->getPartie(idPartie).getSetJoueurD() == NOMBRE_SET_GAGNANT)
    {
        ++pointsTotalEquipeW;
    }

    QString stringPointsTotalEquipeA = QString::number(pointsTotalEquipeA);
    QString stringPointsTotalEquipeW = QString::number(pointsTotalEquipeW);

    ui->pointsTotalEquipeA->setText(stringPointsTotalEquipeA);
    ui->pointsTotalEquipeW->setText(stringPointsTotalEquipeW);
}

void IHMAfficheur::actualiserAffichageSetsPartieGauche(QByteArray idPartieScore)
{
    qDebug() << Q_FUNC_INFO << "Retour de aGagneSet() : " << rencontre->getPartie(idPartieScore.toUInt()).aGagneSet();

    if(rencontre->getPartie(idPartieScore.toUInt()).aGagneSet())
    {
        ui->affichageSetJoueurGPartieG->setText(rencontre->getPartie(idPartieScore.toUInt())
                                                  .definirAffichageSets(rencontre->getPartie(idPartieScore.toUInt())
                                                                          .getSetJoueurG()));
        ui->affichageSetJoueurDPartieG->setText(rencontre->getPartie(idPartieScore.toUInt())
                                                  .definirAffichageSets(rencontre->getPartie(idPartieScore.toUInt())
                                                                          .getSetJoueurD()));
    }
}

void IHMAfficheur::cacherPartiesDoubles()
{
    ui->joueursPartieDouble1coteG->hide();
    ui->joueursPartieDouble1coteD->hide();
    ui->joueursPartieDouble2coteG->hide();
    ui->joueursPartieDouble2coteD->hide();
    ui->setGagnePartieDouble1JoueurG->hide();
    ui->setGagnePartieDouble1JoueurD->hide();
    ui->setGagnePartieDouble2JoueurG->hide();
    ui->setGagnePartieDouble2JoueurD->hide();
}

void IHMAfficheur::ReafficherPartiesDouble(QByteArray JoueurW1, QByteArray JoueurW2, QByteArray idPartieDouble, QByteArray JoueurA2, QByteArray JoueurA1)
{
    if(idPartieDouble.toUInt() == ID_PARTIE_DOUBLE_1)
    {
        ui->joueursPartieDouble1coteG->show();
        ui->joueursPartieDouble1coteG->setText(JoueurA1 + '\n' + JoueurA2);
        ui->joueursPartieDouble1coteD->show();
        ui->joueursPartieDouble1coteD->setText(JoueurW1 + '\n' + JoueurW2);
        ui->setGagnePartieDouble1JoueurG->show();
        ui->setGagnePartieDouble1JoueurD->show();
    }
    else if(idPartieDouble.toUInt() == ID_PARTIE_DOUBLE_2)
    {
        ui->joueursPartieDouble2coteG->show();
        ui->joueursPartieDouble2coteG->setText(JoueurA1 + '\n' + JoueurA2);
        ui->joueursPartieDouble2coteD->show();
        ui->joueursPartieDouble2coteD->setText(JoueurW1 + '\n' + JoueurW2);
        ui->setGagnePartieDouble2JoueurG->show();
        ui->setGagnePartieDouble2JoueurD->show();
    }
}

void IHMAfficheur::associerSignalSlotRencontre()
{
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

    connect(receptionTrame,
            SIGNAL(nouvelleTrameSimple(QString,
                                       QByteArray,
                                       QByteArray,
                                       QByteArray,
                                       QByteArray,
                                       QByteArray)),
            this,
            SLOT(initialiserPartieSimple(QString,
                                         QByteArray,
                                         QByteArray,
                                         QByteArray,
                                         QByteArray,
                                         QByteArray)));

    connect(receptionTrame,
            SIGNAL(nouvelleTrameDouble(QString,
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
            SLOT(initialiserPartieDouble(QString,
                                         QByteArray,
                                         QByteArray,
                                         QByteArray,
                                         QByteArray,
                                         QByteArray,
                                         QByteArray,
                                         QByteArray,
                                         QByteArray,
                                         QByteArray)));
    connect(receptionTrame,
            SIGNAL(nouvelleTrameScore(QString,
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
            SLOT(initialiserScorePartie(QString,
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

void IHMAfficheur::actualiserSetPartie(QByteArray scoreJG, QByteArray idPartieScore, QByteArray scoreJD)
{
    switch(rencontre->getPartie(idPartieScore.toUInt()).getNombreSet())
    {
        case 0:
            ui->scoreSet1JoueurGPartieG->setText(scoreJG);
            ui->scoreSet1JoueurDPartieG->setText(scoreJD);
            ui->statistiquesSet1PartieG->setText(
              "Net = " +
              QString::number(rencontre->getPartie(idPartieScore.toUInt())
                                .getNombreNET()));
            break;
        case 1:
            ui->scoreSet2JoueurGPartieG->setText(scoreJG);
            ui->scoreSet2JoueurDPartieG->setText(scoreJD);
            ui->statistiquesSet2PartieG->setText(
              "Net = " +
              QString::number(rencontre->getPartie(idPartieScore.toUInt())
                                .getNombreNET()));
            break;
        case 2:
            ui->scoreSet3JoueurGPartieG->setText(scoreJG);
            ui->scoreSet3JoueurDPartieG->setText(scoreJD);
            ui->statistiquesSet3PartieG->setText(
              "Net = " +
              QString::number(rencontre->getPartie(idPartieScore.toUInt())
                                .getNombreNET()));
            break;
        case 3:
            ui->scoreSet4JoueurGPartieG->setText(scoreJG);
            ui->scoreSet4JoueurDPartieG->setText(scoreJD);
            ui->statistiquesSet4PartieG->setText(
              "Net = " +
              QString::number(rencontre->getPartie(idPartieScore.toUInt())
                                .getNombreNET()));
            break;
        case 4:
            ui->scoreSet5JoueurGPartieG->setText(scoreJG);
            ui->scoreSet5JoueurDPartieG->setText(scoreJD);
            ui->statistiquesSet5PartieG->setText(
              "Net = " +
              QString::number(rencontre->getPartie(idPartieScore.toUInt())
                                .getNombreNET()));
            break;
        default:
            break;
    }
}

void IHMAfficheur::connecterMinuteurPartieEtIHM(QByteArray idPartieScore)
{
    qDebug() << Q_FUNC_INFO;
    connect(rencontre->getPointeurPartie(idPartieScore.toUInt())->getMinuteur(),
            SIGNAL(timeout()),
            rencontre->getPointeurPartie(idPartieScore.toUInt()),
            SLOT(incrementerTempsPartieCadreGauche()));

    connect(rencontre->getPointeurPartie(idPartieScore.toUInt()),
            SIGNAL(tempsPartieCadreGauche(int)),
            this,
            SLOT(actualiserTempsCadreGauche(int)));
    this->connecteurMinuteurActive = true;
}

void IHMAfficheur::demmarerMinuteur(QByteArray etatPartie, QByteArray idPartieScore)
{
    if(etatPartie.toUInt())
    {
        qDebug() << Q_FUNC_INFO << "Temps en cours ? : " << rencontre->getPointeurPartie(idPartieScore.toUInt())->estMinuteurDemarrer();
        if(!rencontre->getPointeurPartie(idPartieScore.toUInt())->estMinuteurDemarrer())
        {
            qDebug() << Q_FUNC_INFO << "Demarage du Chronometre : ";
            rencontre->getPointeurPartie(idPartieScore.toUInt())->getMinuteur()->start(SECONDE_EN_MILLISECONDE);
            //actualiserTempsCadreGauche(idPartieScore);
            qDebug() << Q_FUNC_INFO << "Temps en cours ? : " << rencontre->getPointeurPartie(idPartieScore.toUInt())->estMinuteurDemarrer();
            if(!estConnecteurMinuteurActive())
            {
                connecterMinuteurPartieEtIHM(idPartieScore);
            }
        }
    }
}

void IHMAfficheur::arreterMinuteur(unsigned int id)
{
    rencontre->getPointeurPartie(id)->getMinuteur()->stop();
}

bool IHMAfficheur::estConnecteurMinuteurActive()
{
    return connecteurMinuteurActive;
}

void IHMAfficheur::actualiserTempsCadreGauche(int idPartieScore)
{
    qDebug() << Q_FUNC_INFO;
    QString tempsPartiesActuelle = rencontre->getPartie(idPartieScore).getTempsPartie()->toString(Qt::TextDate);
    ui->tempsPartieGauche->setText(tempsPartiesActuelle);
}

void IHMAfficheur::afficherSponsors(int i)
{
    labelsSponsors[i]->show();
    labelsSponsors[i]->setMinimumHeight(190);
    labelsSponsors[i]->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:0.991968, y2:1, "
                                     "stop:0 rgba(60, 72, 156, 255), "
                                     "stop:1 rgba(111, 145, 239, 255));\n"
                                     "color: rgb(238, 238, 236);\nf"
                                     "ont: 87 18pt \"Lato Black\";");
}

void IHMAfficheur::activerDeroulementSponsors()
{
    qDebug() << Q_FUNC_INFO;
    for(int i = 0; i < labelsSponsors.size(); ++i)
    {
        qDebug() << i << "est caché ?" << labelsSponsors[i]->isHidden();
        if(!(labelsSponsors[i]->isHidden()))
        {
            labelsSponsors[i]->hide();
            if((i + 1) == labelsSponsors.size())
            {
                i = 0;
            }
            else
            {
                i++;
            }

            afficherSponsors(i);
            i = labelsSponsors.size();
        }
    }
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
        ui->Application->setCurrentIndex(IHMAfficheur::Ecran::EcranRencontre);
        rencontre = new Rencontre(QString(NomClubA.data()), QString(NomClubW.data()));

        cacherPartiesDoubles();
        initialiserSponsors();

        // ajoute les joueurs dans les équipes
        initialiserEquipeA(nomModule, NomJoueurA, PrenomJoueurA, NomJoueurB, PrenomJoueurB, NomJoueurC, PrenomJoueurC, NomJoueurD, PrenomJoueurD);
        initialiserEquipeW(nomModule, NomJoueurW, PrenomJoueurW, NomJoueurX, PrenomJoueurX, NomJoueurY, PrenomJoueurY, NomJoueurZ, PrenomJoueurZ);

        // initialise l'affichage
        initialiserEquipes(QString(NomClubA.data()), QString(NomClubW.data()));
        initialiserJoueurs(NomJoueurA, NomJoueurD, PrenomJoueurC, NomJoueurC, PrenomJoueurB, NomJoueurB, PrenomJoueurY, NomJoueurY, PrenomJoueurX, NomJoueurX, PrenomJoueurZ, PrenomJoueurW, NomJoueurZ, NomJoueurW, PrenomJoueurA, PrenomJoueurD);

        QStringList sequenceJoueursEquipeA;
        sequenceJoueursEquipeA << "A"
                               << "B"
                               << "C"
                               << "D"
                               << "A"
                               << "B"
                               << "D"
                               << "C"
                               << "A"
                               << "C"
                               << "D"
                               << "B";
        QStringList sequenceJoueursEquipeW;
        sequenceJoueursEquipeW << "W"
                               << "X"
                               << "Y"
                               << "Z"
                               << "X"
                               << "W"
                               << "Y"
                               << "Z"
                               << "Y"
                               << "W"
                               << "X"
                               << "Z";
        // initialise les parties
        for(int i = 0; i < sequenceJoueursEquipeA.size(); ++i)
        {
            initialiserPartieSimple1(rencontre->getEquipeA()->getJoueur(sequenceJoueursEquipeA.at(i))->getNom(),
                                     rencontre->getEquipeA()->getJoueur(sequenceJoueursEquipeA.at(i))->getPrenom(),
                                     rencontre->getEquipeW()->getJoueur(sequenceJoueursEquipeW.at(i))->getNom(),
                                     rencontre->getEquipeW()->getJoueur(sequenceJoueursEquipeW.at(i))->getPrenom());
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Erreur rencontre en cours !";
    }
}

void IHMAfficheur::initialiserPartieSimple(QString    nomModule,
                                           QByteArray idPartie,
                                           QByteArray JoueurA,
                                           QByteArray ClassementJoueurA,
                                           QByteArray JoueurB,
                                           QByteArray ClassementJoueurW)
{
    /**
     * @todo Gerer deux parties en même temps
     */
    qDebug() << Q_FUNC_INFO << nomModule;
    if(rencontre == nullptr)
    {
        qDebug() << Q_FUNC_INFO << "Erreur il y a pas de rencontre en cours";
        return;
    }
    else
    {
        ui->nomJoueurGPartieG->setText(JoueurA);
        ui->nomJoueurDPartieG->setText(JoueurB);
        ui->classementJoueurGPartieG->setText(ClassementJoueurA + " pts");
        ui->classementJoueurDPartieG->setText(ClassementJoueurW + " pts");
        rencontre->setIdentifiantPartieGauche(idPartie.toUInt());
    }
}

void IHMAfficheur::initialiserPartieDouble(QString    nomModule,
                                           QByteArray idPartieDouble,
                                           QByteArray JoueurA1,
                                           QByteArray ClassementA1,
                                           QByteArray JoueurA2,
                                           QByteArray ClassementA2,
                                           QByteArray JoueurW1,
                                           QByteArray ClassementW1,
                                           QByteArray JoueurW2,
                                           QByteArray ClassementW2)
{
    /**
     * @todo Gerer deux parties en même temps
     */
    qDebug() << Q_FUNC_INFO << nomModule;
    if(rencontre == nullptr)
    {
        qDebug() << Q_FUNC_INFO << "Erreur il y a pas de rencontre en cours";
        return;
    }
    else
    {
        ui->nomJoueurGPartieG->setText(JoueurA1 + '\n' + JoueurA2);
        ui->nomJoueurDPartieG->setText(JoueurW1 + '\n' + JoueurW2);
        QString sommeClassementA =
          QString::number(ClassementA1.toInt() + ClassementA2.toInt());
        QString sommeClassementW =
          QString::number(ClassementW1.toInt() + ClassementW2.toInt());
        ui->classementJoueurGPartieG->setText(sommeClassementA + "pts");
        ui->classementJoueurDPartieG->setText(sommeClassementW + "pts");
        rencontre->setIdentifiantPartieGauche(idPartieDouble.toUInt());

        ReafficherPartiesDouble(JoueurW1, JoueurW2, idPartieDouble, JoueurA2, JoueurA1);
    }
}

void IHMAfficheur::initialiserScorePartie(QString    nomModule,
                                          QByteArray idPartieScore,
                                          QByteArray scoreJG,
                                          QByteArray scoreJD,
                                          QByteArray etatPartie,
                                          QByteArray tempsMort,
                                          QByteArray nbSetJG,
                                          QByteArray nbSetJD,
                                          QByteArray tourService,
                                          QByteArray net)
{
    qDebug() << Q_FUNC_INFO << nomModule;
    if(rencontre == nullptr)
    {
        qDebug() << Q_FUNC_INFO << "Erreur il y a pas de rencontre en cours";
        return;
    }
    else
    {
        actualiserSetPartie(scoreJG, idPartieScore, scoreJD);
        rencontre->actualiserPartie(idPartieScore, scoreJG, scoreJD, nbSetJG, nbSetJD, net);
        actualiserAffichageSetsPartieGauche(idPartieScore);

        if(tempsMort.toUInt())
        {
            arreterMinuteur(idPartieScore.toUInt());
        }
        else
        {
            demmarerMinuteur(etatPartie, idPartieScore);
        }

        if(tourService.toUInt()) //(Gauche=0 ou Droite=1)
        {
            ui->serviceJoueurDPartieG->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:0.991968, y2:1, "
                                                     "stop:0 rgba(60, 72, 156, 255), stop:1 rgba(111, 145, 239, 255));"
                                                     "color: rgb(238, 238, 236);");
            ui->serviceJoueurGPartieG->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:0.991968, y2:1, "
                                                     "stop:0 rgba(60, 72, 156, 255), stop:1 rgba(111, 145, 239, 255));"
                                                     "color: rgb(238, 238, 236);"
                                                     "image: url(:/images/mainLevee.png)");
        }
        else
        {
            ui->serviceJoueurGPartieG->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:0.991968, y2:1, "
                                                     "stop:0 rgba(60, 72, 156, 255), stop:1 rgba(111, 145, 239, 255));"
                                                     "color: rgb(238, 238, 236);");

            ui->serviceJoueurDPartieG->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:0.991968, y2:1, "
                                                     "stop:0 rgba(60, 72, 156, 255), stop:1 rgba(111, 145, 239, 255));"
                                                     "color: rgb(238, 238, 236);"
                                                     "image: url(:/images/mainLevee.png)");
        }

        if(!etatPartie.toUInt())
        {
            arreterMinuteur(idPartieScore.toUInt());
            renitialiserScorePartieGauche();
            actualiserHistoriqueRencontre(idPartieScore.toUInt());
        }
    }
}

// Méthodes privées

void IHMAfficheur::initialiserIHM()
{
    qDebug() << Q_FUNC_INFO;
#ifdef ECRAN_VEILLE
    ui->Application->setCurrentIndex(IHMAfficheur::Ecran::EcranVeille);
    player.setMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QString("/TitleTheme.mp3")));
    qDebug() << "Le fichier audio est valable ? : " << player.isAudioAvailable();
    player.play();
#endif // ECRAN_VEILLE

#ifdef PLEIN_ECRAN
    showMaximized();
    showFullScreen();
#endif // PLEIN_ECRAN
}

void IHMAfficheur::initialiserReception()
{
    qDebug() << Q_FUNC_INFO;
    receptionTrame = new ReceptionTrame(this);

    associerSignalSlotRencontre();
}

void IHMAfficheur::initialiserEquipes(QString clubA, QString clubW)
{
    qDebug() << Q_FUNC_INFO << clubA << clubW;
    ui->clubA->setText(clubA);
    ui->clubW->setText(clubW);
}

void IHMAfficheur::initialiserEquipeA(QString    nomModule,
                                      QByteArray NomJoueurA,
                                      QByteArray PrenomJoueurA,
                                      QByteArray NomJoueurB,
                                      QByteArray PrenomJoueurB,
                                      QByteArray NomJoueurC,
                                      QByteArray PrenomJoueurC,
                                      QByteArray NomJoueurD,
                                      QByteArray PrenomJoueurD)
{
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
}

void IHMAfficheur::initialiserEquipeW(QString    nomModule,
                                      QByteArray NomJoueurW,
                                      QByteArray PrenomJoueurW,
                                      QByteArray NomJoueurX,
                                      QByteArray PrenomJoueurX,
                                      QByteArray NomJoueurY,
                                      QByteArray PrenomJoueurY,
                                      QByteArray NomJoueurZ,
                                      QByteArray PrenomJoueurZ)
{
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

void IHMAfficheur::initialiserPartieSimple1(QString nomJoueurA,
                                            QString prenomJoueurA,
                                            QString nomJoueurW,
                                            QString prenomJoueurW)
{
    qDebug() << Q_FUNC_INFO;
    rencontre->setPartiesSimple(nomJoueurA,
                                prenomJoueurA,
                                nomJoueurW,
                                prenomJoueurW);
}

void IHMAfficheur::initialiserPartieDouble1(QString nomJoueurA1,
                                            QString prenomJoueurA1,
                                            QString nomJoueurA2,
                                            QString prenomJoueurA2,
                                            QString nomJoueurW1,
                                            QString prenomJoueurW1,
                                            QString nomJoueurW2,
                                            QString prenomJoueurW2)
{
    qDebug() << Q_FUNC_INFO;
    rencontre->setPartiesDouble(nomJoueurA1,
                                prenomJoueurA1,
                                nomJoueurA2,
                                prenomJoueurA2,
                                nomJoueurW1,
                                prenomJoueurW1,
                                nomJoueurW2,
                                prenomJoueurW2);
}

void IHMAfficheur::initialiserJoueurs(QByteArray NomJoueurA, QByteArray NomJoueurD, QByteArray PrenomJoueurC, QByteArray NomJoueurC, QByteArray PrenomJoueurB, QByteArray NomJoueurB, QByteArray PrenomJoueurY, QByteArray NomJoueurY, QByteArray PrenomJoueurX, QByteArray NomJoueurX, QByteArray PrenomJoueurZ, QByteArray PrenomJoueurW, QByteArray NomJoueurZ, QByteArray NomJoueurW, QByteArray PrenomJoueurA, QByteArray PrenomJoueurD)
{
    initialiserJoueurA(QString(NomJoueurA.data()), QString(PrenomJoueurA.data()));
    initialiserJoueurB(QString(NomJoueurB.data()), QString(PrenomJoueurB.data()));
    initialiserJoueurC(QString(NomJoueurC.data()), QString(PrenomJoueurC.data()));
    initialiserJoueurD(QString(NomJoueurD.data()), QString(PrenomJoueurD.data()));
    initialiserJoueurW(QString(NomJoueurW.data()), QString(PrenomJoueurW.data()));
    initialiserJoueurX(QString(NomJoueurX.data()), QString(PrenomJoueurX.data()));
    initialiserJoueurY(QString(NomJoueurY.data()), QString(PrenomJoueurY.data()));
    initialiserJoueurZ(QString(NomJoueurZ.data()), QString(PrenomJoueurZ.data()));
}

void IHMAfficheur::initialiserSponsors()
{
    qDebug() << Q_FUNC_INFO;
    labelsSponsors.push_back(ui->sponsor1);
    labelsSponsors.push_back(ui->sponsor2);
    labelsSponsors.push_back(ui->sponsor3);
    ui->sponsor2->hide();
    ui->sponsor3->hide();
    connect(&minuteurSponsors,
            SIGNAL(timeout()),
            this,
            SLOT(activerDeroulementSponsors()));
    minuteurSponsors.start(10000);
}
