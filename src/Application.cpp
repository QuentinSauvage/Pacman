//
//  Application.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 24/04/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Application.h"
#include <iostream>

Application::Application():
_width(1400),
_height(768),
_window(sf::VideoMode(_width, _height), "Pacman"),
_vue(_window.getDefaultView()),
_gestionnaireMenu(sf::Vector2f(_width, _height), _vue)
{
    _window.setKeyRepeatEnabled(false);
    _window.setFramerateLimit(60);
    GestionnaireCollision::setWallSize(sf::Vector2f(_width, _height));
    
    _window.setView(_vue.getVue());
    
}

Application::~Application()
{

}


void Application::processEvent()
{
    sf::Clock heure;
    while(_window.isOpen())
    {
        sf::Time delta = heure.restart();
        sf::Event evt;

        while (_window.pollEvent(evt))
        {
            if(evt.type == sf::Event::Closed)
                _window.close();
            if(evt.type == sf::Event::Resized)
            {
                _width = _window.getSize().x;
                _height = _window.getSize().y;
                
            }
            if(evt.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i posMouse = sf::Mouse::getPosition(_window);
                sf::Vector2f worldPos = _window.mapPixelToCoords(posMouse);
                
                evt.mouseButton.x = worldPos.x;
                evt.mouseButton.y = worldPos.y;
            }

            _gestionnaireMenu.processEvent(evt);
        }
        _gestionnaireMenu.update(delta);
        this->update();

        draw();

    }
}

void Application::update()
{
    _window.setView(_vue.getVue());
    if(_gestionnaireMenu.quitterPartie())
    {
        _window.close();
    }
}

void Application::draw()
{
    _gestionnaireMenu.draw(_window);
    _window.display();
    _window.clear();
    
}