#include "equipe.h"

Equipe::Equipe() : nom("")
{

}

Equipe::~Equipe()
{
}

Equipe::Equipe(const Equipe &equipe)
{
    *this = equipe;
}

Equipe & Equipe::operator=(const Equipe & equipe)
{
    if(this != &equipe)
    {
        this->nom = equipe.nom;
    }

    return *this;
}

QString Equipe::getNom() const
{
    return this->nom;
}

void Equipe::setNom(const QString &nom)
{
    this->nom = nom;
}
