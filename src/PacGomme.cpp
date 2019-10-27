//
//  PacGomme.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 05/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "PacGomme.h"

PacGomme::PacGomme():
_posX(0),
_posY(0),
_pointRapporte(10)
{
    
}
PacGomme::PacGomme(int posX, int posY):
_pointRapporte(10),
_posX(posX),
_posY(posY)
{
    
}

PacGomme::~PacGomme()
{
    
}

void PacGomme::setPosX(int x)
{
    _posX = x;
}

void PacGomme::setPosY(int y)
{
    _posY = y;
}


int PacGomme::getPointRapporte()const
{
    return _pointRapporte;
}

sf::Vector2f PacGomme::getPosition()const
{
    return sf::Vector2f(_posX, _posY);
}