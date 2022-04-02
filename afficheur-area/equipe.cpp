#include "equipe.h"

/**
 * @file equipe.cpp
 *
 * @brief Définition de la classe Equipe
 * @author
 * @version 1.0
 *
 */

Equipe::Equipe() : nom("")
{
}

Equipe::Equipe(const Equipe& equipe) : nom(equipe.nom)
{
}

Equipe::~Equipe()
{
}

Equipe& Equipe::operator=(const Equipe& equipe)
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

void Equipe::setNom(const QString& nom)
{
    this->nom = nom;
}
