//
//  MenuEntrePlateau.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 23/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "MenuEntrePlateau.h"
#include "GraphicDispatcher.h"
#include "GestionnaireSon.h"

#include <iostream>

MenuEntrePlateau::MenuEntrePlateau(sf::Vector2f taillePlateau, std::string ecriture):
_ecriture(ecriture, GraphicDispatcher::getFont(0), 90),
_fond(sf::Vector2f(taillePlateau)),
_temps()
{
    GestionnaireSon::stopToutesMusiques();
    GestionnaireSon::jouer("pacman_intermission.ogg");
    _ecriture.setPosition((taillePlateau.x - (_ecriture.getGlobalBounds().width))/2,
                          (taillePlateau.y - (_ecriture.getGlobalBounds().height))/2
                          );
}

MenuEntrePlateau::~MenuEntrePlateau()
{
    
}

void MenuEntrePlateau::update(sf::Time &delta)
{
    _temps.update();
}

void MenuEntrePlateau::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_ecriture);
}

Temps MenuEntrePlateau::getTemps()const
{
    return _temps;
}