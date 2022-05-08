/**
 * @file afficheurLed.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-06-03
 */
/*
 * Règles :
 * - toujours inclure en premier son fichier de déclaration
 * - inutile d'inclure des fichiers déjà inclus dans son fichier de délaration
 * - inclure seulement les fichiers dont CE code source a besoin (Adage : "Ne s'occuper que de soi !"
 * - l'ordre peut être important
 */
#include "afficheurLed.h"
#include <Wire.h>

DigitLed::DigitLed() : adresse(0), valeur(0), initialise(false)
{
}

DigitLed::~DigitLed()
{
}

void DigitLed::initialiserDigit(uint8_t adresse, uint8_t adresseRang, uint8_t rang)
{
  this->adresse = adresse;
  this->adresseRang = adresseRang;
  this->rang = rang;
  while(Wire.busy());
  Wire.beginTransmission(adresse);
  Wire.write(adresseRang); // accès au registre de configuration des GPIOs
  Wire.write(SORTIE);
  Wire.endTransmission();
  this->valeur = 0;
  this->initialise = true;
}

void DigitLed::effacerDigit()
{
  if(this->initialise)
  {
    Wire.beginTransmission(adresse);
    Wire.write(rang);
    Wire.write(BLANC);
    Wire.endTransmission();
    this->valeur = 0;
  }
}

uint8_t DigitLed::getValeur() const
{
  return this->valeur;
}

void DigitLed::setValeur(uint8_t valeur)
{
  if(!this->initialise)
    return;

  if(valeur >= 0 && valeur <= 9)
  {
    Wire.beginTransmission(adresse);
    Wire.write(rang);
    Wire.write((BASE + valeur));
    Wire.endTransmission();
    this->valeur = valeur;
  }
}

/*
 * Règle : utilier systématiquement la liste d'initialisation (et obligatoirement dans l'ordre de déclaration des attributs)
 */
AfficheurLed::AfficheurLed(uint8_t sda_pin /* = SDA_PIN*/, uint8_t scl_pin /* = SCL_PIN*/) : sda_pin(sda_pin), scl_pin(scl_pin), adresse(0), score(0), remplissage(false), initialise(false)
{
  initialiserI2C();
}

AfficheurLed::~AfficheurLed()
{
}

/*
 * Règle : on pratique le remaniement de code par extraction de méthodes
 */
void AfficheurLed::initialiserI2C()
{
  Wire.begin(sda_pin, scl_pin);
  pinMode(sda_pin, OUTPUT);
  pinMode(scl_pin, OUTPUT);
}

void AfficheurLed::initialiserAfficheur(uint8_t adresse)
{
  #ifdef DEBUG_AFFICHEUR
  Serial.print("ADRESSE : ");
  Serial.println(adresse);
  #endif
  this->adresse = adresse;
  while(Wire.busy());
  digitLedUnite.initialiserDigit(adresse, ADRESSE_UNITE, UNITE);
  digitLedDizaine.initialiserDigit(adresse, ADRESSE_DIZAINE, DIZAINE);
  this->score = 0;
  this->initialise = true;
}

void AfficheurLed::effacerAfficheur()
{
  if(this->initialise)
  {
    digitLedUnite.effacerDigit();
    digitLedDizaine.effacerDigit();
    this->score = 0;
  }
}

void AfficheurLed::afficherScore(uint8_t score)
{
  if(!this->initialise)
    return;

  this->score = score;
  uint8_t unite = score;
  uint8_t dizaine = 0;
  #ifdef DEBUG_AFFICHEUR
  Serial.print("ADRESSE : ");
  Serial.println(adresse);
  Serial.print("SCORE : ");
  Serial.println(score);
  #endif
  /**
   * @warning Et les valeurs supérieures à 99 ?
   *
   */
  if(score >= DIX)
  {
    unite = score % DIX;
    dizaine = (score - unite ) / DIX;
    digitLedDizaine.setValeur(dizaine);
  }
  else
  {
    if(remplissage)
    {
      digitLedDizaine.setValeur(0);
    }
    else
    {
      digitLedDizaine.effacerDigit();
    }
  }
  digitLedUnite.setValeur(unite);
}

uint8_t AfficheurLed::getAdresse() const
{
  return this->adresse;
}

uint8_t AfficheurLed::getScore() const
{
  return this->score;
}

void AfficheurLed::setRemplissage(bool remplissage)
{
  this->remplissage = remplissage;
}
