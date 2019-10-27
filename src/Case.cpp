//
//  Case.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 05/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Case.h"
#include <iostream>

Case::Case(int identifiant, sf::Vector2f size, sf::Vector2f position, bool contientPacGomme):
_contientPacGomme(contientPacGomme),
_identifiant(identifiant),
_pacGomme()
{
    _shape.setSize(size);
    _shape.setPosition(position);
    _pacGomme.setPosX(_shape.getPosition().x + 16);
    _pacGomme.setPosY(_shape.getPosition().y + 16);
}

Case::~Case()
{
    
}

bool Case::pacGommePresente()const
{
    return _contientPacGomme;
}

void Case::desactiverPacGomme()
{
    _contientPacGomme = false;
}

sf::Vector2f Case::getPosition()const
{
    return _shape.getPosition();
}

void Case::setType(int identifiant)
{
    _identifiant = identifiant;
}

int Case::getType()const
{
    return _identifiant;
}

sf::RectangleShape Case::getRectangle()const
{
    return _shape;
}

int Case::getPointPacGomme()const
{
    return _pacGomme.getPointRapporte();
}

sf::Vector2f Case::getPositionPacGomme()const
{
    return _pacGomme.getPosition();
}

void Case::processEvent()
{

}