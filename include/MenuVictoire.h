//
//  MenuVictoire.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 08/06/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__MenuVictoire__
#define __ProjetPacman__MenuVictoire__

#include <SFML/Graphics.hpp>
#include <vector>
class MenuVictoire
{
    
private:
    
    enum class Focus
    {
        Rejouer = 0,
        MenuPrincipal = 1,
        Quitter = 2
    };
    
    bool                    _retournerEtat;
    sf::RectangleShape      _fond;
    sf::Text                _texteVictoire;
    std::vector<sf::Text>   _listeTexte;
    Focus                   _focus;
    
    sf::Vector2f            _taillePlateau;
    
    
    void construireTexte();
    
public:
    
    MenuVictoire(sf::Vector2f taillePlateau, std::string theme);
    ~MenuVictoire();
    
    std::string getBoutonAppuyer();
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);

};

#endif /* defined(__ProjetPacman__MenuVictoire__) */
