/*  Programme Gestion de score

     - initialiser la liaison série
     - configurer les mcp23017 (port A et Ben sorties)
     - commander les 4511 (xx11 iiii)
     - instancier les objets points Joueurs
     - instancier les objets sets Joueurs

    Date : 23/11/20
    Rev.: 1.0
    Auteur: J.BEAUMONT
*/

#include <Arduino.h>
#include "recevoir.h"

//#define TEST_AFFICHEURS

//////////////////////////////////////////////////////////////////////////////////////////

String nomMarqueur = "areapi-score-1";

//////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    Serial.println("starting config SCORE_AREA ***");
    initBluetooth(nomMarqueur);
    initAfficheurs();
    Serial.println("ending config SCORE_AREA ***");

    #ifdef TEST_AFFICHEURS
    testerAfficheurs();
    #endif
}

//////////////////////////////////////////////////////////////////////////////////////////

void loop()
{
  if(lireTrame())
  {
    decoderTrame();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
