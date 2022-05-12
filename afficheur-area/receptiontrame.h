#ifndef RECEPTIONTRAME_H
#define RECEPTIONTRAME_H

/**
 * @file receptiontrame.h
 * @brief Déclaration de la classe ReceptionTrame
 * @version 1.0
 * @author Enzo LADRIERE
 */

#include <QtBluetooth>
#include <QString>
#include <QByteArray>
#include <QList>
#include <QVector>

#define NB_TABLES            2
#define NOM_MODULE_ARBITRE_1 "AREAPI-arbitre-1"
#define NOM_MODULE_ARBITRE_2 "AREAPI-arbitre-2"

static const QString serviceUuid(
  QStringLiteral("0000110a-0000-1000-8000-00805f9b34fb"));
static const QString serviceNom(QStringLiteral("AREA-Afficheur"));

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
    QString recupererNomTableArbitre(QBluetoothSocket* socket) const;
    int     recupererNumeroTableArbitre(QBluetoothSocket* socket) const;

  public slots:
    void gererClient();
    void deconnecterSocket();
    void lireSocket();
    void changerEtatSocket(QBluetoothSocket::SocketState etat);
    void renvoyerErreurSocket(QBluetoothSocket::SocketError erreur);
    void renvoyerErreurDevice(QBluetoothLocalDevice::Error erreur);

  signals:
    void clientConnecte(QString nom, QString adresse);
    void clientDeconnecte(QString nomModule);
    void nouvelleTrameRencontre(QString    nomModule,
                                QByteArray NomClubA,
                                QByteArray NomClubW,
                                QByteArray NomJoueurA,
                                QByteArray PrenomJoueurA,
                                QByteArray NomJoueurB,
                                QByteArray PrenomJoueurB,
                                QByteArray NomJoueurC,
                                QByteArray PrenomJoueurC,
                                QByteArray NomJoueurD,
                                QByteArray PrenomJoueurD,
                                QByteArray NomJoueurW,
                                QByteArray PrenomJoueurW,
                                QByteArray NomJoueurX,
                                QByteArray PrenomJoueurX,
                                QByteArray NomJoueurY,
                                QByteArray PrenomJoueurY,
                                QByteArray NomJoueurZ,
                                QByteArray PrenomJoueurZ);

    void nouvelleTrameSimple(QString nomModule,
                             QByteArray idPartie,
                             QByteArray JoueurA,
                             QByteArray ClassementJoueurA,
                             QByteArray JoueurB,
                             QByteArray ClassementJoueurW);
};

#endif // RECEPTIONTRAME_H
