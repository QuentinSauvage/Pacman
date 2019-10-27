//
//  MenuChoixTheme.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 23/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__MenuChoixTheme__
#define __ProjetPacman__MenuChoixTheme__

#include <SFML/Graphics.hpp>

class MenuChoixTheme
{
    
private:
    
    enum class Focus
    {
        Pacman,
        Lotr
    };
    
    bool                _retournerChoix;
    Focus               _focus;
    std::string         _theme;
    
    sf::Text            _titre;
    sf::Text            _pacmanText;
    sf::Text            _lotrText;
    
    sf::RectangleShape  _fond;
    
public:
    
    MenuChoixTheme(sf::Vector2f taillePlateau);
    ~MenuChoixTheme();
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    
    std::string getTheme()const;
    bool        valideRetournerEtat()const;
    
};

#endif /* defined(__ProjetPacman__MenuChoixTheme__) */
