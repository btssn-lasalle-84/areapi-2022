#ifndef RECEPTIONTRAME_H
#define RECEPTIONTRAME_H

/**
 * @file receptiontrame.h
 * @brief Déclaration de la classe ReceptionTrame
 * @version
 * @author
 */

#include <QString>
#include <QBluetoothSocket>
#include <QBluetoothServer>
#include <QBluetoothLocalDevice>

/**
 * @class ReceptionTrame
 * @brief Déclaration de la classe ReceptionTrame
 * @details gère la connexion avec le module d'arbitrage et les trames reçus
 */

class ReceptionTrame
{
    private:
        QString trame;
        QBluetoothServer server;
        QBluetoothSocket socket;
        QBluetoothLocalDevice appareilLocal;
        QString nomAppareilLocal;

    public:
        ReceptionTrame();
        ~ReceptionTrame();
        void connecterBluetooth();
        void rechercherPeripheriqueBluetooth();
        void deconnecterBluetooth();
        bool estConnecte();
        void demarrerServeur();
        void arreterServeur();

};

#endif // RECEPTIONTRAME_H
