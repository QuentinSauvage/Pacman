//
//  MenuStatistiques.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 05/06/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__MenuStatistiques__
#define __ProjetPacman__MenuStatistiques__

#include <SFML/Graphics.hpp>
#include "Informateur.h"
#include "Joueur.h"
#include "ListeSucces.h"

class MenuStatistiques
{
    
private:
    
    enum class Focus
    {
        revenirMenu,
        Aucun
    };
    
    enum class Scroll
    {
        Haut,
        Bas,
        Aucun
    };
    
    Joueur&                 _joueur;
    sf::RectangleShape      _fond;
    sf::Text                _titre;
    sf::Text                _texteRevenirMenu;
    std::vector<sf::Text>   _statistiques;
    bool                    _revenirMenu;
    Focus                   _focus;
    Scroll                  _etatScroll;
    
    sf::Vector2f            _taillePlateau;
    
    void placerStatistiques();
    
public:
    
    MenuStatistiques(sf::Vector2f taillePlateau, Joueur& joueur);
    ~MenuStatistiques();
    
    std::string getBouttonAppuyer()const;
    std::string getEtatScroll()const;
    int getNombreSucces()const;
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
};

#endif /* defined(__ProjetPacman__MenuStatistiques__) */
