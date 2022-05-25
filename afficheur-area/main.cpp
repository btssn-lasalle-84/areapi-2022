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

    //a.setStyleSheet("QLabel { background-color: rgb(0, 0, 0); \
                              color: rgb(255, 255, 0); \
                              font: 87 16pt \"Lato Black\" }");

    //background-color: rgb(0, 0, 0);
    //color: rgb(255, 255, 0);
    //font: 87 13pt "Lato Black";


    w.show();

    return a.exec();
}
