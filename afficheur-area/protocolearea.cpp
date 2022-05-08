#include "protocolearea.h"

QByteArray ProtocoleArea::DEBUT_TRAME      = "$AREA";
QByteArray ProtocoleArea::FIN_TRAME        = "\r\n";
char       ProtocoleArea::DELIMITEUR_TRAME = ';';

QByteArray ProtocoleArea::RENCONTRE = "RENCONTRE";
QByteArray ProtocoleArea::SIMPLE    = "SIMPLE";
QByteArray ProtocoleArea::DOUBLE    = "DOUBLE";
QByteArray ProtocoleArea::SCORE     = "SCORE";
