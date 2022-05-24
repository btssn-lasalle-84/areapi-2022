#include "ihmafficheur.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application
 * Afficheur-AREA
 * @author
 * @version 1.0
 *
 * @param argc
 * @param argv[]
 * @return int
 *
 */

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    IHMAfficheur w;

    a.setStyleSheet("QLabel { color: white; font: 75 20pt \"Ubuntu Condensed\"; }");

    w.show();

    return a.exec();
}
