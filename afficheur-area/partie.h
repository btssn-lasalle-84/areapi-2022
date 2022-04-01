#ifndef PARTIE_H
#define PARTIE_H

#include <QString>

class Partie
{
    private:
        int nombreSet;
        unsigned int scoreJoueurG;
        unsigned int scoreJoueurD;
        unsigned int setJoueurG;
        unsigned int setJoueurD;
        unsigned int nombreNET;
        unsigned int pointConsecutif;
        QString joueurPointConsecutif;


    public:
        Partie();
        ~Partie();
        Partie(const Partie &partie);

        Partie & operator=(const Partie & partie);

        bool aGagne() const;
        bool estPointConsecutif() const;
        void ajouterPointJoueurG();
        void ajouterPointJoueurD();
        void gagneSetJoueurG();
        void gagneSetJoueurD();
        void ajouterNET();
        void rajouterPointConsecutif();

        unsigned int getScoreJoueurG() const;
        unsigned int getScoreJoueurD() const;
        unsigned int getSetJoueurG() const;
        unsigned int getSetJoueurD() const;
        unsigned int getNombreNET() const;
        unsigned int getPointConsecutif() const;
        QString getJoueurPointConsecutif() const;

        void setScoreJoueurG(unsigned int &scoreJoueurG);
        void setScoreJoueurD(unsigned int &scoreJoueurD);
        void setSetJoueurG(unsigned int &setJoueurG);
        void setSetJoueurD(unsigned int &setJoueurD);
        void setNombreNET(unsigned int &nombreNET);
        void setPointConsecutif(unsigned int &pointConsecutif);
        void setJoueurPointConsecutif(QString &joueurPointConsecutif);


};

#endif // PARTIE_H
