/**
 * @file afficheurLed.h
 * @author your name (you@domain.com)
 * @brief ...
 * @version 0.1
 * @date 2021-06-03
 */
/*
 * Règle : l'utilisation des doubles uderscores est réservée aux DEFINE du système
 */
#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include <Arduino.h> /* se justifie seulement pour uint8_t ? */

//#define DEBUG_AFFICHEUR

#define VITESSE_SERIE   9600

// Liaison I2C et afficheur
#define SDA_PIN                   21
#define SCL_PIN                   22
#define ADRESSE_AFFICHEUR_GAUCHE  0x24 // 36
#define ADRESSE_AFFICHEUR_DROIT   0x20 // 32
#define ADRESSE_SET_GAUCHE        0x22
#define ADRESSE_SET_DROIT         0x23
#define ADRESSE_UNITE             0x00
#define ADRESSE_DIZAINE           0x01
#define DIZAINE                   0x13
#define UNITE                     0x12
#define SORTIE                    0x00
#define BLANC                     0x10
#define BASE                      0x30
#define TEST_LED                  0x00

#define NEUF                      9
#define DIX                       10
#define DELAI_INTER_TRAME         400          // temps en deux trames I2C concécutives

/*
 * Remarque : le C++ n'oblige pas à déclarer les classes dans des fichiers séparés
 * Ici, la classe DigitLed n'a pas d'usage en dehors de la classe AfficheurLed. Elle peut donc se déclarer ici.
 */

/**
 * @brief ...
 */
class DigitLed
{
    private:
        uint8_t adresse;
        uint8_t adresseRang;
        uint8_t rang;
        uint8_t valeur;
        bool initialise;

    public:
        DigitLed();
        ~DigitLed();

        void initialiserDigit(uint8_t adresse, uint8_t adresseRang, uint8_t rang);
        void effacerDigit();
        uint8_t getValeur() const;
        void setValeur(uint8_t valeur);
};

/**
 * @brief ...
 */
/*
 * Règle : CamelCase pour les noms des classes
 */
class AfficheurLed
{
    private:
        uint8_t sda_pin;
        uint8_t scl_pin;
        uint8_t adresse;
        uint8_t score;
        /*
         * Remarque : AfficheurLed est composé de deux DigitLed. En UML, c'est une composition si :
         *  - l'objet composant n'est pas partagé (il n'est pas membre d'un autre objet composite)
         *  - l'objet composant sera détruit lorsque son composite sera détruit
         * Ici, on a donc bien une composition. Sinon, ce serait une agrégation UML.
         */
        DigitLed digitLedUnite;
        DigitLed digitLedDizaine;
        bool remplissage; // remplir à gauche avec des zéros
        bool initialise;

        void initialiserI2C();

    public:
        AfficheurLed(uint8_t sda_pin = SDA_PIN,uint8_t scl_pin = SCL_PIN);
        ~AfficheurLed();

        void initialiserAfficheur(uint8_t adresse);
        void effacerAfficheur();
        void afficherScore(uint8_t score);
        void setRemplissage(bool remplissage);

        /*
         * Bonne pratique : une méthode const est une méthode qui ne modifie aucun attribut de la classe
         * Le compilateur fera systématiquement les vérifications et te protégera de tes probables futures erreurs
         * Ceci permettra l'application de l'adage "Le compilateur est ton meilleur ami !"
         *
         */
        uint8_t getAdresse() const;
        uint8_t getScore() const;
};

/*
 * Règle : on prend l'habitude de marquer en commentaire la fin d'un ifdef
 */
#endif /* AFFICHEUR_H */