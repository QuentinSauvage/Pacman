//
//  MenuEntrePlateau.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 23/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__MenuEntrePlateau__
#define __ProjetPacman__MenuEntrePlateau__

#include <SFML/Graphics.hpp>
#include "Temps.h"

class MenuEntrePlateau
{
    
private:
    
    sf::Text            _ecriture;
    sf::RectangleShape  _fond;
    Temps               _temps;
    
public:
    
    MenuEntrePlateau(sf::Vector2f taillePlateau, std::string ecriture);
    ~MenuEntrePlateau();
    
    void draw(sf::RenderWindow& renderer);
    void update(sf::Time& delta);
    
    Temps getTemps()const;
    
};

#endif /* defined(__ProjetPacman__MenuEntrePlateau__) */
