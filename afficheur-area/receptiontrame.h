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
#include <QByteArray>

/**
 * @class ReceptionTrame
 * @brief Déclaration de la classe ReceptionTrame
 * @details gère la connexion avec le module d'arbitrage et les trames reçus
 */

static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
static const QString serviceNom(QStringLiteral("AREA-Afficheur"));

class ReceptionTrame : public QObject
{
    Q_OBJECT
    private:
        QByteArray trame;
        QBluetoothServer *serveur;
        QBluetoothSocket *socket;
        QBluetoothLocalDevice peripheriqueLocal;
        QString nomPeripheriqueLocal;
        QString adressePeripheriqueLocal;
        QBluetoothServiceInfo serviceInfo;
        bool connecte;

    public:
        ReceptionTrame(QObject *parent = 0);
        ~ReceptionTrame();
        void connecterBluetooth();
        void deconnecterBluetooth();
        bool estConnecte();
        void demarrerServeur();
        void arreterServeur();
        QString getNomPeripheriqueLocal();
        QString getAdressePeripheriqueLocal();

    public slots:
        void gererClient();
        void deconnecterSocket();
        void lireSocket();
        void renvoyerErreurSocket(QBluetoothSocket::SocketError erreur);
        void changerEtatSocket(QBluetoothSocket::SocketState etat);
        void renvoieBluetoothErreur(QBluetoothLocalDevice::Error erreur);

    signals:

};

#endif // RECEPTIONTRAME_H
