# Simulateur de NET pour AREAPI 2022

## Présentation du protocole implanté dans le simulateur ESP32

Ce document présente rapidement le fonctionnement du simulateur ainsi que le protocole implémenté. Le protocole complet est disponible dans Google Drive. Actuellement, la version du protocole est la **2.0** (08 mai 2022).

## Configuration du simulateur

Ce programme est destiné à une carte ESP'ACE (ESP32), équipée d'un écran OLED, dont le brochage est le suivant :

```cpp
#define GPIO_LED_ROUGE      5       //!< Mise sous tension
#define GPIO_LED_ORANGE     17      //!< Un service
#define GPIO_LED_VERTE      16      //!< Un net
#define GPIO_SW1            12      //!< Pour simuler un service
#define GPIO_SW2            14      //!< Pour simuler un net
```

Par défaut, la configuration de l'écran OLED est la suivante :

```cpp
#define ADRESSE_I2C_OLED    0x3c    //!< Adresse I2C de l'OLED
#define BROCHE_I2C_SDA      21      //!< Broche SDA
#define BROCHE_I2C_SCL      22      //!< Broche SCL
```

## platform.ini

```ini
[env:lolin32]
platform = espressif32
board = lolin32
framework = arduino
lib_deps =
  thingpulse/ESP8266 and ESP32 OLED driver for SSD1306 displays @ ^4.2.0
upload_port = /dev/ttyUSB0
upload_speed = 115200
monitor_port = /dev/ttyUSB0
monitor_speed = 115200
```

## Auteur

- Thierry Vaira <<tvaira@free.fr>>
