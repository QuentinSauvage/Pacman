//
//  GestionnaireCollision.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 03/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "GestionnaireCollision.h"
#include "Pacman.h"
#include "Fantome.h"
#include <iostream>

sf::Vector2f GestionnaireCollision::_wallSize = sf::Vector2f(600,400);

void GestionnaireCollision::setWallSize(const sf::Vector2f& size)
{
    _wallSize = size;
}

void GestionnaireCollision::updateWallSize(const sf::Vector2f& size)
{
    _wallSize = size;
}

bool GestionnaireCollision::collisionMur(const Pacman& pacman, const Case& mur)
{
    // 0 et 4 représente les tile ou l'on peut passer
    if(mur.getType() != 0 && mur.getType() != 4 && mur.getType() != 5)
    {
        return pacman.getSprite().getGlobalBounds().intersects(mur.getRectangle().getGlobalBounds());
    }
    else
    {
        return false;
    }
}

bool GestionnaireCollision::collisionMur(const Fantome& fantome, const Case& mur)
{
    if(fantome.estSorti())
    {
        if(mur.getType() != 0 && mur.getType() != 4 && mur.getType() != 5)
        {
            return fantome.getSprite().getGlobalBounds().intersects(mur.getRectangle().getGlobalBounds());
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(mur.getType() != 0 && mur.getType() != 3 && mur.getType() != 4 && mur.getType() != 5)
        {
            return fantome.getSprite().getGlobalBounds().intersects(mur.getRectangle().getGlobalBounds());
        }
        else
        {
            return false;
        }
    }
}

bool GestionnaireCollision::collisionFantome(const Fantome& fantome, const Pacman& pacman)
{
    return pacman.getSprite().getGlobalBounds().intersects(fantome.getSprite().getGlobalBounds());
}

bool GestionnaireCollision::collisionPacgomme(const Pacman& pacman, const Case& uneCase, char direction)
{
    switch(direction)
    {
        case 'z':
        {
            if(uneCase.getType() == 4 && uneCase.pacGommePresente() &&
               uneCase.getRectangle().getGlobalBounds().contains(pacman.getPosition().x,pacman.getPosition().y + 23))
            {
                return true;
            }
            else if(uneCase.getType() == 5 && uneCase.pacGommePresente() &&
                    uneCase.getRectangle().getGlobalBounds().contains(pacman.getPosition().x, pacman.getPosition().y + 23))
            {
                return true;
            }
            
            return false;
            
            break;
        }
        case 's':
        {
            if(uneCase.getType() == 4 && uneCase.pacGommePresente() &&
               uneCase.getRectangle().getGlobalBounds().contains(pacman.getPosition().x, pacman.getPosition().y + 5))
            {
                return true;
            }
            else if(uneCase.getType() == 5 && uneCase.pacGommePresente() &&
                    uneCase.getRectangle().getGlobalBounds().contains(pacman.getPosition().x, pacman.getPosition().y + 5))
            {
                return true;
            }
            
            return false;
            
                        break;
        }
        case 'q':
        {
            if(uneCase.getType() == 4 && uneCase.pacGommePresente() &&
               uneCase.getRectangle().getGlobalBounds().contains(pacman.getPosition().x + 23, pacman.getPosition().y))
            {
                return true;
            }
            else if(uneCase.getType() == 5 && uneCase.pacGommePresente() &&
                    uneCase.getRectangle().getGlobalBounds().contains(pacman.getPosition().x+23, pacman.getPosition().y))
            {
                return true;
            }
            
            return false;
            
                       break;
        }
        case 'd':
        {
            if(uneCase.getType() == 4 && uneCase.pacGommePresente() &&
               uneCase.getRectangle().getGlobalBounds().contains(pacman.getPosition().x + 5, pacman.getPosition().y))
            {
                return true;
            }
            else if(uneCase.getType() == 5 && uneCase.pacGommePresente() &&
                    uneCase.getRectangle().getGlobalBounds().contains(pacman.getPosition().x +5, pacman.getPosition().y))
            {
                return true;
            }
            
            return false;
            
                        break;
        }
    }
}