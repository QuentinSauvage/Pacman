//
//  Debuggeur.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 09/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Debuggeur__
#define __ProjetPacman__Debuggeur__

#include <vector>
#include <SFML/Graphics.hpp>

#include "GraphicDispatcher.h"

class Debuggeur
{
    
private:
    
    std::vector<sf::Text>    _message;
    std::vector<sf::Text>    _valeur;
    
public:
    
    Debuggeur();
    ~Debuggeur();
    
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    void setValeurs(std::string xPac, std::string yPac, std::string posMatricielPac, std::string posMatricielCase);
    void setCollision(std::string collision);
    
    void initTextPosition();
};

#endif /* defined(__ProjetPacman__Debuggeur__) */
