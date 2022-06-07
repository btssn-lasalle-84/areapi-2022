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
    discoveryAgentService = new QBluetoothServiceDiscoveryAgent(this);
    connect(discoveryAgentService,
            SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this,
            SLOT(chercherService(QBluetoothServiceInfo)));
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
        qDebug() << Q_FUNC_INFO << module << modulesAREA.at(module).name()
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
    qDebug() << Q_FUNC_INFO << module;
    switch(module)
    {
        case Module::Ecran:
            if(socketEcran != nullptr &&
               socketEcran->state() == QBluetoothSocket::ConnectedState)
            {
                socketEcran->disconnectFromService();
                // socketEcran->close();
            }
            delete socketEcran;
            socketEcran = nullptr;
            break;
        case Module::Net:
            if(socketNet != nullptr &&
               socketNet->state() == QBluetoothSocket::ConnectedState)
            {
                socketNet->disconnectFromService();
                // socketNet->close();
            }
            delete socketNet;
            socketNet = nullptr;
            break;
        case Module::Score:
            if(socketScore != nullptr &&
               socketScore->state() == QBluetoothSocket::ConnectedState)
            {
                socketScore->disconnectFromService();
                // socketScore->close();
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
    if(!discoveryAgentDevice->isActive())
    {
        qDebug() << Q_FUNC_INFO;
        discoveryAgentDevice->start();
    }
}

void CommunicationBluetooth::arreterRecherche()
{
    qDebug() << Q_FUNC_INFO;
    discoveryAgentDevice->stop();
}

void CommunicationBluetooth::demarrerRechercheService()
{
    if(!discoveryAgentService->isActive())
    {
        qDebug() << Q_FUNC_INFO;
        discoveryAgentService->start();
    }
}

void CommunicationBluetooth::arreterRechercheService()
{
    qDebug() << Q_FUNC_INFO;
    discoveryAgentService->stop();
}

void CommunicationBluetooth::chercherModule(QBluetoothDeviceInfo device)
{
    // qDebug() << Q_FUNC_INFO << device.name() << device.address() <<
    // device.rssi();

    if(device.name().startsWith(PREFIXE_MODULE_AREA))
    {
        qDebug() << Q_FUNC_INFO << "module AREAPI détecté !" << device.name()
                 << device.address() << device.rssi();
        enregistrerModule(device);
    }
}

void CommunicationBluetooth::chercherService(QBluetoothServiceInfo service)
{
    // qDebug() << Q_FUNC_INFO << "module AREAPI détecté !" <<
    // service.serviceName() << service.serviceUuid() << service.device().name()
    // << service.device().address() << service.device().rssi();
    if(service.device().name().startsWith(PREFIXE_MODULE_AREA))
    {
        qDebug() << Q_FUNC_INFO << "module AREAPI détecté !"
                 << service.serviceName() << service.serviceUuid()
                 << service.device().name() << service.device().address()
                 << service.device().rssi();
        enregistrerModule(service.device());
    }
}

void CommunicationBluetooth::gererConnexionEcran()
{
    qDebug() << Q_FUNC_INFO << socketEcran->state();
    if(socketEcran->state() == QBluetoothSocket::ConnectedState)
    {
        emit moduleEcranConnecte();
        if(!trameEnvoiEcran.isEmpty())
        {
            qDebug() << Q_FUNC_INFO << modulesAREA.at(Module::Ecran).name()
                     << modulesAREA.at(Module::Ecran).address().toString()
                     << trameEnvoiEcran;
            socketEcran->write(trameEnvoiEcran.toLatin1());
            trameEnvoiEcran.clear();
        }
    }
    else
    {
        emit moduleEcranDeconnecte();
    }
}

void CommunicationBluetooth::gererConnexionNet()
{
    qDebug() << Q_FUNC_INFO << socketNet->state();
    if(socketNet->state() == QBluetoothSocket::ConnectedState)
    {
        emit moduleNetConnecte();
        if(!trameEnvoiNet.isEmpty())
        {
            qDebug() << Q_FUNC_INFO << modulesAREA.at(Module::Net).name()
                     << modulesAREA.at(Module::Net).address().toString()
                     << trameEnvoiNet;
            socketNet->write(trameEnvoiNet.toLatin1());
            trameEnvoiNet.clear();
        }
    }
    else
    {
        emit moduleNetDeconnecte();
    }
}

void CommunicationBluetooth::gererConnexionScore()
{
    qDebug() << Q_FUNC_INFO << socketScore->state();
    if(socketScore->state() == QBluetoothSocket::ConnectedState)
    {
        emit moduleScoreConnecte();
        if(!trameEnvoiScore.isEmpty())
        {
            qDebug() << Q_FUNC_INFO << modulesAREA.at(Module::Score).name()
                     << modulesAREA.at(Module::Score).address().toString()
                     << trameEnvoiScore;
            socketScore->write(trameEnvoiScore.toLatin1());
            trameEnvoiScore.clear();
        }
    }
    else
    {
        emit moduleScoreDeconnecte();
    }
}

void CommunicationBluetooth::envoyer(Module module, QString trame)
{
    if(modulesAREA.at(module).isValid())
    {
        QStringList nomDevice =
          modulesAREA.at(module).name().split("-", QString::SkipEmptyParts);

        switch(module)
        {
            case Module::Ecran:
                trameEnvoiEcran = trame;
                connecter(module);
                if(socketEcran->state() == QBluetoothSocket::ConnectedState)
                {
                    qDebug() << Q_FUNC_INFO << modulesAREA.at(module).name()
                             << modulesAREA.at(module).address().toString()
                             << nomDevice << trameEnvoiEcran;
                    socketEcran->write(trame.toLatin1());
                    trameEnvoiEcran.clear();
                }
                break;
            case Module::Net:
                trameEnvoiNet = trame;
                connecter(module);
                if(socketNet->state() == QBluetoothSocket::ConnectedState)
                {
                    qDebug() << Q_FUNC_INFO << modulesAREA.at(module).name()
                             << modulesAREA.at(module).address().toString()
                             << nomDevice << trameReceptionNet;
                    socketNet->write(trame.toLatin1());
                    trameEnvoiNet.clear();
                }
                break;
            case Module::Score:
                trameEnvoiScore = trame;
                connecter(module);
                if(socketScore->state() == QBluetoothSocket::ConnectedState)
                {
                    qDebug() << Q_FUNC_INFO << modulesAREA.at(module).name()
                             << modulesAREA.at(module).address().toString()
                             << nomDevice << trameReceptionScore;
                    socketScore->write(trame.toLatin1());
                    trameEnvoiScore.clear();
                }
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

void CommunicationBluetooth::recevoirEcran()
{
    QByteArray donnees;
    donnees = socketEcran->readAll();
    // qDebug() << Q_FUNC_INFO << donnees;

    trameReceptionEcran += QString(donnees);
    if(trameReceptionEcran.startsWith(DEBUT_TRAME) &&
       trameReceptionEcran.endsWith(FIN_TRAME))
    {
        qDebug() << Q_FUNC_INFO << trameReceptionEcran;
        trameReceptionEcran.clear();
    }
}

void CommunicationBluetooth::recevoirNet()
{
    QByteArray donnees;
    donnees = socketNet->readAll();
    // qDebug() << Q_FUNC_INFO << donnees;

    trameReceptionNet += QString(donnees);
    if(trameReceptionNet.startsWith(DEBUT_TRAME) &&
       trameReceptionNet.endsWith(FIN_TRAME))
    {
        QStringList champsTrames = trameReceptionNet.split(";");
        qDebug() << Q_FUNC_INFO << champsTrames;
        if(champsTrames.at(TrameNet::Type) == "NET")
        {
            emit netDetecte(champsTrames.at(TrameNet::NbNets).toInt());
        }
        // prochaine réception
        trameReceptionNet.clear();
    }
}

void CommunicationBluetooth::recevoirScore()
{
    QByteArray donnees;
    donnees = socketScore->readAll();
    // qDebug() << Q_FUNC_INFO << donnees;

    trameReceptionScore += QString(donnees);
    if(trameReceptionScore.startsWith(DEBUT_TRAME) &&
       trameReceptionScore.endsWith(FIN_TRAME))
    {
        qDebug() << Q_FUNC_INFO << trameReceptionScore;
        // prochaine réception
        trameReceptionScore.clear();
    }
}

void CommunicationBluetooth::detecterErreurSocket(
  QBluetoothSocket::SocketError erreur)
{
    qDebug() << Q_FUNC_INFO << erreur;
}

void CommunicationBluetooth::gererEtatSocket(QBluetoothSocket::SocketState etat)
{
    QBluetoothSocket* socket = qobject_cast<QBluetoothSocket*>(sender());
    qDebug() << Q_FUNC_INFO << socket << socket->peerName()
             << socket->peerAddress().toString() << socket->state() << etat;
    qDebug() << Q_FUNC_INFO << etat;
}

void CommunicationBluetooth::enregistrerModule(
  const QBluetoothDeviceInfo device)
{
    QStringList nomDevice = device.name().split("-", QString::SkipEmptyParts);
    qDebug() << Q_FUNC_INFO << nomDevice.at(1);
    if(nomDevice.at(1) == "net")
    {
        // nouvelle détection
        if(!modulesAREA[Module::Net].isValid())
        {
            modulesAREA[Module::Net] = device;
            qDebug() << Q_FUNC_INFO << "module NET trouvé !";
            emit moduleNetTrouve();
        }
    }
    else if(nomDevice.at(1) == "ecran")
    {
        // nouvelle détection
        if(!modulesAREA[Module::Ecran].isValid())
        {
            modulesAREA[Module::Ecran] = device;
            qDebug() << Q_FUNC_INFO << "module ECRAN trouvé !";
            emit moduleEcranTrouve();
        }
    }
    else if(nomDevice.at(1) == "score")
    {
        // nouvelle détection
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
    if(!modulesAREA[Module::Net].isValid())
        return;

    // un seul module connectable à la fois ;(
    deconnecter(Module::Ecran);
    deconnecter(Module::Score);

    if(socketNet == nullptr)
    {
        qDebug() << Q_FUNC_INFO << device.name() << device.address();
        socketNet = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        connect(socketNet,
                SIGNAL(connected()),
                this,
                SLOT(gererConnexionNet()));
        connect(socketNet,
                SIGNAL(disconnected()),
                this,
                SLOT(gererConnexionNet()));
        connect(socketNet,
                SIGNAL(error(QBluetoothSocket::SocketError)),
                this,
                SLOT(detecterErreurSocket(QBluetoothSocket::SocketError)));
        connect(socketNet,
                SIGNAL(stateChanged(QBluetoothSocket::SocketState)),
                this,
                SLOT(gererEtatSocket(QBluetoothSocket::SocketState)));
        connect(socketNet, SIGNAL(readyRead()), this, SLOT(recevoirNet()));
    }
    else
    {
        qDebug() << Q_FUNC_INFO << device.name() << device.address()
                 << socketNet->state();
    }

    if(socketNet->state() == QBluetoothSocket::ConnectingState)
    {
        socketNet->disconnectFromService();
    }

    if(socketNet->state() != QBluetoothSocket::ConnectedState)
    {
        QBluetoothAddress adresse =
          QBluetoothAddress(modulesAREA[Module::Net].address());
        QBluetoothUuid uuid = QBluetoothUuid(QBluetoothUuid::SerialPort);
        socketNet->connectToService(adresse, uuid);
        // socketNet->open(QIODevice::ReadWrite);
    }
}

void CommunicationBluetooth::initialiserSocketEcran(
  const QBluetoothDeviceInfo device)
{
    if(!modulesAREA[Module::Ecran].isValid())
        return;

    // un seul module connectable à la fois ;(
    deconnecter(Module::Net);
    deconnecter(Module::Score);

    if(socketEcran == nullptr)
    {
        qDebug() << Q_FUNC_INFO << device.name() << device.address();
        socketEcran =
          new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        connect(socketEcran,
                SIGNAL(connected()),
                this,
                SLOT(gererConnexionEcran()));
        connect(socketEcran,
                SIGNAL(disconnected()),
                this,
                SLOT(gererConnexionEcran()));
        connect(socketEcran,
                SIGNAL(error(QBluetoothSocket::SocketError)),
                this,
                SLOT(detecterErreurSocket(QBluetoothSocket::SocketError)));
        connect(socketEcran,
                SIGNAL(stateChanged(QBluetoothSocket::SocketState)),
                this,
                SLOT(gererEtatSocket(QBluetoothSocket::SocketState)));
        connect(socketEcran, SIGNAL(readyRead()), this, SLOT(recevoirEcran()));
    }

    qDebug() << Q_FUNC_INFO << device.name() << device.address()
             << socketEcran->state() << "!!!!!!!!!!!";
    if(socketEcran->state() == QBluetoothSocket::ConnectingState)
    {
        socketEcran->disconnectFromService();
    }

    if(socketEcran->state() != QBluetoothSocket::ConnectedState)
    {
        QBluetoothAddress adresse =
          QBluetoothAddress(modulesAREA[Module::Ecran].address());
        QBluetoothUuid uuid = QBluetoothUuid(QBluetoothUuid::SerialPort);
        qDebug() << Q_FUNC_INFO << uuid;
        socketEcran->connectToService(adresse, uuid);
        // bool retour = socketEcran->open(QIODevice::ReadWrite);
    }
}

void CommunicationBluetooth::initialiserSocketScore(
  const QBluetoothDeviceInfo device)
{
    if(!modulesAREA[Module::Score].isValid())
        return;

    // un seul module connectable à la fois ;(
    deconnecter(Module::Net);
    deconnecter(Module::Ecran);

    if(socketScore == nullptr)
    {
        qDebug() << Q_FUNC_INFO << device.name() << device.address()
                 << device.name() << device.address();
        socketScore =
          new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        connect(socketScore,
                SIGNAL(connected()),
                this,
                SLOT(gererConnexionScore()));
        connect(socketScore,
                SIGNAL(disconnected()),
                this,
                SLOT(gererConnexionScore()));
        connect(socketScore,
                SIGNAL(error(QBluetoothSocket::SocketError)),
                this,
                SLOT(detecterErreurSocket(QBluetoothSocket::SocketError)));
        connect(socketScore,
                SIGNAL(stateChanged(QBluetoothSocket::SocketState)),
                this,
                SLOT(gererEtatSocket(QBluetoothSocket::SocketState)));
        connect(socketScore, SIGNAL(readyRead()), this, SLOT(recevoirScore()));
    }

    qDebug() << Q_FUNC_INFO << socketScore->state();

    if(socketScore->state() == QBluetoothSocket::ConnectingState)
    {
        qDebug() << Q_FUNC_INFO << "disconnectFromService";
        socketScore->disconnectFromService();
    }
    if(socketScore->state() != QBluetoothSocket::ConnectedState)
    {
        QBluetoothAddress adresse =
          QBluetoothAddress(modulesAREA[Module::Score].address());
        QBluetoothUuid uuid = QBluetoothUuid(QBluetoothUuid::SerialPort);
        socketScore->connectToService(adresse, uuid);
        // socketScore->open(QIODevice::ReadWrite);
    }
}
