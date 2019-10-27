//
//  Temps.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 19/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Temps__
#define __ProjetPacman__Temps__

#include <SFML/Graphics.hpp>

class Temps
{
private:
    
    sf::Clock   _horloge;
    sf::Time    _sauvegardeTemps;
    sf::Time    _tempsEfficiant;
    bool        _pause;
    
public:
    
    Temps();
    ~Temps();
    
    void update();
    void pause();
    void reprendre();
    void redemarrer();
    
    bool enPause()const;
    int  getTempsSecondes()const;
    sf::Time& getTempsReel();
    
};

#endif /* defined(__ProjetPacman__Temps__) */
