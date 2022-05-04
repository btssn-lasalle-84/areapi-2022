#ifndef IHMAFFICHEUR_H
#define IHMAFFICHEUR_H

/**
 * @file ihmafficheur.h
 *
 * @brief Déclaration de la classe IHMAfficheur
 * @author
 * @version 1.0
 *
 */

#include <QtWidgets>

/**
 * @def PLEIN_ECRAN
 * @brief Pour le mode kiosque Télévision
 */
//#define PLEIN_ECRAN

#define TEST_RELATIONS

namespace Ui
{
class IHMAfficheur;
}

class ReceptionTrame;

#ifdef TEST_RELATIONS
class Rencontre;
#endif

/**
 * @class IHMAfficheur
 * @brief Déclaration de la classe IHMAfficheur
 * @details Cette classe s'occupe de l'affichage sur l'écran Télévision
 */
class IHMAfficheur : public QMainWindow
{
    Q_OBJECT

  public:
    IHMAfficheur(QWidget* parent = nullptr);
    ~IHMAfficheur();

  private:
    Ui::IHMAfficheur* ui; //!< la fenêtre graphique associée à cette classe
    ReceptionTrame*   receptionTrame;
#ifdef TEST_RELATIONS
    Rencontre* rencontre;
#endif
};

#endif // IHMAFFICHEUR_H
