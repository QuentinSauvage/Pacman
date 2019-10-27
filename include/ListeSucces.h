//
//  ListeSucces.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 27/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__ListeSucces__
#define __ProjetPacman__ListeSucces__

#include <vector>
#include "Succes.h"

class ListeSucces
{
    
private:
    
    std::vector<Succes>     _listeSucces;
    static int              _nbSucces;
    
    sf::Vector2f            _taillePlateau;
    
public:
    
    ListeSucces(sf::Vector2f taillePlateau);
    ~ListeSucces();
    
    static int getNombreSucces();
    
    int getValeurSucces(std::string nomSucces)const;
    void deverouillerSucces(int index);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    
    
};

#endif /* defined(__ProjetPacman__ListeSucces__) */
