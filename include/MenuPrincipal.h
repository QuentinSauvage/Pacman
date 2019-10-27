//
//  MenuPrincipal.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 27/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__MenuPrincipal__
#define __ProjetPacman__MenuPrincipal__

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "GraphicDispatcher.h"

class MenuPrincipal
{
    
private:
    
    enum class Focus
    {
        Jouer = 1,
        Option = 2,
        Statistiques = 3,
        Quitter = 4
    };
    
    sf::Vector2f            _taillePlateau;
    bool                    _retournerResultat;
    std::string             _pseudoJoueur;
    
    Focus                   _focus;
    
    sf::RectangleShape      _fond;
    std::vector<sf::Text>   _listeEcriture;
    

    
    void placerTexte();
    
public:
    
    MenuPrincipal(sf::Vector2f taillePlateau, std::string theme, std::string pseudoJoueur);
    ~MenuPrincipal();
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    
    std::string getBouttonAppuyer()const;
};

#endif /* defined(__ProjetPacman__MenuPrincipal__) */
