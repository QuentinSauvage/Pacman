//
//  MenuChoixTheme.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 23/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "MenuChoixTheme.h"
#include "GraphicDispatcher.h"
#include "GestionnaireSon.h"
#include "OutilsDivers.h"
#include <iostream>

MenuChoixTheme::MenuChoixTheme(sf::Vector2f taillePlateau):
_focus(Focus::Pacman),
_retournerChoix(false),
_titre("Theme", GraphicDispatcher::getFont(0), 120),
_lotrText("LOTR", GraphicDispatcher::getFont(0), 50),
_pacmanText("Pacman", GraphicDispatcher::getFont(0), 50),
_theme("")
{
    int espacementTheme = 200; //200 Px
    int espaceXOccupe = _lotrText.getGlobalBounds().width + _pacmanText.getGlobalBounds().width + espacementTheme;
    int posX = (taillePlateau.x - espaceXOccupe) / 2;
    int posY = (taillePlateau.x - _lotrText.getGlobalBounds().height) / (2);
    
    _titre.setPosition( (taillePlateau.x - _titre.getGlobalBounds().width) / 2,0);
    _pacmanText.setPosition(posX,posY);
    _lotrText.setPosition(posX+_pacmanText.getGlobalBounds().width+200,posY);
    _fond.setSize(taillePlateau);
    _fond.setPosition(0, 0);
    

    
    _fond.setTexture(&GraphicDispatcher::getFondPacman("fond"+std::to_string(getRandom(1, 4))+".png"));

    
}
MenuChoixTheme::~MenuChoixTheme()
{
    
}

std::string MenuChoixTheme::getTheme()const
{
    if(_retournerChoix)
    {
        if(_focus == Focus::Pacman)
        {
            return "themePacman";
        }
        else
        {
            return "themeLotr";
        }
    }
    else
    {
        return "pasDefini";
    }
}

void MenuChoixTheme::processEvent(sf::Event& evt)
{
    //Evenement Clavier
    if(evt.type == sf::Event::KeyPressed)
    {
        if(evt.key.code == sf::Keyboard::Right)
        {
            if(_focus == Focus::Pacman)
            {
                GestionnaireSon::stopToutesMusiques();
                GestionnaireSon::jouerMusiqueFond("themeLotr");
                _focus = Focus::Lotr;
                _fond.setTexture(&GraphicDispatcher::getFondLotr("fond"+std::to_string(getRandom(1, 4))+".png"));
            }
        }
        if(evt.key.code == sf::Keyboard::Left)
        {
            if(_focus == Focus::Lotr)
            {
                GestionnaireSon::stopToutesMusiques();
                GestionnaireSon::jouerMusiqueFond("themePacman");
                _focus = Focus::Pacman;
                _fond.setTexture(&GraphicDispatcher::getFondPacman("fond"+std::to_string(getRandom(1, 4))+".png"));
            }
        }
        if(evt.key.code == sf::Keyboard::Return)
        {
            _retournerChoix = true;
        }
    }
    
    //Evenement souris
    if(evt.type == sf::Event::MouseButtonPressed)
    {
        if(_pacmanText.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
        {
            GestionnaireSon::jouer("changementFocus.wav");
            _focus = Focus::Pacman;
            _fond.setTexture(&GraphicDispatcher::getFondPacman("fond"+std::to_string(getRandom(1, 4))+".png"));
        }
        
        if(_lotrText.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
        {
            GestionnaireSon::jouer("changementFocus.wav");
            _focus = Focus::Lotr;
            _fond.setTexture(&GraphicDispatcher::getFondLotr("fond"+std::to_string(getRandom(1, 4))+".png"));
            
        }
    }
}

void MenuChoixTheme::update(sf::Time& delta)
{
    switch (_focus)
    {
        case (Focus::Pacman):
        {
            _pacmanText.setColor(sf::Color::Yellow);
            _lotrText.setColor(sf::Color::White);
            break;
        }
        case (Focus::Lotr):
        {
            _lotrText.setColor(sf::Color::Yellow);
            _pacmanText.setColor(sf::Color::White);
            break;
        }
    }
}

void MenuChoixTheme::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_fond);
    renderer.draw(_titre);
    renderer.draw(_pacmanText);
    renderer.draw(_lotrText);
}