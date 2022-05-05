# Simulateur de SCORE pour AREAPI 2022

## Présentation du protocole implanté dans le simulateur ESP32

Ce document présente rapidement le fonctionnement du simulateur ainsi que le protocole implémenté. Le protocole complet est disponible dans Google Drive. Actuellement, la version du protocole est la **0.1** (04 avril 2022).

## platform.ini

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
upload_port = /dev/ttyUSB0
upload_speed = 115200
monitor_port = /dev/ttyUSB0
monitor_speed = 115200
```

## Auteur

- Thierry Vaira <<tvaira@free.fr>>
