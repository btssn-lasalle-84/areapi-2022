#ifndef COMMUNICATION_BLUETOOTH_H
#define COMMUNICATION_BLUETOOTH_H

#include <QObject>
#include <QtBluetooth>

#define PREFIXE_MODULE_AREA "area"

class IHMArbitre;

class CommunicationBluetooth : public QObject
{
    Q_OBJECT
  public:
    /**
     * @enum Module
     * @brief Définit les différents modules AREA
     *
     */
    enum Module
    {
        Ecran,
        Net,
        Score,
        NbModules
    };

  private:
    IHMArbitre*                     ihmArbitre;
    QBluetoothLocalDevice           interfaceLocale;
    QList<QBluetoothDeviceInfo>     modulesAREA;
    QBluetoothDeviceDiscoveryAgent* discoveryAgentDevice;
    QBluetoothSocket*               socketEcran;
    QBluetoothSocket*               socketNet;
    QBluetoothSocket*               socketScore;

  public:
    CommunicationBluetooth(IHMArbitre* ihmArbitre = nullptr);
    ~CommunicationBluetooth();

    void connecter(const QBluetoothDeviceInfo device);
    void deconnecter();
    void deconnecter(Module module);
    void initSocketNet(const QBluetoothDeviceInfo device);
    void initSocketEcran(const QBluetoothDeviceInfo device);
    void initSocketScore(const QBluetoothDeviceInfo device);

  public slots:
    void chercherModule(QBluetoothDeviceInfo device);
    void recevoirEcran();
    void recevoirNet();
    void recevoirScore();
};

#endif // COMMUNICATION_BLUETOOTH_H
