//
//  Fruit.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 20/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Fruit__
#define __ProjetPacman__Fruit__

#include <SFML/Graphics.hpp>
#include "GraphicDispatcher.h"

class Fruit
{
private:
    
    int                 _nbColonne;
    int                 _nbLigne;
    int                 _nbPoint;
    sf::Sprite          _sprite;
    bool                _present;
    
public:
    
    Fruit();
    Fruit(int ligne, int colonne, int niveauPlateau);
    ~Fruit();
    
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    
    void setPosition(sf::Vector2f position);
    
    bool estPresent()const;
    int getPoint()const;
    sf::Vector2f getPositionMatriciel()const;
    sf::Vector2f getPosition()const;
    sf::FloatRect getGlobalBouds()const;
};

#endif /* defined(__ProjetPacman__Fruit__) */
