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
        switch(module)
        {
            case Module::Ecran:
                this->initialiserSocketEcran(modulesAREA.at(module));
                break;
            case Module::Net:
                this->initialiserSocketNet(modulesAREA.at(module));
                break;
            case Module::Score:
                this->initialiserSocketScore(modulesAREA.at(module));
                break;
            default:
                qDebug() << Q_FUNC_INFO << "module AREAPI inconnu !";
                break;
        }
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
            if(socketEcran != nullptr && socketEcran->isOpen())
            {
                socketEcran->close();
            }
            delete socketEcran;
            socketEcran = nullptr;
            break;
        case Module::Net:
            if(socketNet != nullptr && socketNet->isOpen())
            {
                socketNet->close();
            }
            delete socketNet;
            socketNet = nullptr;
            break;
        case Module::Score:
            if(socketScore != nullptr && socketScore->isOpen())
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
    QByteArray donnees;
    donnees = socketEcran->readAll();
    // qDebug() << Q_FUNC_INFO << donnees;

    trameEcran += QString(donnees);
    if(trameEcran.startsWith(DEBUT_TRAME) && trameEcran.endsWith(FIN_TRAME))
    {
        qDebug() << Q_FUNC_INFO << trameEcran;
        trameEcran.clear();
    }
}

void CommunicationBluetooth::recevoirNet()
{
    QByteArray donnees;
    donnees = socketNet->readAll();
    // qDebug() << Q_FUNC_INFO << donnees;

    trameNet += QString(donnees);
    if(trameNet.startsWith(DEBUT_TRAME) && trameNet.endsWith(FIN_TRAME))
    {
        QStringList champsTrames = trameNet.split(";");
        qDebug() << Q_FUNC_INFO << champsTrames;
        if(champsTrames.at(TrameNet::Type) == "NET")
        {
            emit netDetecte(champsTrames.at(TrameNet::NbNets).toInt());
        }
        // prochaine réception
        trameNet.clear();
    }
}

void CommunicationBluetooth::recevoirScore()
{
    QByteArray donnees;
    donnees = socketScore->readAll();
    // qDebug() << Q_FUNC_INFO << donnees;

    trameScore += QString(donnees);
    if(trameScore.startsWith(DEBUT_TRAME) && trameScore.endsWith(FIN_TRAME))
    {
        qDebug() << Q_FUNC_INFO << trameScore;
        // prochaine réception
        trameScore.clear();
    }
}

void CommunicationBluetooth::detecterErreurSocket(
  QBluetoothSocket::SocketError erreur)
{
    qDebug() << Q_FUNC_INFO << erreur;
}

void CommunicationBluetooth::gererEtatSocket(QBluetoothSocket::SocketState etat)
{
    qDebug() << Q_FUNC_INFO << etat;
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
        // nouvelle détecion
        if(!modulesAREA[Module::Ecran].isValid())
        {
            modulesAREA[Module::Ecran] = device;
            qDebug() << Q_FUNC_INFO << "module ECRAN trouvé !";
            emit moduleEcranTrouve();
        }
    }
    else if(nomDevice.at(1) == "score")
    {
        // nouvelle détecion
        if(!modulesAREA[Module::Score].isValid())
        {
            modulesAREA[Module::Score] = device;
            qDebug() << Q_FUNC_INFO << "module SCORE trouvé !";
            emit moduleScoreTrouve();
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "Erreur module AREAPI non reconnu !";
        }
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
        connect(socketNet,
                SIGNAL(error(QBluetoothSocket::SocketError)),
                this,
                SLOT(detecterErreurSocket(QBluetoothSocket::SocketError)));
        connect(socketNet,
                SIGNAL(stateChanged(QBluetoothSocket::SocketState)),
                this,
                SLOT(gererEtatSocket(QBluetoothSocket::SocketState)));
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
        connect(socketScore,
                SIGNAL(error(QBluetoothSocket::SocketError)),
                this,
                SLOT(detecterErreurSocket(QBluetoothSocket::SocketError)));
        connect(socketScore,
                SIGNAL(stateChanged(QBluetoothSocket::SocketState)),
                this,
                SLOT(gererEtatSocket(QBluetoothSocket::SocketState)));
        connect(socketScore, SIGNAL(readyRead()), this, SLOT(recevoirScore()));

        QBluetoothAddress adresse = QBluetoothAddress(device.address());
        QBluetoothUuid    uuid    = QBluetoothUuid(QBluetoothUuid::SerialPort);
        socketScore->connectToService(adresse, uuid);
        socketScore->open(QIODevice::ReadWrite);
    }
}
