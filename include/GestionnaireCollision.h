//
//  GestionnaireCollision.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 03/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__GestionnaireCollision__
#define __ProjetPacman__GestionnaireCollision__

#include <SFML/Graphics.hpp>
#include "Map.h"

class Pacman;
class Fantome;

class GestionnaireCollision
{
private:
    
    static sf::Vector2f _wallSize;
    
public:
    
    static void setWallSize(const sf::Vector2f& size);
    static void updateWallSize(const sf::Vector2f& size);
    static bool collisionMur(const Pacman& pacman, const Case& mur);
    static bool collisionMur(const Fantome& fantome, const Case& mur);
    static bool collisionFantome(const Fantome& fantome, const Pacman& pacman);
    static bool collisionPacgomme(const Pacman& pacman, const Case& uneCase, char direction);
};

#endif /* defined(__ProjetPacman__GestionnaireCollision__) */
