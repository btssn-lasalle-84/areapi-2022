#ifndef IHMARBITRE_H
#define IHMARBITRE_H

/**
 * @file ihmarbitre.h
 *
 * @brief Déclaration de la classe IHMArbitre
 * @author
 * @version 1.0
 *
 */

#include <QtWidgets>
#include "basededonnees.h"

/**
 * @def TEST_IHMARBITRE
 * @brief Pour le mode test (raccourcis clavier)
 */
#define TEST_IHMARBITRE

/**
 * @def PLEIN_ECRAN
 * @brief Pour le mode kiosque Raspberry Pi
 */
#define PLEIN_ECRAN

#define NB_SET_GAGNANTS 3

// Numéro de champs pour les requête SQL
#define COLONNE_idRencontre        0
#define COLONNE_idClubA            1
#define COLONNE_idClubW            2
#define COLONNE_nbPartiesGagnantes 3
#define COLONNE_estFinie           4
#define COLONNE_horodatage         5
#define COLONNE_nomClubA           6
#define COLONNE_nomClubW           7
#define COLONNE_nomClub            1
/**
 * @todo Définir les noms de colonnes pour les parties
 */

// QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMArbitre;
}
// QT_END_NAMESPACE

class CommunicationBluetooth;

/**
 * @class IHMArbitre
 * @brief Déclaration de la classe IHMArbitre
 * @details Cette classe s'occupe de l'affichage sur l'écran Raspberry Pi
 */
class IHMArbitre : public QMainWindow
{
    Q_OBJECT

  public:
    IHMArbitre(QWidget* parent = nullptr);
    ~IHMArbitre();

  private:
    Ui::IHMArbitre* ui; //!< la fenêtre graphique associée à cette classe
    CommunicationBluetooth*
                         communicationBluetooth; //!< la communication avec les modules
    BaseDeDonnees*       bdd;        //!< la relation vers la base de données
    QVector<QStringList> rencontres; //!< Les rencontres
    QVector<QStringList> joueursEquipeA; //!< Les joueurs du club A
    QVector<QStringList> joueursEquipeW; //!< Les joueurs du club W
    QVector<QStringList> clubs;          //!< Les clubs
    int                  nbSetJouer    = 0;
    bool                 partieEnCours = false;
    bool                 estGagnee     = false;
    bool                 aDejaEchanger = false;

    /**
     * @enum Ecran
     * @brief Définit les différents écrans de l'IHM
     */
    enum Ecran
    {
        Accueil,
        Rencontre,
        Partie,
        NbEcrans
    };
    /**
     * @enum Ecran
     * @brief Définit les différents écrans de l'IHM
     */
    enum EtatModule
    {
        Absent,   // 0
        Trouve,   // 1
        Connecte, // 2
        NbEtats
    };

    void initialiserCommunicationBluetooth();
    void installerGestionEvenements();
    void initialiserPageAccueil();
    void initialiserBDD();
    void afficherEtatBluetooth(QLabel* module, EtatModule etat);
    void chargerRencontres();
    void chargerRencontresASuppr();
    void chargerClubs();
    void chargerJoueurs();
    void envoiTrameScore();

#ifdef TEST_IHMARBITRE
    void creerRaccourcisClavier();
#endif

  public slots:
    void afficherEcran(IHMArbitre::Ecran ecran);
    void afficherEcranPrecedent();
    void afficherEcranSuivant();
    void fermerApplication();
    void demarrer();
    void afficherNetTrouve();
    void afficherEcranTrouve();
    void afficherScoreTrouve();
    void afficherConnexionNet();
    void afficherConnexionEcran();
    void afficherConnexionScore();
    void afficherDeconnexionNet();
    void afficherDeconnexionEcran();
    void afficherDeconnexionScore();
    void detecter();
    void declencherNet(int nbNets);
    void chargerPartiesSimples();
    void chargerPartiesDoubles();
    void demarrerPartieSimple();
    void demarrerPartieDouble();
    void demarrerRencontre();
    void creerRencontre();
    void supprimerRencontre();
    void echangerJoueur();
    void demarrerPartie();
    void ajoutPointG();
    void ajoutPointD();
    void retraitPointG();
    void retraitPointD();
};

#endif // IHMARBITRE_H
