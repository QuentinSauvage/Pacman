//
//  MenuPrincipal.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 27/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "MenuPrincipal.h"
#include "OutilsDivers.h"
#include "GraphicDispatcher.h"
#include "GestionnaireSon.h"

MenuPrincipal::MenuPrincipal(sf::Vector2f taillePlateau, std::string theme, std::string pseudoJoueur):
_focus(Focus::Jouer),
_taillePlateau(taillePlateau),
_fond(taillePlateau),
_retournerResultat(false)
{
    if(theme == "themePacman")
        _fond.setTexture(&GraphicDispatcher::getFondPacman("fond"+std::to_string(getRandom(1, 4))+".png"));
    else
        _fond.setTexture(&GraphicDispatcher::getFondLotr("fond"+std::to_string(getRandom(1, 4))+".png"));
    
    _listeEcriture.push_back(sf::Text("Menu Principal", GraphicDispatcher::getFont(0), 140));
    _listeEcriture.push_back(sf::Text("Jouer", GraphicDispatcher::getFont(0), 70));
    _listeEcriture.push_back(sf::Text("Options", GraphicDispatcher::getFont(0), 70));
    _listeEcriture.push_back(sf::Text("Statistiques", GraphicDispatcher::getFont(0), 70));
    _listeEcriture.push_back(sf::Text("Quitter", GraphicDispatcher::getFont(0), 70));
    
    placerTexte();
}

MenuPrincipal::~MenuPrincipal()
{
    
}

void MenuPrincipal::placerTexte()
{
    int y = 0;
    for(int i = 0; i < _listeEcriture.size(); i++)
    {
        int positionX = (_taillePlateau.x - _listeEcriture[i].getGlobalBounds().width) / 2;
        _listeEcriture[i].setPosition(sf::Vector2f(positionX, y));
        y+= 165;
    }
}

std::string MenuPrincipal::getBouttonAppuyer()const
{
    if(_retournerResultat)
    {
        switch(_focus)
        {
            case(Focus::Jouer):
            {
                return "Jouer";
                break;
            }
            case(Focus::Option):
            {
                return "Option";
                break;
            }
            case(Focus::Statistiques):
            {
                return "Statistiques";
                break;
            }
            case(Focus::Quitter):
            {
                return "Quitter";
                break;
            }
        }
    }
    else
    {
        return "retournerFaux";
    }
}

void MenuPrincipal::processEvent(sf::Event& evt)
{
    //Evenement clavier
    if(evt.type == sf::Event::KeyPressed)
    {
        if(evt.key.code == sf::Keyboard::Down)
        {
            switch(_focus)
            {
                case (Focus::Jouer):
                {
                    GestionnaireSon::jouer("changementFocus.wav");
                    _focus = Focus::Option;
                    break;
                }
                case (Focus::Option):
                {
                    GestionnaireSon::jouer("changementFocus.wav");
                    _focus = Focus::Statistiques;
                    break;
                }
                case (Focus::Statistiques):
                {
                    GestionnaireSon::jouer("changementFocus.wav");
                    _focus = Focus::Quitter;
                    break;
                }
                case (Focus::Quitter):
                {
                    break;
                }
            }
        }
        else if(evt.key.code == sf::Keyboard::Up)
        {
            switch(_focus)
            {
                case (Focus::Jouer):
                {
                    break;
                }
                case (Focus::Option):
                {
                    GestionnaireSon::jouer("changementFocus.wav");
                    _focus = Focus::Jouer;
                    break;
                }
                case (Focus::Statistiques):
                {
                    GestionnaireSon::jouer("changementFocus.wav");
                    _focus = Focus::Option;
                    break;
                }
                case (Focus::Quitter):
                {
                    GestionnaireSon::jouer("changementFocus.wav");
                    _focus = Focus::Statistiques;
                    break;
                }
            }
        }
        else if(evt.key.code == sf::Keyboard::Return)
        {
            _retournerResultat = true;
        }
    }
    
    //Evenement souris
    if(evt.type == sf::Event::MouseButtonPressed)
    {
        for(int i = 1; i < _listeEcriture.size(); i++)
        {
            if(_listeEcriture[i].getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = static_cast<Focus>(i);
            }
        }
    }
}

void MenuPrincipal::update(sf::Time& delta)
{
    switch(_focus)
    {
        case(Focus::Jouer):
        {
            _listeEcriture[1].setColor(sf::Color::Yellow);
            _listeEcriture[2].setColor(sf::Color::White);
            _listeEcriture[3].setColor(sf::Color::White);
            _listeEcriture[4].setColor(sf::Color::White);
            break;
        }
        case(Focus::Option):
        {
            _listeEcriture[1].setColor(sf::Color::White);
            _listeEcriture[2].setColor(sf::Color::Yellow);
            _listeEcriture[3].setColor(sf::Color::White);
            _listeEcriture[4].setColor(sf::Color::White);
            break;
        }
        case(Focus::Statistiques):
        {
            _listeEcriture[1].setColor(sf::Color::White);
            _listeEcriture[2].setColor(sf::Color::White);
            _listeEcriture[3].setColor(sf::Color::Yellow);
            _listeEcriture[4].setColor(sf::Color::White);
            break;
        }
        case(Focus::Quitter):
        {
            _listeEcriture[1].setColor(sf::Color::White);
            _listeEcriture[2].setColor(sf::Color::White);
            _listeEcriture[3].setColor(sf::Color::White);
            _listeEcriture[4].setColor(sf::Color::Yellow);
            break;
        }
    }
}

void MenuPrincipal::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_fond);
    for(sf::Text i : _listeEcriture)
    {
        renderer.draw(i);
    }
}