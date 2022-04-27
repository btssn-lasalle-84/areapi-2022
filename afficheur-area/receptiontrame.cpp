#include "receptiontrame.h"

ReceptionTrame::ReceptionTrame(QObject *parent) :
            QObject(parent), trame(""), serveur(NULL),
            socket(),peripheriqueLocal(), nomPeripheriqueLocal("")
{
}

ReceptionTrame::~ReceptionTrame()
{
}

void ReceptionTrame::connecterBluetooth()
{
    if(peripheriqueLocal.isValid())
    {
        qDebug() << peripheriqueLocal.hostMode();

        this->peripheriqueLocal.powerOn();
        this->nomPeripheriqueLocal = this->peripheriqueLocal.name();
        this->adressePeripheriqueLocal = this->peripheriqueLocal.address().toString();
        QList<QBluetoothAddress> appareilconnectes;
        appareilconnectes = this->peripheriqueLocal.connectedDevices();
        peripheriqueLocal.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    }
    else
    {

    }
}

void ReceptionTrame::rechercherPeripheriqueBluetooth()
{
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
    if(!serveur)
    {
        serveur = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
        connect(serveur, SIGNAL(newConnection()), this, SLOT(nouveauClient()));
        QBluetoothUuid uuid = QBluetoothUuid(serviceUuid);
        serviceInfo = serveur->listen(uuid, serviceNom);
    }
}


void ReceptionTrame::arreterServeur()
{
}

void ReceptionTrame::nouveauClient()
{
}
