#include "receptiontrame.h"

ReceptionTrame::ReceptionTrame() :
                trame(""), server(QBluetoothServiceInfo::RfcommProtocol), socket(),
                appareilLocal(), nomAppareilLocal("")
{
}

ReceptionTrame::~ReceptionTrame()
{
}

void ReceptionTrame::connecterBluetooth()
{
    if(appareilLocal.isValid())
    {
        this->appareilLocal.powerOn();
        this->nomAppareilLocal = this->appareilLocal.name();
        QList<QBluetoothAddress> appareilconnectes;
        appareilconnectes = this->appareilLocal.connectedDevices();
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
}


void ReceptionTrame::arreterServeur()
{
}
