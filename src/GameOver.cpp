//
//  GameOver.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 31/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "GameOver.h"
#include "GraphicDispatcher.h"
#include "GestionnaireSon.h"
#include <iostream>

GameOver::GameOver(sf::Vector2f taillePlateau):
_titre("Game Over", GraphicDispatcher::getFont(0), 100),
_recommencer("Recommencer ?", GraphicDispatcher::getFont(0), 100),
_focus(Focus::Yes),
_fond(taillePlateau),
_retournerEtat(false)
{
    _fond.setTexture(&GraphicDispatcher::getFondPacman("gameover.png"));
    _titre.setPosition((taillePlateau.x - _titre.getGlobalBounds().width ) / 2, 0);
    _recommencer.setPosition((taillePlateau.x - _recommencer.getGlobalBounds().width) / 2, 300);
    
    _listeTexte.push_back(sf::Text("Oui", GraphicDispatcher::getFont(0), 85));
    _listeTexte.push_back(sf::Text("Non", GraphicDispatcher::getFont(0), 85));
    
    //300 = espacement
    int posX = (taillePlateau.x - (_listeTexte[0].getGlobalBounds().width + _listeTexte[1].getGlobalBounds().width + 300)) / 2;
    int posY = 600;
    _listeTexte[0].setPosition(posX, posY);
    _listeTexte[1].setPosition(posX + _listeTexte[0].getGlobalBounds().width + 300, posY);
}

GameOver::~GameOver()
{
}

std::string GameOver::recupererReponse()const
{
    if(_retournerEtat)
    {
        switch(_focus)
        {
            case(Focus::Yes):
            {
                return "oui";
                break;
            }
            case(Focus::No):
            {
                return "non";
                break;
            }
        }
    }
    else
    {
        return "pasDefini";
    }
}

void GameOver::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_fond);
    renderer.draw(_titre);
    renderer.draw(_recommencer);
    for(sf::Text i : _listeTexte)
        renderer.draw(i);
}

void GameOver::processEvent(sf::Event &evt)
{
    //Evenement clavier
    if(evt.type == sf::Event::KeyPressed)
    {
        if(evt.key.code == sf::Keyboard::Left)
        {
            if(_focus == Focus::No)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::Yes;
            }
        }
        if(evt.key.code == sf::Keyboard::Right)
        {
            if(_focus == Focus::Yes)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::No;
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
        for(int i = 0; i < _listeTexte.size(); i++)
        {
            if(_listeTexte[i].getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
                _focus = static_cast<Focus>(i);
        }
    }
}

void GameOver::update(sf::Time& delta)
{
    switch(_focus)
    {
        case(Focus::Yes):
        {
            _listeTexte[0].setColor(sf::Color::Yellow);
            _listeTexte[1].setColor(sf::Color::White);
            break;
        }
        case(Focus::No):
        {
            _listeTexte[0].setColor(sf::Color::White);
            _listeTexte[1].setColor(sf::Color::Yellow);
            break;
        }
    }
}
