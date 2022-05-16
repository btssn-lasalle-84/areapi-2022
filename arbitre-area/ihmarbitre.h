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

    /**
     * @enum Ecran
     * @brief Définit les différents écrans de l'IHM
     */
    enum Ecran
    {
        Accueil,
        AccueilRencontre,
        CreationRencontre,
        CreationTournoi,
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
    void afficherEtatBluetooth(QLabel* module, EtatModule etat);

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
};

#endif // IHMARBITRE_H
