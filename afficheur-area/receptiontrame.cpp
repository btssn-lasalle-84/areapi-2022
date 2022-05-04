#include "receptiontrame.h"
#include <QDebug>
#include <QMessageBox>

ReceptionTrame::ReceptionTrame(QObject *parent) :
            QObject(parent), trame(""), serveur(nullptr),
            socket(nullptr),peripheriqueLocal(), nomPeripheriqueLocal(""), adressePeripheriqueLocal(""), serviceInfo(), connecte(false)
{
    qDebug() << Q_FUNC_INFO;
    connecterBluetooth();
    demarrerServeur();
}

ReceptionTrame::~ReceptionTrame()
{
    qDebug() << Q_FUNC_INFO;
    arreterServeur();
    this->peripheriqueLocal.setHostMode(QBluetoothLocalDevice::HostPoweredOff);
}

void ReceptionTrame::connecterBluetooth()
{
    qDebug() << Q_FUNC_INFO;
    if(!peripheriqueLocal.isValid())
    {
        QMessageBox::critical(0, QString::fromUtf8("Erreur"), QString::fromUtf8("Bluetooth désactivé !"));
        return;
    }
    else
    {
        qDebug() << peripheriqueLocal.hostMode();
        peripheriqueLocal.powerOn();
        nomPeripheriqueLocal = peripheriqueLocal.name();
        adressePeripheriqueLocal = peripheriqueLocal.address().toString();
        peripheriqueLocal.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
        qDebug() << peripheriqueLocal.hostMode();

        connect(&peripheriqueLocal,
                SIGNAL(error(QBluetoothLocalDevice::Error)),
                this,
                SLOT(renvoieBluetoothErreur(QBluetoothLocalDevice::Error)));
    }
}

void ReceptionTrame::deconnecterBluetooth()
{
}

bool ReceptionTrame::estConnecte()
{
    return false;
}

void ReceptionTrame::demarrerServeur()
{
    qDebug() << Q_FUNC_INFO;
    if(!serveur)
    {
        serveur = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
        connect(serveur,
                SIGNAL(newConnection()),
                this,
                SLOT(gererClient()));
        QBluetoothUuid uuid = QBluetoothUuid(serviceUuid);
        this->serviceInfo = this->serveur->listen(uuid, serviceNom);
        qDebug() << serviceInfo;
    }
}

void ReceptionTrame::arreterServeur()
{
    if (!this->serveur)
    {
        return;
    }

    this->serviceInfo.unregisterService();

    if(socket)
    {
        if(this->socket->isOpen())
        {
            this->socket->close();
            delete this->socket;
            this->socket = nullptr;
        }

        delete this->serveur;
        this->serveur = nullptr;
    }
}

void ReceptionTrame::gererClient()
{
        qDebug() << Q_FUNC_INFO;
        socket = serveur->nextPendingConnection();
        if (!this->socket)
        {
            return;
        }

        /*
        connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecterSocket()));
        connect(socket, SIGNAL(readyRead()), this, SLOT(lireSocket()));
        connect(socket, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(renvoyerErreurSocket(QBluetoothSocket::SocketError)));
        connect(socket, SIGNAL(stateChanged(QBluetoothSocket::SocketState)), this, SLOT(changerEtatSocket(QBluetoothSocket::SocketState)));
        */

        connecte = true;
}

QString ReceptionTrame::getNomPeripheriqueLocal()
{
    return this->nomPeripheriqueLocal;
}

QString ReceptionTrame::getAdressePeripheriqueLocal()
{
    return this->adressePeripheriqueLocal;
}

void ReceptionTrame::deconnecterSocket()
{
    qDebug() << Q_FUNC_INFO;
    connecte = false;
    //emit clientDeconnecte(); << Pour IHM <
}

void ReceptionTrame::lireSocket()
{
    qDebug() << Q_FUNC_INFO;
    trame += this->socket->readAll();
}

void ReceptionTrame::renvoyerErreurSocket(QBluetoothSocket::SocketError erreur)
{
    qDebug() << Q_FUNC_INFO << erreur;
}

void ReceptionTrame::changerEtatSocket(QBluetoothSocket::SocketState etat)
{
    qDebug() << Q_FUNC_INFO << etat;
}

void ReceptionTrame::renvoieBluetoothErreur(QBluetoothLocalDevice::Error erreur)
{
    qDebug() << Q_FUNC_INFO << erreur;
}


