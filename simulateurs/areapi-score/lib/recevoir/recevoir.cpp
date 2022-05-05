/*

*/

#include "recevoir.h"
#include <Arduino.h>
#include <BluetoothSerial.h>
#include "afficheurLed.h"
#include <Ticker.h>

///////////////////////////////////////////////////////////////////////////////

BluetoothSerial liaisonBluetooth;
AfficheurLed  scoreGauche;
AfficheurLed  scoreDroit;
Ticker timerHeartBeat;

String entete = "$";          // entête de la trame
String separateur = ";";      // caractère séparateur
String delimiteurFin = "\r\n";          // fin de trame
String trame = "";
String typeDeTrame = "";
String positionJoueurA = "";

int idPartie = -1;
String etatPartie;
int nbSets = 0;
PositionJoueur placeJoueurA = PositionJoueur::GAUCHE;

///////////////////////////////////////////////////////////////////////////////

void initBluetooth(String nomIot)
{
  liaisonBluetooth.end();
  bool retour = liaisonBluetooth.begin(nomIot);            // initialisation de du module BT
  #ifdef DEBUG_RECEVOIR
  Serial.print("liaisonBluetooth = ");
  Serial.println(retour);
  #endif
  if(retour)
    timerHeartBeat.attach(30, envoyerTrameHeartBeat);
}

void initAfficheurs()
{
  scoreGauche.initialiserAfficheur(ADRESSE_AFFICHEUR_GAUCHE);
  scoreGauche.effacerAfficheur();
  scoreDroit.initialiserAfficheur(ADRESSE_AFFICHEUR_DROIT);
  scoreDroit.effacerAfficheur();
}

bool lireTrame()
{
  if (liaisonBluetooth.available())
  {
    trame.clear();
    trame = liaisonBluetooth.readStringUntil(delimiteurFin[1]);
    trame.concat(delimiteurFin[1]);
    #ifdef DEBUG_RECEVOIR
    Serial.println(trame);
    #endif
    return true;
  }

  return false;
}

bool decoderTrame()
{
  if(trame.startsWith(ENTETE_TRAME))
  {
    String typeTrame = extraireChamp(CHAMP_TYPE_TRAME);

    if(typeTrame == "SCORE")
    {
          //$AREA;SCORE;idPartie;scoreJG;scoreJD;etatPartie;tempsMort;nbSetJG;nbSetJD;tourService;net\r\n
          #ifdef DEBUG_RECEVOIR
          Serial.print("ID PARTIE = ");
          Serial.println(extraireChamp(ID_PARTIE));
          #endif
          if(idPartie == extraireChamp(ID_PARTIE).toInt())
          {
            gererScore(extraireChamp(ID_PARTIE).toInt(), extraireChamp(POINTS_JOUEUR_A).toInt(), extraireChamp(POINTS_JOUEUR_B).toInt(), extraireChamp(MANCHES_JOUEUR_A).toInt(), extraireChamp(MANCHES_JOUEUR_B).toInt());
          }
          #ifdef DEBUG_RECEVOIR
          else
          {
            Serial.print("idPartie = ");
            Serial.println(idPartie);
          }
          #endif
          // Le champ ETAT peut prendre deux valeurs : DEMARREE ou TERMINEE
          etatPartie = extraireChamp(ETAT_PARTIE);
          #ifdef DEBUG_RECEVOIR
          Serial.print("ID PARTIE = ");
          Serial.print(extraireChamp(ID_PARTIE).toInt());
          Serial.print(" -> ETAT PARTIE = ");
          Serial.println(etatPartie);
          #endif

          if(etatPartie == "1") // DEMARREE
          {
            idPartie = extraireChamp(ID_PARTIE).toInt();            
          }
          else if(etatPartie == "0") // TERMINEE
          {
            idPartie = -1;
            effacerScore();
            nbSets = 0;
          }
          else if(etatPartie == "ANNULEE")
          {
            idPartie = -1;
            effacerScore();
          }
          #ifdef DEBUG_RECEVOIR
          else
            Serial.println("ETAT inconnu !");
          #endif
    }
    else
    {
      #ifdef DEBUG_RECEVOIR
      Serial.println("Type de trame inconnu !");
      #endif
      return false;
    }
  }

  return true;
}

void gererScore(int idPartie, int pointJoueurA, int pointJoueurB, int mancheJoueurA, int mancheJoueurB)
{
  #ifdef DEBUG_RECEVOIR
  Serial.print("SCORE : ");
  Serial.print(pointJoueurA);
  Serial.print(" vs ");
  Serial.println(pointJoueurB);
  Serial.print("SET   : ");
  Serial.print(mancheJoueurA);
  Serial.print(" vs ");
  Serial.println(mancheJoueurB);
  #endif
  nbSets = mancheJoueurA + mancheJoueurB;
  /*if((nbSets % 2) == 0)
  {
  }
  else
  {
  }*/
  if(placeJoueurA == PositionJoueur::GAUCHE)
  {
    scoreGauche.afficherScore(pointJoueurA);
    scoreDroit.afficherScore(pointJoueurB);
  }
  else if(placeJoueurA == PositionJoueur::DROITE)
  {
    scoreDroit.afficherScore(pointJoueurA);
    scoreGauche.afficherScore(pointJoueurB);
  }
  /**
   * @todo Gérer l'affichage des sets ?
   *
   */
}

void effacerScore()
{
  Serial.println("SCORE : CLEAR");
  scoreGauche.effacerAfficheur();
  scoreDroit.effacerAfficheur();
}

String extraireChamp(unsigned int numeroChamp)
{
  String champ;
  int compteurCaractere = 0;
  int compteurDelimiteur = 0;
  char fin = '\n';

  if(delimiteurFin.length() > 0)
    fin = delimiteurFin[0];

  for(int i = 0; i < trame.length(); i++)
  {
    if(trame[i] == separateur[0] || trame[i] == fin)
    {
      compteurDelimiteur++;
    }
    else if(compteurDelimiteur == numeroChamp)
    {
        champ += trame[i];
        compteurCaractere++;
    }
  }

  return champ;
}

int compterParametres()
{
  int n = 0;
  for(int i=0;i< trame.length();i++)
  {
    if(trame[i] == separateur[0])
      ++n;
  }
  return n;
}

/**
 * @brief Envoie une trame "battemment de coeur" !
 *
 * @fn envoyerTrameHeartBeat()
 */
void envoyerTrameHeartBeat()
{
  char trameEnvoi[64];

  sprintf((char *)trameEnvoi, "SCORE_AREA;HEARTBEAT\r\n");
  liaisonBluetooth.write((uint8_t*)trameEnvoi, strlen((char *)trameEnvoi));
  #ifdef DEBUG_RECEVOIR
  String trame = String(trameEnvoi);
  trame.remove(trame.indexOf("\r"), 2);
  Serial.print("--> ");
  Serial.println(trame);
  #endif
}

void testerAfficheurs()
{
    Serial.print("  Test comptage ...");
    for(uint points = 0; points<=31 ; points++)
    {
        scoreGauche.afficherScore(points);
        delay(200);
        scoreDroit.afficherScore(points);
        delay(200);
    }
    scoreGauche.effacerAfficheur();
    scoreDroit.effacerAfficheur();
    Serial.print(" Fin ");
}
