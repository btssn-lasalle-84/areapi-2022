#include "receptiontrame.h"
#include "protocolearea.h"
#include <QDebug>

/**
 * @file receptiontrame.cpp
 * @brief Définition de la classe ReceptionTrame
 * @version 1.0
 * @author Enzo LADRIERE
 */

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
    qDebug() << Q_FUNC_INFO;
    QBluetoothSocket* socket = this->serveur->nextPendingConnection();
    if(!socket)
    {
        return;
    }
    // nouveau client
    qDebug() << Q_FUNC_INFO << socket->peerName()
             << socket->peerAddress().toString();
    for(int numeroTable = 0; numeroTable < NB_TABLES; ++numeroTable)
    {
        if(socketsTableArbitre.at(numeroTable) == nullptr)
        {
            /**
             * @todo Vérifier avant si c'est bien un arbitre AREA
             */
            qDebug() << Q_FUNC_INFO << socket << "numeroTable" << numeroTable;
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

QString ReceptionTrame::recupererNomTableArbitre(QBluetoothSocket* socket) const
{
    for(int i = 0; i < NB_TABLES; ++i)
    {
        if(socketsTableArbitre.at(i) == socket)
        {
            return nomsTableArbitre.at(i);
        }
    }
    return QString();
}

int ReceptionTrame::recupererNumeroTableArbitre(QBluetoothSocket* socket) const
{
    for(int i = 0; i < NB_TABLES; ++i)
    {
        if(socketsTableArbitre.at(i) == socket)
        {
            return i;
        }
    }
    return -1;
}

void ReceptionTrame::deconnecterSocket()
{
    // quel arbitre ?
    QBluetoothSocket* socket      = qobject_cast<QBluetoothSocket*>(sender());
    int               numeroTable = recupererNumeroTableArbitre(socket);
    if(numeroTable != -1)
    {
        qDebug() << Q_FUNC_INFO << socket << socket->peerName()
                 << socket->peerAddress().toString() << socket->state()
                 << recupererNomTableArbitre(socket);
        emit clientDeconnecte(recupererNomTableArbitre(socket));
        delete socketsTableArbitre[numeroTable];
        socketsTableArbitre[numeroTable] = nullptr;
        nomsTableArbitre[numeroTable]    = "";
    }
}

void ReceptionTrame::lireSocket()
{
    // quel arbitre ?
    QBluetoothSocket* socket = qobject_cast<QBluetoothSocket*>(sender());
    qDebug() << Q_FUNC_INFO << socket->peerName()
             << socket->peerAddress().toString();
    trame += socket->readAll();
    // une trame AREA ?
    bool trameValide = trame.startsWith(ProtocoleArea::DEBUT_TRAME) &&
                       trame.endsWith(ProtocoleArea::FIN_TRAME);
    if(trameValide)
    {
        qDebug() << Q_FUNC_INFO << trame;
        QList<QByteArray> decoupageTrame = decouperTrame();
        qDebug() << Q_FUNC_INFO << decoupageTrame;

        if(decoupageTrame[ProtocoleArea::ChampsTrame::TYPE] ==
           ProtocoleArea::RENCONTRE)
        {
            qDebug() << decoupageTrame[ProtocoleArea::ChampsTrame::TYPE]
                     << decoupageTrame.length();
            if(decoupageTrame.length() ==
               ProtocoleArea::ChampsRencontre::NbChampsRencontre + 1)
            {
                emit nouvelleTrameRencontre(
                  socket->peerName(),
                  decoupageTrame[ProtocoleArea::ChampsRencontre::NomClubA],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::NomClubW],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::NomJoueurA],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::PrenomJoueurA],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::NomJoueurB],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::PrenomJoueurB],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::NomJoueurC],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::PrenomJoueurC],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::NomJoueurD],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::PrenomJoueurD],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::NomJoueurW],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::PrenomJoueurW],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::NomJoueurX],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::PrenomJoueurX],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::NomJoueurY],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::PrenomJoueurY],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::NomJoueurZ],
                  decoupageTrame[ProtocoleArea::ChampsRencontre::PrenomJoueurZ]);
            }
            else
            {
                qDebug() << Q_FUNC_INFO << "Trame RENCONTRE invalide !";
            }
        }
        else if(decoupageTrame[ProtocoleArea::ChampsTrame::TYPE] ==
                ProtocoleArea::SIMPLE)
        {
            qDebug() << decoupageTrame[ProtocoleArea::ChampsTrame::TYPE]
                     << decoupageTrame.length();
            if(decoupageTrame.length() ==
               ProtocoleArea::ChampsPartieSimple::NbChampsPartieSimple + 1)
            {
                emit nouvelleTrameSimple(
                  socket->peerName(),
                  decoupageTrame[ProtocoleArea::ChampsPartieSimple::idPartie],
                  decoupageTrame[ProtocoleArea::ChampsPartieSimple::JoueurA],
                  decoupageTrame[ProtocoleArea::ChampsPartieSimple::ClassementJoueurA],
                  decoupageTrame[ProtocoleArea::ChampsPartieSimple::JoueurW],
                  decoupageTrame[ProtocoleArea::ChampsPartieSimple::ClassementJoueurW]);
            }
            else
            {
                qDebug() << Q_FUNC_INFO << "Trame SIMPLE invalide !";
            }
        }
        else if(decoupageTrame[ProtocoleArea::ChampsTrame::TYPE] ==
                ProtocoleArea::DOUBLE)
        {
            qDebug() << decoupageTrame[ProtocoleArea::ChampsTrame::TYPE]
                     << decoupageTrame.length();
            if(decoupageTrame.length() ==
               ProtocoleArea::ChampsPartieDouble::NbChampsPartieDouble + 1)
            {
                emit nouvelleTrameDouble(
                  socket->peerName(),
                  decoupageTrame[ProtocoleArea::ChampsPartieDouble::idPartieDouble],
                  decoupageTrame[ProtocoleArea::ChampsPartieDouble::JoueurA1],
                  decoupageTrame[ProtocoleArea::ChampsPartieDouble::ClassementA1],
                  decoupageTrame[ProtocoleArea::ChampsPartieDouble::JoueurA2],
                  decoupageTrame[ProtocoleArea::ChampsPartieDouble::ClassementA2],
                  decoupageTrame[ProtocoleArea::ChampsPartieDouble::JoueurW1],
                  decoupageTrame[ProtocoleArea::ChampsPartieDouble::ClassementW1],
                  decoupageTrame[ProtocoleArea::ChampsPartieDouble::JoueurW2],
                  decoupageTrame[ProtocoleArea::ChampsPartieDouble::ClassementW2]);
            }
        }
        else if(decoupageTrame[ProtocoleArea::ChampsTrame::TYPE] ==
                ProtocoleArea::SCORE)
        {
            qDebug() << decoupageTrame[ProtocoleArea::ChampsTrame::TYPE]
                     << decoupageTrame.length();
            if(decoupageTrame.length() == ProtocoleArea::ChampsPartieScore::NbChampsScore + 1)
            {
                emit nouvelleTrameScore(
                  socket->peerName(),
                  decoupageTrame[ProtocoleArea::ChampsPartieScore::idPartieScore],
                  decoupageTrame[ProtocoleArea::ChampsPartieScore::scoreJG],
                  decoupageTrame[ProtocoleArea::ChampsPartieScore::scoreJD],
                  decoupageTrame[ProtocoleArea::ChampsPartieScore::etatPartie],
                  decoupageTrame[ProtocoleArea::ChampsPartieScore::tempsMort],
                  decoupageTrame[ProtocoleArea::ChampsPartieScore::nbSetJG],
                  decoupageTrame[ProtocoleArea::ChampsPartieScore::nbSetJD],
                  decoupageTrame[ProtocoleArea::ChampsPartieScore::tourService],
                  decoupageTrame[ProtocoleArea::ChampsPartieScore::net]);
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "Trame inconnue !";
        }

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

QList<QByteArray> ReceptionTrame::decouperTrame()
{
    QList<QByteArray> decoupageTrame =
      trame.split(ProtocoleArea::DELIMITEUR_TRAME);

    return decoupageTrame;
}
