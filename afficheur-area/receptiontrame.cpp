#include "receptiontrame.h"
#include <QDebug>

ReceptionTrame::ReceptionTrame(QObject* parent) :
    QObject(parent), serveur(nullptr), nomsTableArbitre(NB_TABLES),
    peripheriqueLocal(), nomPeripheriqueLocal(""), adressePeripheriqueLocal(""),
    serviceInfo()
{
    qDebug() << Q_FUNC_INFO;
    for(int i = 0; i < NB_TABLES; ++i)
        socketsTableArbitre.push_back(nullptr);
    activerBluetooth();
    demarrerServeur();
}

ReceptionTrame::~ReceptionTrame()
{
    arreterServeur();
    desactiverBluetooth();
    qDebug() << Q_FUNC_INFO;
}

void ReceptionTrame::activerBluetooth()
{
    qDebug() << Q_FUNC_INFO;
    if(!peripheriqueLocal.isValid())
    {
        qDebug() << Q_FUNC_INFO << "Bluetooth désactivé !";
        return;
    }
    else
    {
        peripheriqueLocal.powerOn();
        nomPeripheriqueLocal     = peripheriqueLocal.name();
        adressePeripheriqueLocal = peripheriqueLocal.address().toString();
        peripheriqueLocal.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
        qDebug() << Q_FUNC_INFO << nomPeripheriqueLocal
                 << adressePeripheriqueLocal << peripheriqueLocal.hostMode();
        peripheriquesDistants = peripheriqueLocal.connectedDevices();
        if(peripheriquesDistants.size())
            qDebug() << Q_FUNC_INFO << "peripheriquesDistants"
                     << peripheriquesDistants;
        connect(&peripheriqueLocal,
                SIGNAL(error(QBluetoothLocalDevice::Error)),
                this,
                SLOT(renvoyerErreurDevice(QBluetoothLocalDevice::Error)));
    }
}

void ReceptionTrame::desactiverBluetooth()
{
    this->peripheriqueLocal.setHostMode(QBluetoothLocalDevice::HostPoweredOff);
}

bool ReceptionTrame::estConnecte(int numeroTable) const
{
    if(!peripheriqueLocal.isValid() || numeroTable < 0 ||
       numeroTable >= NB_TABLES)
    {
        return false;
    }
    if(socketsTableArbitre.at(numeroTable))
    {
        qDebug() << Q_FUNC_INFO
                 << socketsTableArbitre.at(numeroTable)->isOpen();
        return socketsTableArbitre.at(numeroTable)->isOpen();
    }
    return false;
}

void ReceptionTrame::demarrerServeur()
{
    if(!peripheriqueLocal.isValid())
    {
        return;
    }
    if(serveur == nullptr)
    {
        serveur =
          new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
        connect(serveur, SIGNAL(newConnection()), this, SLOT(gererClient()));
        QBluetoothUuid uuid = QBluetoothUuid(serviceUuid);
        QString        serviceNom(nomPeripheriqueLocal);
        this->serviceInfo = this->serveur->listen(uuid, serviceNom);
        qDebug() << Q_FUNC_INFO << "attente connexion";
    }
}

void ReceptionTrame::arreterServeur()
{
    if(!peripheriqueLocal.isValid())
    {
        return;
    }
    if(!this->serveur)
    {
        return;
    }

    this->serviceInfo.unregisterService();

    for(int i = 0; i < NB_TABLES; ++i)
    {
        if(socketsTableArbitre.at(i))
        {
            if(socketsTableArbitre.at(i)->isOpen())
            {
                socketsTableArbitre.at(i)->close();
            }
            delete this->serveur;
            delete socketsTableArbitre.at(i);
            this->serveur          = nullptr;
            socketsTableArbitre[i] = nullptr;
        }
    }
}

void ReceptionTrame::gererClient()
{
    QBluetoothSocket* socket = this->serveur->nextPendingConnection();
    if(!socket)
    {
        return;
    }
    qDebug() << Q_FUNC_INFO << socket->peerName()
             << socket->peerAddress().toString();
    for(int numeroTable = 0; numeroTable < NB_TABLES; ++numeroTable)
    {
        if(socketsTableArbitre.at(numeroTable) == nullptr)
        {
            /**
             * @todo Vérifier avant si c'est bien un arbitre AREA
             */
            socketsTableArbitre[numeroTable] = socket;
            nomsTableArbitre[numeroTable]    = socket->peerName();
            connect(socket,
                    SIGNAL(disconnected()),
                    this,
                    SLOT(deconnecterSocket()));
            connect(socket, SIGNAL(readyRead()), this, SLOT(lireSocket()));
            connect(socket,
                    SIGNAL(error(QBluetoothSocket::SocketError)),
                    this,
                    SLOT(renvoyerErreurSocket(QBluetoothSocket::SocketError)));
            connect(socket,
                    SIGNAL(stateChanged(QBluetoothSocket::SocketState)),
                    this,
                    SLOT(changerEtatSocket(QBluetoothSocket::SocketState)));
            emit clientConnecte(socket->peerName(),
                                socket->peerAddress().toString());
            return;
        }
        /**
         * @todo Gérer si ce client est déjà connecté
         */
    }
}

QString ReceptionTrame::getNomPeripheriqueLocal() const
{
    return this->nomPeripheriqueLocal;
}

QString ReceptionTrame::getAdressePeripheriqueLocal() const
{
    return this->adressePeripheriqueLocal;
}

void ReceptionTrame::deconnecterSocket()
{
    qDebug() << Q_FUNC_INFO;
    emit clientDeconnecte();
}

void ReceptionTrame::lireSocket()
{
    // quel arbitre ?
    QBluetoothSocket* socket = qobject_cast<QBluetoothSocket*>(sender());
    qDebug() << Q_FUNC_INFO << socket->peerName()
             << socket->peerAddress().toString();
    trame += socket->readAll();
    // une trame AREA ?
    if(trame.startsWith(DEBUT_TRAME) && trame.endsWith(FIN_TRAME))
    {
        qDebug() << Q_FUNC_INFO << trame;
        /**
         * @todo Traiter la trame puis signaler les données reçues
         */

        // prochaine réception
        trame.clear();
    }
}

void ReceptionTrame::changerEtatSocket(QBluetoothSocket::SocketState etat)
{
    qDebug() << Q_FUNC_INFO << etat;
}

void ReceptionTrame::renvoyerErreurSocket(QBluetoothSocket::SocketError erreur)
{
    qDebug() << Q_FUNC_INFO << erreur;
}

void ReceptionTrame::renvoyerErreurDevice(QBluetoothLocalDevice::Error erreur)
{
    qDebug() << Q_FUNC_INFO << erreur;
}
