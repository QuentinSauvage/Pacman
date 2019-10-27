//
//  Pause.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 11/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Pause__
#define __ProjetPacman__Pause__

#include <SFML/Graphics.hpp>

class Pause
{
    enum class Focus
    {
        Reprendre,
        MenuPrincipal,
        Quitter
    };
    
private:
    
    //Juste un texte d'affichage
    sf::Text            _textePause;
    sf::RectangleShape  _fond;

    //Texte qui interagisse si on les clique ou focus.
    sf::Text            _reprendre;
    sf::Text            _menuPrincipal;
    sf::Text            _quitter;

    Focus               _focus;
    
    bool                _retournerEtat;

    
public:
    
    Pause(sf::Vector2f tailleFenetre);
    Pause(Pause& pause) = delete;
    ~Pause();
    
    std::string getBoutonAppuyer()const;
    
    void processEvent(sf::Event& evt);
    void update();
    void draw(sf::RenderWindow& renderer);
    void reinitialiserPause();
    
    Pause operator=(Pause& pause) = delete;
};

#endif /* defined(__ProjetPacman__Pause__) */
