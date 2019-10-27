//
//  Pause.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 11/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Pause.h"
#include "GestionnaireSon.h"
#include "GraphicDispatcher.h"
#include <iostream>

Pause::Pause(sf::Vector2f tailleFenetre):
_textePause("Pause", GraphicDispatcher::getFont(0), 150),
_reprendre("Reprendre", GraphicDispatcher::getFont(0), 80),
_menuPrincipal("Menu Principal", GraphicDispatcher::getFont(0), 80),
_quitter("Quitter jeu", GraphicDispatcher::getFont(0), 80),
_fond(tailleFenetre),
_focus(Focus::Reprendre),
_retournerEtat(false)
{
    _reprendre.setColor(sf::Color::Yellow);
    _fond.setPosition(0,0);
    _fond.setFillColor(sf::Color::Black);
    _textePause.setPosition((tailleFenetre.x - _textePause.getGlobalBounds().width)/2, 50);
    _reprendre.setPosition((tailleFenetre.x - _reprendre.getGlobalBounds().width)/2, 300);
    _menuPrincipal.setPosition((tailleFenetre.x - _menuPrincipal.getGlobalBounds().width)/2, 400);
    _quitter.setPosition((tailleFenetre.x - _quitter.getGlobalBounds().width)/2, 500);
    
}

Pause::~Pause()
{
    
}

void Pause::reinitialiserPause()
{
    _focus = Focus::Reprendre;
    _retournerEtat = false;
}


std::string Pause::getBoutonAppuyer()const
{
    if(_retournerEtat)
    {
        switch(_focus)
        {
            case(Focus::Reprendre):
            {
                return "reprendre";
                break;
            }
            case(Focus::MenuPrincipal):
            {
                return "menuPrincipal";
                break;
            }
            case(Focus::Quitter):
            {
                return "quitter";
                break;
            }
        }
    }
    else
    {
        return "nonDefini";
    }
}


void Pause::draw(sf::RenderWindow& renderer)
{
        renderer.draw(_fond);
        renderer.draw(_textePause);
        renderer.draw(_reprendre);
        renderer.draw(_menuPrincipal);
        renderer.draw(_quitter);
}

void Pause::update()
{
    switch (_focus)
    {
        case (Focus::Reprendre):
        {
            _reprendre.setColor(sf::Color::Yellow);
            _menuPrincipal.setColor(sf::Color::White);
            _quitter.setColor(sf::Color::White);
            break;
        }
        case (Focus::MenuPrincipal):
        {
            _reprendre.setColor(sf::Color::White);
            _menuPrincipal.setColor(sf::Color::Yellow);
            _quitter.setColor(sf::Color::White);
            break;
        }
        case (Focus::Quitter):
        {
            _reprendre.setColor(sf::Color::White);
            _menuPrincipal.setColor(sf::Color::White);
            _quitter.setColor(sf::Color::Yellow);
            break;
        }
    }
}

void Pause::processEvent(sf::Event& evt)
{
    //Evenement clavier
    if(evt.type == sf::Event::KeyPressed)
    {
        if(evt.key.code == sf::Keyboard::Down)
        {
            if(_focus == Focus::Reprendre)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::MenuPrincipal;
            }
            else if(_focus == Focus::MenuPrincipal)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::Quitter;
            }
        }
        
        if(evt.key.code == sf::Keyboard::Up)
        {
            if(_focus == Focus::MenuPrincipal)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::Reprendre;
            }
            else if(_focus == Focus::Quitter)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::MenuPrincipal;
            }
        }
        
        if(evt.key.code == sf::Keyboard::Return)
        {
            _retournerEtat = true;
        }
    }
    //Evenement souris
    if(evt.type == sf::Event::MouseButtonPressed)
    {
        if(_reprendre.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
        {
            GestionnaireSon::jouer("changementFocus.wav");
            _focus = Focus::Reprendre;
        }
        if(_menuPrincipal.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
        {
            GestionnaireSon::jouer("changementFocus.wav");
            _focus = Focus::MenuPrincipal;
        }
        if(_quitter.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
        {
            GestionnaireSon::jouer("changementFocus.wav");
            _focus = Focus::Quitter;
        }
    }
}

