#ifndef COMMUNICATION_BLUETOOTH_H
#define COMMUNICATION_BLUETOOTH_H

#include <QObject>
#include <QtBluetooth>

#define PREFIXE_MODULE_AREA "areapi"
#define DEBUT_TRAME         "$AREA"
#define FIN_TRAME           "\r\n"

class IHMArbitre;

class CommunicationBluetooth : public QObject
{
    Q_OBJECT
  public:
    /**
     * @enum Module
     * @brief Définit les différents modules AREA
     */
    enum Module
    {
        Ecran,
        Net,
        Score,
        NbModules
    };
    /**
     * @enum TrameNet
     * @brief Définit les champs d'une trame NET ("$AREA", "NET", "1", "\r\n")
     */
    enum TrameNet
    {
        EnTete,
        Type,
        NbNets,
        Fin
    };

  private:
    IHMArbitre*                     ihmArbitre;
    QBluetoothLocalDevice           interfaceLocale;
    QVector<QBluetoothDeviceInfo>   modulesAREA;
    QBluetoothDeviceDiscoveryAgent* discoveryAgentDevice;
    QBluetoothDeviceInfo            moduleEcran;
    QBluetoothDeviceInfo            moduleNet;
    QBluetoothDeviceInfo            moduleScore;
    QBluetoothSocket*               socketEcran;
    QBluetoothSocket*               socketNet;
    QBluetoothSocket*               socketScore;
    QString                         trameEcran;
    QString                         trameNet;
    QString                         trameScore;

    void enregistrerModule(const QBluetoothDeviceInfo device);
    void initialiserSocketNet(const QBluetoothDeviceInfo device);
    void initialiserSocketEcran(const QBluetoothDeviceInfo device);
    void initialiserSocketScore(const QBluetoothDeviceInfo device);

  public:
    CommunicationBluetooth(IHMArbitre* ihmArbitre = nullptr);
    ~CommunicationBluetooth();

    void connecter(Module module);
    void deconnecter();
    void deconnecter(Module module);

  public slots:
    void demarrerRecherche();
    void arreterRecherche();
    void chercherModule(QBluetoothDeviceInfo device);
    void recevoirEcran();
    void recevoirNet();
    void recevoirScore();
    void detecterErreurSocket(QBluetoothSocket::SocketError erreur);
    void gererEtatSocket(QBluetoothSocket::SocketState etat);

  signals:
    void moduleEcranTrouve();
    void moduleNetTrouve();
    void moduleScoreTrouve();
    void netDetecte(int nbNets);
};

#endif // COMMUNICATION_BLUETOOTH_H
