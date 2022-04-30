/**
*
* @file src/main.cpp
*
* @brief Programme principal : Simulateur AREAPI 2022
*
* @author Thierry Vaira
*
* @version 0.2
*
*/
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <afficheur.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"

#define DEBUG

// Brochages
#define GPIO_LED_ROUGE      5       //!< Mise sous tension
#define GPIO_LED_ORANGE     17      //!< Un service
#define GPIO_LED_VERTE      16      //!< Un net
#define GPIO_SW1            12      //!< Pour simuler un service
#define GPIO_SW2            14      //!< Pour simuler un net
#define ADRESSE_I2C_OLED    0x3c    //!< Adresse I2C de l'OLED
#define BROCHE_I2C_SDA      21      //!< Broche SDA
#define BROCHE_I2C_SCL      22      //!< Broche SCL

// Protocole (cf. Google Drive)
#define EN_TETE_TRAME_RECEPTION "$AREA"
#define EN_TETE_TRAME_EMISSION  "$AREA"
#define TRAME_SERVICE           "SERVICE"
#define TRAME_NET               "NET"
#define TRAME_RAZ_COMPTEUR_NET  "RAZ_COMPTEUR_NET"
#define DELIMITEUR_CHAMP        ";"
#define DELIMITEURS_FIN         "\r\n"
#define DELIMITEUR_DATAS        ';'
#define DELIMITEUR_FIN          '\n'

// Variables
BluetoothSerial ESPBluetooth;
int nbNets = 1;             //!< Compteur de nets par partie
bool service = false;       //!< true si un service est en cours
bool refresh = false;       //!< true pour demander un refraichissement de l'écran OLED
bool refreshNet = false;    //!< pour la détction d'un net
Afficheur afficheur(ADRESSE_I2C_OLED, BROCHE_I2C_SDA, BROCHE_I2C_SCL); //!< afficheur OLED SSD1306

/**
 * @brief Envoie une trame via le Bluetooth
 *
 * @fn envoyerTrameNet()
 */
void envoyerTrameNet(int nbNets)
{
  char trameEnvoi[64];

  //Format : $AREA;NET;1\r\n
  sprintf((char *)trameEnvoi, "$AREA;NET;%d\r\n", nbNets);
  ESPBluetooth.write((uint8_t*)trameEnvoi, strlen((char *)trameEnvoi));
  #ifdef DEBUG
  String trame = String(trameEnvoi);
  trame.remove(trame.indexOf("\r"), 2);
  Serial.print("--> ");
  Serial.println(trame);
  #endif
}

/**
 * @brief Déclenchée par interruption sur le bouton SW1
 *
 * @fn simulerService()
 */
void IRAM_ATTR simulerService()
{
  service = true;
  //nbNets = 1;

  char strMessageDisplay[24];
  sprintf(strMessageDisplay, "Service");
  afficheur.setMessageLigne(Afficheur::Ligne1, String(strMessageDisplay));
  afficheur.setMessageLigne(Afficheur::Ligne2, ""); // Reset ligne NET
  refresh = true;
  #ifdef DEBUG
  Serial.println("Simulation service !");
  #endif
}

/**
 * @brief Déclenchée par interruption sur le bouton SW2
 *
 * @fn simulerNet()
 */
void IRAM_ATTR simulerNet()
{
  if(refreshNet || !service)
    return;

  //int hasard = random(10);

  //if(hasard < 6)
  {
    envoyerTrameNet(nbNets);
    refreshNet = true;
    service = false;

    char strMessageDisplay[24];
    sprintf(strMessageDisplay, "NET %d", nbNets);
    afficheur.setMessageLigne(Afficheur::Ligne2, String(strMessageDisplay));
    refresh = true;

    #ifdef DEBUG
    Serial.print("NET ");
    Serial.println(nbNets);
    #endif

    nbNets++;
  }
}

/**
 * @brief Lit une trame via le Bluetooth
 *
 * @fn lireTrame(String &trame)
 * @param trame la trame reçue
 * @return bool true si une trame a été lue, sinon false
 */
bool lireTrame(String &trame)
{
  if (ESPBluetooth.available())
  {
    trame.clear();
    trame = ESPBluetooth.readStringUntil(DELIMITEUR_FIN);
    #ifdef DEBUG
    Serial.print("<-- ");
    Serial.println(trame);
    #endif
    trame.concat(DELIMITEUR_FIN); // remet le DELIMITEUR_FIN
    return true;
  }

  return false;
}

/**
 * @brief Vérifie si la trame reçue est une trame de SERVICE valide ou RAZ
 *
 * @fn verifierTrameMobile(String &trame)
 * @param trame
 * @return bool true si une trame de SERVICE ou RAZ a été reçue, sinon false
 */
bool verifierTrameMobile(String &trame)
{
  String trameService;
  //trame.toUpperCase();
  // MOBILE_AREA;SERVICE\r\n
  trameService = String(EN_TETE_TRAME_RECEPTION) + String(DELIMITEUR_CHAMP) + String(TRAME_SERVICE) + String(DELIMITEURS_FIN);
  //trameService.toUpperCase();
  if(trame.equals(trameService))
  //if(trame.startsWith(trameService))
  {
    service = true;

    char strMessageDisplay[24];
    sprintf(strMessageDisplay, "SERVICE");
    afficheur.setMessageLigne(Afficheur::Ligne1, String(strMessageDisplay));
    afficheur.setMessageLigne(Afficheur::Ligne2, ""); // Reset ligne NET
    refresh = true;
    #ifdef DEBUG
    Serial.println("Service !");
    #endif
    return true;
  }

  String trameRaz;
  //trame.toUpperCase();
  // MOBILE_AREA;SERVICE\r\n
  trameRaz = String(EN_TETE_TRAME_RECEPTION) + String(DELIMITEUR_CHAMP) + String(TRAME_RAZ_COMPTEUR_NET) + String(DELIMITEURS_FIN);
  //trameRaz.toUpperCase();
  if(trame.equals(trameRaz))
  //if(trame.startsWith(trameRaz))
  {
    // remettre le compteur de nets à 1 ???
    nbNets = 1;

    char strMessageDisplay[24];
    sprintf(strMessageDisplay, "RAZ");
    afficheur.setMessageLigne(Afficheur::Ligne1, String(strMessageDisplay));
    afficheur.setMessageLigne(Afficheur::Ligne2, ""); // Reset ligne NET
    refresh = true;
    #ifdef DEBUG
    Serial.println("Raz !");
    #endif
    return true;
  }

  return false;
}

void reinitialiserAffichage()
{
  afficheur.setMessageLigne(Afficheur::Ligne1, "");
  afficheur.setMessageLigne(Afficheur::Ligne2, "");
  afficheur.setMessageLigne(Afficheur::Ligne3, "");
  refresh = true;
}

/**
* @brief Initialise les ressources du programme
*
* @fn setup
*
*/
void setup()
{
  Serial.begin(115200);
  while (!Serial);

  // Configuration des E/S
  pinMode(GPIO_LED_ROUGE, OUTPUT);
  pinMode(GPIO_LED_ORANGE, OUTPUT);
  pinMode(GPIO_LED_VERTE, OUTPUT);
  pinMode(GPIO_SW1, INPUT_PULLUP);
  pinMode(GPIO_SW2, INPUT_PULLUP);

  // Installe le gestionnaire d'interruption pour SW1 -> Simule un service
  attachInterrupt(digitalPinToInterrupt(GPIO_SW1), simulerService, FALLING);
  // Installe le gestionnaire d'interruption pour SW2 -> Simule un NET
  attachInterrupt(digitalPinToInterrupt(GPIO_SW2), simulerNet, FALLING);

  // Initialisation des états des leds
  digitalWrite(GPIO_LED_ROUGE, LOW);
  digitalWrite(GPIO_LED_ORANGE, LOW);
  digitalWrite(GPIO_LED_VERTE, LOW);

  // Initialisation de l'affichage OLED
  afficheur.initialiser();

  String titre = "";
  String stitre = "=====================";
  String nomBluetooth = "areapi-net-1";
  ESPBluetooth.begin(nomBluetooth);
  const uint8_t* adresseESP32 = esp_bt_dev_get_address();
  char str[18];
  sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x", adresseESP32[0], adresseESP32[1], adresseESP32[2], adresseESP32[3], adresseESP32[4], adresseESP32[5]);
  stitre = String("== ") + String(str) + String(" ==");
  titre = String("AREAPI : NET");
  digitalWrite(GPIO_LED_ROUGE, HIGH);

  #ifdef DEBUG
  Serial.println(titre);
  Serial.println(stitre);
  #endif

  afficheur.setTitre(titre);
  afficheur.setSTitre(stitre);
  afficheur.afficher();
}

/**
* @brief Boucle infinie d'exécution du programme
*
* @fn loop
*
*/
void loop()
{
  String trame;

  // Rafraîchir l'affichage de l'écran OLED
  if(refresh)
  {
    afficheur.afficher();
    refresh = false;
  }

  // Gérer l'anti-rebond et la durée d'affichage d'un net
  if(refreshNet)
  {
    digitalWrite(GPIO_LED_VERTE, HIGH);
    afficheur.afficher();
    delay(300);
    refreshNet = false;
    digitalWrite(GPIO_LED_VERTE, LOW);
    reinitialiserAffichage();
  }

  // Recevoir une trame du terminal Mobile ?
  if(lireTrame(trame))
  {
    if(verifierTrameMobile(trame))
    {
      #ifdef DEBUG
      Serial.println("Trame valide !");
      #endif
    }
  }

  // Afficher la led si un service est encours ?
  if(service)
  {
    digitalWrite(GPIO_LED_ORANGE, HIGH);
  }
  else
  {
    digitalWrite(GPIO_LED_ORANGE, LOW);
  }
}
