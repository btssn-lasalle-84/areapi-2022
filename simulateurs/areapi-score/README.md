# Simulateur de SCORE pour AREAPI 2022

## Présentation du protocole implanté dans le simulateur ESP32

Ce document présente rapidement le fonctionnement du simulateur ainsi que le protocole implémenté. Le protocole complet est disponible dans Google Drive. Actuellement, la version du protocole est la **2.0** (08 mai 2022).

Trame reçue :

`$AREA;SCORE;idPartie;scoreJG;scoreJD;etatPartie;tempsMort;nbSetJG;nbSetJD;tourService;net;\r\n`

Champs :

- `idPartie` : int (identifiant de la partie)
- `scoreJG` : int (joueur à gauche de l’arbitre)
- `scoreJD` : int (joueur à droite de l’arbitre)
- `etatPartie` : bool (1 si la partie est en cours sinon 0)
- `tempsMort` : bool (1 si le temps mort est en cours sinon 0)
- `nbSetJ1` : int (max 5)
- `nbSetJ2` : int (max 5)
- `tourService` : int (G ou D)
- `net` : int (nombre de nets)

Exemple : `$AREA;SCORE;1;2;5;1;0;1;2;G;5;\r\n`

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
