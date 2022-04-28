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

//QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMArbitre;
}
//QT_END_NAMESPACE

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
    CommunicationBluetooth *communicationBluetooth;

    /**
     * @enum Ecran
     * @brief Définit les différents écrans de l'IHM
     *
     */
    enum Ecran
    {
        AccueilRencontre = 0,
        CreationRencontre,
        CreationTournoi,
        NbEcrans
    };

#ifdef TEST_IHMARBITRE
    void creerRaccourcisClavier();
#endif

  public slots:
    void afficherEcran(IHMArbitre::Ecran ecran);
    void afficherEcranPrecedent();
    void afficherEcranSuivant();
    void fermerApplication();
};

#endif // IHMARBITRE_H
