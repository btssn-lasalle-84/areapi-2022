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
#define PLEIN_ECRAN

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMAfficheur;
}
QT_END_NAMESPACE

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
};

#endif // IHMAFFICHEUR_H
