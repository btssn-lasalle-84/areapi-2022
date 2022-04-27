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
#include <QBluetoothServiceInfo>
#include <QBluetoothDeviceInfo>

/**
 * @class ReceptionTrame
 * @brief Déclaration de la classe ReceptionTrame
 * @details gère la connexion avec le module d'arbitrage et les trames reçus
 */

static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
static const QString serviceNom(QStringLiteral("AREA-Afficheur"));

class ReceptionTrame : public QObject
{
    private:
        QString trame;
        QBluetoothServer *serveur;
        QBluetoothSocket socket;
        QBluetoothLocalDevice peripheriqueLocal;
        QString nomPeripheriqueLocal;
        QString adressePeripheriqueLocal;
        QBluetoothServiceInfo serviceInfo;

    public:
        ReceptionTrame(QObject *parent = 0);
        ~ReceptionTrame();
        void connecterBluetooth();
        void rechercherPeripheriqueBluetooth();
        void deconnecterBluetooth();
        bool estConnecte();
        void demarrerServeur();
        void arreterServeur();

    private slots:
        void nouveauClient();

    signals:

};

#endif // RECEPTIONTRAME_H
