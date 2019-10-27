//
//  GameOver.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 31/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__GameOver__
#define __ProjetPacman__GameOver__

#include <SFML/Graphics.hpp>
#include <vector>

class GameOver
{
private:

    enum class Focus
    {
        Yes = 0,
        No = 1
    };
    
    Focus                   _focus;
    bool                    _retournerEtat;
    
    sf::RectangleShape      _fond;
    sf::Text                _titre;
    sf::Text                _recommencer;
    std::vector<sf::Text>   _listeTexte;
    
public:
    
    GameOver(sf::Vector2f taillePlateau);
    ~GameOver();
    
    std::string recupererReponse()const;
    
    void draw(sf::RenderWindow& renderer);
    void update(sf::Time& delta);
    void processEvent(sf::Event& evt);
    
};

#endif /* defined(__ProjetPacman__GameOver__) */
