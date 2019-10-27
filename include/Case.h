//
//  Case.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 05/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Case__
#define __ProjetPacman__Case__

#include <SFML/Graphics.hpp>
#include "PacGomme.h"

class Case
{
    
private:
    
    bool                        _contientPacGomme;
    
    sf::RectangleShape          _shape;
    int                         _identifiant;
    PacGomme                    _pacGomme;
    
public:
    
    Case(int identifiant, sf::Vector2f size, sf::Vector2f position, bool contientPacGomme);
    ~Case();
    
    bool                pacGommePresente()const;
    
    int                 getType()const;
    void                setType(int identifiant);
    sf::Vector2f        getPosition()const;
    sf::RectangleShape  getRectangle()const;
    int                 getPointPacGomme()const;
    sf::Vector2f        getPositionPacGomme()const;
    
    void                desactiverPacGomme();
    void                processEvent();
    
};

#endif /* defined(__ProjetPacman__Case__) */
