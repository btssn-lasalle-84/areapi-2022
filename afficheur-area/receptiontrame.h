#ifndef RECEPTIONTRAME_H
#define RECEPTIONTRAME_H

/**
 * @file receptiontrame.h
 * @brief Déclaration de la classe ReceptionTrame
 * @version
 * @author
 */

#include <QtBluetooth>
#include <QString>
#include <QByteArray>
#include <QList>
#include <QVector>

#define NB_TABLES 2

#define DEBUT_TRAME "$AREA"
#define FIN_TRAME   "\r\n"

static const QString serviceUuid(
  QStringLiteral("0000110a-0000-1000-8000-00805f9b34fb"));
// static const QString serviceNom(QStringLiteral("AREA-Afficheur"));

/**
 * @class ReceptionTrame
 * @brief Déclaration de la classe ReceptionTrame
 * @details gère la connexion avec le module d'arbitrage et les trames reçus
 */
class ReceptionTrame : public QObject
{
    Q_OBJECT
  private:
    QBluetoothServer*          serveur;
    QVector<QBluetoothSocket*> socketsTableArbitre;
    QVector<QString>           nomsTableArbitre;
    QBluetoothLocalDevice      peripheriqueLocal;
    QString                    nomPeripheriqueLocal;
    QString                    adressePeripheriqueLocal;
    QBluetoothServiceInfo      serviceInfo;
    QList<QBluetoothAddress>   peripheriquesDistants;
    bool                       connecte;
    QByteArray                 trame;

  public:
    ReceptionTrame(QObject* parent = 0);
    ~ReceptionTrame();
    void    activerBluetooth();
    void    desactiverBluetooth();
    bool    estConnecte(int numeroTable) const;
    void    demarrerServeur();
    void    arreterServeur();
    QString getNomPeripheriqueLocal() const;
    QString getAdressePeripheriqueLocal() const;

  public slots:
    void gererClient();
    void deconnecterSocket();
    void lireSocket();
    void changerEtatSocket(QBluetoothSocket::SocketState etat);
    void renvoyerErreurSocket(QBluetoothSocket::SocketError erreur);
    void renvoyerErreurDevice(QBluetoothLocalDevice::Error erreur);

  signals:
    void clientConnecte(QString nom, QString adresse);
    void clientDeconnecte();
};

#endif // RECEPTIONTRAME_H
