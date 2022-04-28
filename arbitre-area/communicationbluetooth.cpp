#include "communicationbluetooth.h"
#include "ihmarbitre.h"
#include <QDebug>

CommunicationBluetooth::CommunicationBluetooth(IHMArbitre* ihmArbitre) :
    QObject(ihmArbitre), ihmArbitre(ihmArbitre), discoveryAgentDevice(nullptr),
    socketEcran(nullptr), socketNet(nullptr), socketScore(nullptr)
{
    qDebug() << Q_FUNC_INFO;
    if(!interfaceLocale.isValid())
    {
        // QMessageBox::critical(0, QString::fromUtf8("Erreur"),
        // QString::fromUtf8("Bluetooth désactivé !"));
        qDebug() << Q_FUNC_INFO << "Pas de Bluetooth !";
        return;
    }

    interfaceLocale.powerOn();

    qDebug() << Q_FUNC_INFO << interfaceLocale.name()
             << interfaceLocale.address().toString();

    discoveryAgentDevice = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgentDevice,
            SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this,
            SLOT(chercherModule(QBluetoothDeviceInfo)));

    discoveryAgentDevice->start();
}

CommunicationBluetooth::~CommunicationBluetooth()
{
    qDebug() << Q_FUNC_INFO;
}

void CommunicationBluetooth::connecter(const QBluetoothDeviceInfo device)
{
    qDebug() << Q_FUNC_INFO << device.name() << device.address();
    /**
     * @todo Détecter le module AREA (Ecran ? Net ? Score ?)
     */
    qDebug() << Q_FUNC_INFO << device.name().split("-");
    QStringList nomDevice = device.name().split("-", QString::SkipEmptyParts);
    if(nomDevice.at(1) == "net")
    {
        this->initSocketNet(device);
    }
    else
    {
        if(nomDevice.at(1) == "ecran")
        {
            this->initSocketEcran(device);
        }
        else
        {
            if(nomDevice.at(1) == "score")
            {
                this->initSocketNet(device);
            }
            else
            {
                qDebug() << Q_FUNC_INFO
                         << "Erreur module AREAPI non reconnu !!";
            }
        }
    }

    /*if (socketXXX == nullptr)
    {
        socketXXX = new
    QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        connect(socketXXX, SIGNAL(connected()), ihmArbitre,
    SLOT(afficherConnexionXXX())); connect(socketXXX,
    SIGNAL(disconnected()), ihmArbitre, SLOT(afficherDeconnexionXXX()));
    connect(socketXXX, SIGNAL(readyRead()), this, SLOT(recevoirXXX()));

        QBluetoothAddress adresse = QBluetoothAddress(device.address());
        QBluetoothUuid uuid = QBluetoothUuid(QBluetoothUuid::SerialPort);
        socketXXX->connectToService(adresse, uuid);
        socketXXX->open(QIODevice::ReadWrite);
    }*/
}

void CommunicationBluetooth::initSocketNet(const QBluetoothDeviceInfo device)
{
    if(socketNet == nullptr)
    {
        socketNet = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        connect(socketNet,
                SIGNAL(connected()),
                ihmArbitre,
                SLOT(afficherConnexionNet()));
        connect(socketNet,
                SIGNAL(disconnected()),
                ihmArbitre,
                SLOT(afficherDeconnexionNet()));
        connect(socketNet, SIGNAL(readyRead()), this, SLOT(recevoirNet()));

        QBluetoothAddress adresse = QBluetoothAddress(device.address());
        QBluetoothUuid    uuid    = QBluetoothUuid(QBluetoothUuid::SerialPort);
        socketNet->connectToService(adresse, uuid);
        socketNet->open(QIODevice::ReadWrite);
    }
}

void CommunicationBluetooth::initSocketEcran(const QBluetoothDeviceInfo device)
{
    if(socketEcran == nullptr)
    {
        socketEcran =
          new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        connect(socketEcran,
                SIGNAL(connected()),
                ihmArbitre,
                SLOT(afficherConnexionEcran()));
        connect(socketEcran,
                SIGNAL(disconnected()),
                ihmArbitre,
                SLOT(afficherDeconnexionEcran()));
        connect(socketEcran, SIGNAL(readyRead()), this, SLOT(recevoirEcran()));

        QBluetoothAddress adresse = QBluetoothAddress(device.address());
        QBluetoothUuid    uuid    = QBluetoothUuid(QBluetoothUuid::SerialPort);
        socketEcran->connectToService(adresse, uuid);
        socketEcran->open(QIODevice::ReadWrite);
    }
}

void CommunicationBluetooth::initSocketScore(const QBluetoothDeviceInfo device)
{
    if(socketScore == nullptr)
    {
        socketScore =
          new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        connect(socketScore,
                SIGNAL(connected()),
                ihmArbitre,
                SLOT(afficherConnexionScore()));
        connect(socketScore,
                SIGNAL(disconnected()),
                ihmArbitre,
                SLOT(afficherDeconnexionScore()));
        connect(socketScore, SIGNAL(readyRead()), this, SLOT(recevoirScore()));

        QBluetoothAddress adresse = QBluetoothAddress(device.address());
        QBluetoothUuid    uuid    = QBluetoothUuid(QBluetoothUuid::SerialPort);
        socketScore->connectToService(adresse, uuid);
        socketScore->open(QIODevice::ReadWrite);
    }
}

void CommunicationBluetooth::deconnecter()
{
    qDebug() << Q_FUNC_INFO;
    /**
     * @todo Déconnecter tous les modules AREA
     */
    this->deconnecter(Ecran);
    this->deconnecter(Net);
    this->deconnecter(Score);
}

void CommunicationBluetooth::deconnecter(Module module)
{
    qDebug() << Q_FUNC_INFO;
    switch(module)
    {
        case Module::Ecran:
            if(socketEcran->isOpen())
            {
                socketEcran->close();
            }
            break;
        case Module::Net:
            if(socketNet->isOpen())
            {
                socketNet->close();
            }
            break;
        case Module::Score:
            if(socketScore->isOpen())
            {
                socketScore->close();
            }
            break;
        default:
            qDebug() << Q_FUNC_INFO << "module inconnu !";
            break;
    }
}

void CommunicationBluetooth::chercherModule(QBluetoothDeviceInfo device)
{
    qDebug() << Q_FUNC_INFO << device.name() << device.address()
             << device.rssi();

    /**
     * @todo Détecter spécifiquement un module AREA
     */
    if(device.name().startsWith(PREFIXE_MODULE_AREA))
    {
        qDebug() << Q_FUNC_INFO << "un module AREAPI détecté !" << device.name()
                 << device.address() << device.rssi();
        /**
         * @todo Ajouter les modules AREA dans la liste
         */
        modulesAREA.push_back(device);
    }
}

void CommunicationBluetooth::recevoirEcran()
{
    qDebug() << Q_FUNC_INFO;
}

void CommunicationBluetooth::recevoirNet()
{
    qDebug() << Q_FUNC_INFO;
}

void CommunicationBluetooth::recevoirScore()
{
    qDebug() << Q_FUNC_INFO;
}
