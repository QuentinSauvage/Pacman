//
//  MenuVictoire.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 08/06/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "MenuVictoire.h"
#include "GraphicDispatcher.h"
#include "GestionnaireSon.h"
#include <iostream>

MenuVictoire::MenuVictoire(sf::Vector2f taillePlateau, std::string theme):
_taillePlateau(taillePlateau),
_focus(Focus::Rejouer),
_retournerEtat(false),
_fond(taillePlateau)
{
    _fond.setPosition(0,0);
    if(theme == "themePacman")
    {
        _fond.setTexture(&GraphicDispatcher::getFondPacman("victoire.png"));
    }
    else
    {
        _fond.setTexture(&GraphicDispatcher::getFondLotr("victoire.png"));
    }
    
    _listeTexte.push_back(sf::Text("Rejouer", GraphicDispatcher::getFont(4), 40));
    _listeTexte.push_back(sf::Text("Menu Principal", GraphicDispatcher::getFont(4), 40));
    _listeTexte.push_back(sf::Text("Quitter", GraphicDispatcher::getFont(4), 40));
    
    construireTexte();
}

MenuVictoire::~MenuVictoire()
{
    
}

void MenuVictoire::construireTexte()
{
    int positionY = 650;
    int positionXOccupe = _listeTexte[0].getGlobalBounds().width + _listeTexte[1].getGlobalBounds().width + _listeTexte[2].getGlobalBounds().width + (2*150);
    int positionX = (_taillePlateau.x - positionXOccupe)/2;
    
    _listeTexte[0].setPosition(positionX,positionY);
    _listeTexte[1].setPosition(positionX + _listeTexte[0].getGlobalBounds().width + 150,positionY);
    _listeTexte[2].setPosition(_listeTexte[1].getPosition().x + _listeTexte[1].getGlobalBounds().width + 150,positionY);
    
}

std::string MenuVictoire::getBoutonAppuyer()
{
    if(_retournerEtat)
    {
        if(_focus == Focus::Rejouer)
            return "rejouer";
        if(_focus == Focus::MenuPrincipal)
            return "menuPrincipal";
        if(_focus == Focus::Quitter)
            return "quitter";
    }
    else
    {
        return "nonDefini";
    }
}

void MenuVictoire::processEvent(sf::Event& evt)
{
    //Evenement clavier
    if(evt.type == sf::Event::KeyPressed)
    {
        if(evt.key.code == sf::Keyboard::Right)
        {
            if(_focus == Focus::Rejouer)
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
        if(evt.key.code == sf::Keyboard::Left)
        {
            if(_focus == Focus::MenuPrincipal)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::Rejouer;
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
        for(int i = 0; i < _listeTexte.size(); i++)
            if(_listeTexte[i].getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
                _focus = static_cast<Focus>(i);
    }
}

void MenuVictoire::update(sf::Time& delta)
{
    switch (_focus)
    {
        case(Focus::Rejouer):
        {
            _listeTexte[0].setColor(sf::Color::Yellow);
            _listeTexte[1].setColor(sf::Color::White);
            _listeTexte[2].setColor(sf::Color::White);
            
            break;
        }
        case(Focus::MenuPrincipal):
        {
            _listeTexte[0].setColor(sf::Color::White);
            _listeTexte[1].setColor(sf::Color::Yellow);
            _listeTexte[2].setColor(sf::Color::White);
            
            break;
        }
        case(Focus::Quitter):
        {
            _listeTexte[0].setColor(sf::Color::White);
            _listeTexte[1].setColor(sf::Color::White);
            _listeTexte[2].setColor(sf::Color::Yellow);
            
            break;
        }
    }
}

void MenuVictoire::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_fond);
    renderer.draw(_texteVictoire);
    for(auto i : _listeTexte)
        renderer.draw(i);
}