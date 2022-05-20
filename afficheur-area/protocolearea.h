#ifndef PROTOCOLEAREA_H
#define PROTOCOLEAREA_H

#include <QString>
#include <QByteArray>

/*
    Exemple : $AREA;RENCONTRE;PPC Avignon;PPC
   Sorguais;BOUDRIMIL;Kamal;REDOR;Simon;KRIER;Eric;RUIZ;Jean-michel;BEAUMONT;Jérôme;SAULNIER;Christian;COMTE;Emmanuel;LEVRARD;Mickael;\r\n

    $AREA;DOUBLE;idPartie;JoueurA1;JoueurA2;JoueurW1;JoueurW2;EquipeAG;\r\n
    $AREA;SIMPLE;idPartie;JoueurA;JoueurW;EquipeAG;\r\n
    EquipeAG : bool (1 si l’équipe A est à gauche, 0 si elle est à droite)

    $AREA;SCORE;idPartie;scoreJG;scoreJD;etatPartie;tempsMort;nbSetJG;nbSetJD;tourService;net;\r\n
    Exemple : $AREA;SCORE;1;2;5;1;0;1;2;G;5;\r\n
 */

class ProtocoleArea
{
  public:
    static QByteArray DEBUT_TRAME;
    static QByteArray FIN_TRAME;
    static char       DELIMITEUR_TRAME;
    /**
     * @enum ChampsTrame
     * @brief Définit les différents champs d'une trame
     */
    enum ChampsTrame
    {
        ENTETE = 0,
        TYPE
    };
    static QByteArray RENCONTRE;
    static QByteArray SIMPLE;
    static QByteArray DOUBLE;
    static QByteArray SCORE;
    /**
     * @enum ChampsRencontre
     * @brief Définit les différents champs d'une trame RENCONTRE
     */
    enum ChampsRencontre
    {
        NomClubA = 2,
        NomClubW,
        NomJoueurA,
        PrenomJoueurA,
        NomJoueurB,
        PrenomJoueurB,
        NomJoueurC,
        PrenomJoueurC,
        NomJoueurD,
        PrenomJoueurD,
        NomJoueurW,
        PrenomJoueurW,
        NomJoueurX,
        PrenomJoueurX,
        NomJoueurY,
        PrenomJoueurY,
        NomJoueurZ,
        PrenomJoueurZ,
        NbChampsRencontre
    };
    /**
     * @enum ChampsPartieSimple
     * @brief Définit les différents champs d'une trame SIMPLE
     */
    enum ChampsPartieSimple
    {
        idPartie = 2,
        JoueurA,
        ClassementJoueurA,
        JoueurW,
        ClassementJoueurW,
        NbChampsPartieSimple
    };

    /**
     * @enum ChampsPartieDouble
     * @brief Définit les différents champs d'une trame DOUBLE
     */
    enum ChampsPartieDouble
    {
        idPartieDouble = 2,
        JoueurA1,
        ClassementA1,
        JoueurA2,
        ClassementA2,
        JoueurW1,
        ClassementW1,
        JoueurW2,
        ClassementW2,
        NbChampsPartieDouble
    };

    /**
     * @enum ChampsPartieDouble
     * @brief Définit les différents champs d'une trame SCORE
     */
    enum ChampsPartieScore
    {
        idPartieScore = 2,
        scoreJG,
        scoreJD,
        etatPartie,
        tempsMort,
        nbSetJG,
        nbSetJD,
        tourService,
        net,
        NbChampsScore
    };
};

#endif // PROTOCOLEAREA_H
