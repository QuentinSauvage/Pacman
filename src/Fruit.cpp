//
//  Fruit.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 20/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Fruit.h"

//2 par niveau
//1er = 70 dots
//2eme = 170dots


Fruit::Fruit():
_nbColonne(0),
_nbLigne(0)
{
    
}

Fruit::Fruit(int ligne, int colonne, int niveauPlateau):
_nbLigne(ligne),
_nbColonne(colonne),
_sprite(GraphicDispatcher::getTextureFruit(niveauPlateau-1)),
_present(true),
_nbPoint(niveauPlateau*20)
{
    
}

Fruit::~Fruit()
{
    
}

bool Fruit::estPresent()const
{
    return _present;
}

int Fruit::getPoint()const
{
    return _nbPoint;
}

sf::Vector2f Fruit::getPosition()const
{
    return _sprite.getPosition();
}

sf::Vector2f Fruit::getPositionMatriciel()const
{
    return sf::Vector2f(_nbLigne, _nbColonne);
}

void Fruit::setPosition(sf::Vector2f position)
{
    _sprite.setPosition(position);
}

sf::FloatRect Fruit::getGlobalBouds()const
{
    return _sprite.getGlobalBounds();
}

void Fruit::update(sf::Time &delta)
{
    
}

void Fruit::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_sprite);
}

