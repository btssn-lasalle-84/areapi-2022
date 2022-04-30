#include "communicationbluetooth.h"
#include "ihmarbitre.h"
#include <QDebug>

CommunicationBluetooth::CommunicationBluetooth(IHMArbitre* ihmArbitre) :
    QObject(ihmArbitre), ihmArbitre(ihmArbitre), modulesAREA(Module::NbModules),
    discoveryAgentDevice(nullptr), socketEcran(nullptr), socketNet(nullptr),
    socketScore(nullptr)
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
}

CommunicationBluetooth::~CommunicationBluetooth()
{
    deconnecter();
    qDebug() << Q_FUNC_INFO;
}

void CommunicationBluetooth::connecter(Module module)
{
    if(modulesAREA.at(module).isValid())
    {
        QStringList nomDevice =
          modulesAREA.at(module).name().split("-", QString::SkipEmptyParts);
        qDebug() << Q_FUNC_INFO << modulesAREA.at(module).name()
                 << modulesAREA.at(module).address().toString() << nomDevice;
        this->initialiserSocketNet(modulesAREA.at(module));
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Erreur module AREAPI non valide !";
    }
}

void CommunicationBluetooth::deconnecter()
{
    qDebug() << Q_FUNC_INFO;
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
            delete socketEcran;
            socketEcran = nullptr;
            break;
        case Module::Net:
            if(socketNet->isOpen())
            {
                socketNet->close();
            }
            delete socketNet;
            socketNet = nullptr;
            break;
        case Module::Score:
            if(socketScore->isOpen())
            {
                socketScore->close();
            }
            delete socketScore;
            socketScore = nullptr;
            break;
        default:
            qDebug() << Q_FUNC_INFO << "module AREAPI inconnu !";
            break;
    }
}

void CommunicationBluetooth::demarrerRecherche()
{
    discoveryAgentDevice->start();
}

void CommunicationBluetooth::arreterRecherche()
{
    discoveryAgentDevice->stop();
}

void CommunicationBluetooth::chercherModule(QBluetoothDeviceInfo device)
{
    qDebug() << Q_FUNC_INFO << device.name() << device.address()
             << device.rssi();

    if(device.name().startsWith(PREFIXE_MODULE_AREA))
    {
        qDebug() << Q_FUNC_INFO << "module AREAPI détecté !" << device.name()
                 << device.address() << device.rssi();
        enregistrerModule(device);
    }
}

void CommunicationBluetooth::recevoirEcran()
{
    qDebug() << Q_FUNC_INFO;
}

void CommunicationBluetooth::recevoirNet()
{
    QByteArray donnees;
    donnees = socketNet->readAll();
    // qDebug() << Q_FUNC_INFO << donnees;

    trameNet += QString(donnees);
    if(trameNet.startsWith(DEBUT_TRAME) && trameNet.endsWith(FIN_TRAME))
    {
        qDebug() << Q_FUNC_INFO << trameNet;
        /**
         * @todo Traiter la trame puis signaler les données reçues
         */

        // prochaine réception
        trameNet.clear();
    }
}

void CommunicationBluetooth::recevoirScore()
{
    qDebug() << Q_FUNC_INFO;
}

void CommunicationBluetooth::enregistrerModule(
  const QBluetoothDeviceInfo device)
{
    QStringList nomDevice = device.name().split("-", QString::SkipEmptyParts);
    qDebug() << Q_FUNC_INFO << nomDevice.at(1);
    if(nomDevice.at(1) == "net")
    {
        // nouvelle détecion
        if(!modulesAREA[Module::Net].isValid())
        {
            modulesAREA[Module::Net] = device;
            qDebug() << Q_FUNC_INFO << "module NET trouvé !";
            emit moduleNetTrouve();
        }
    }
    else if(nomDevice.at(1) == "ecran")
    {
    }
    else if(nomDevice.at(1) == "score")
    {
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Erreur module AREAPI non reconnu !";
    }
}

void CommunicationBluetooth::initialiserSocketNet(
  const QBluetoothDeviceInfo device)
{
    if(socketNet == nullptr)
    {
        qDebug() << Q_FUNC_INFO << device.name() << device.address();
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

void CommunicationBluetooth::initialiserSocketEcran(
  const QBluetoothDeviceInfo device)
{
    if(socketEcran == nullptr)
    {
        qDebug() << Q_FUNC_INFO << device.name() << device.address();
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

void CommunicationBluetooth::initialiserSocketScore(
  const QBluetoothDeviceInfo device)
{
    if(socketScore == nullptr)
    {
        qDebug() << Q_FUNC_INFO << device.name() << device.address();
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
