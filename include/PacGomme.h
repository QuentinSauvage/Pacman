//
//  PacGomme.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 05/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__PacGomme__
#define __ProjetPacman__PacGomme__

#include <SFML/Graphics.hpp>

class PacGomme
{
    
private:
    
    int     _pointRapporte;
    int     _posX;
    int     _posY;
    
public:
    
    PacGomme();
    PacGomme(int posX, int posY);
    ~PacGomme();
    
    void setPosX(int x);
    void setPosY(int y);
    
    int getPointRapporte()const;
    sf::Vector2f getPosition()const;
};

#endif /* defined(__ProjetPacman__PacGomme__) */
