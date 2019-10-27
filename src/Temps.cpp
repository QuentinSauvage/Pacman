//
//  Temps.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 19/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Temps.h"
#include <iostream>

Temps::Temps():
_horloge(),
_sauvegardeTemps(),
_tempsEfficiant(),
_pause(false)
{
    _sauvegardeTemps = sf::seconds(0.f);
}

Temps::~Temps()
{
    
}

bool Temps::enPause()const
{
    return _pause;
}

void Temps::update()
{
    if(!_pause)
        _tempsEfficiant = _horloge.getElapsedTime() +  _sauvegardeTemps;
}

void Temps::pause()
{
    _sauvegardeTemps = _tempsEfficiant;
    _pause = true;
}

void Temps::reprendre()
{
    _horloge.restart();
    _pause = false;
}

void Temps::redemarrer()
{
    _horloge.restart();
}

int Temps::getTempsSecondes()const
{
    return static_cast<int>(_tempsEfficiant.asSeconds());
}

sf::Time& Temps::getTempsReel()
{
    return _tempsEfficiant;
}