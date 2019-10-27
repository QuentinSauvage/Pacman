//
//  Debuggeur.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 09/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Debuggeur.h"

Debuggeur::Debuggeur()
{
    _message.push_back(sf::Text("Position X Pacman: ", GraphicDispatcher::getFont(0)));
    _message.push_back(sf::Text("Position Y Pacman: ", GraphicDispatcher::getFont(0)));
    _message.push_back(sf::Text("Collision: ", GraphicDispatcher::getFont(0)));
    _message.push_back(sf::Text("Position Matriciel Pacman: ", GraphicDispatcher::getFont(0)));
    _message.push_back(sf::Text("Position Matriciel Case: ", GraphicDispatcher::getFont(0)));
    
    _valeur.push_back(sf::Text("",GraphicDispatcher::getFont(0)));
    _valeur.push_back(sf::Text("",GraphicDispatcher::getFont(0)));
    _valeur.push_back(sf::Text("",GraphicDispatcher::getFont(0)));
    _valeur.push_back(sf::Text("",GraphicDispatcher::getFont(0)));
    _valeur.push_back(sf::Text("",GraphicDispatcher::getFont(0)));
    
    initTextPosition();
    
}

Debuggeur::~Debuggeur()
{
    
}

void Debuggeur::update(sf::Time& delta)
{
    
}

void Debuggeur::draw(sf::RenderWindow& renderer)
{
    for(int i = 0; i < _message.size(); ++i)
    {
        renderer.draw(_message[i]);
        renderer.draw(_valeur[i]);
    }
}

void Debuggeur::initTextPosition()
{
    /**
     * 100 = début de la carte
     * 32 * 24 = 32 px * 24 cases
     * 25 = plus aéré
     */
    int constantXMessage = 100 + 32*24 + 25;
    int variableY = 600;
    for(int i = 0; i < _message.size(); ++i)
    {
        _message[i].setPosition(constantXMessage, variableY);
        //+ 10 pour aéré
        _valeur[i].setPosition(constantXMessage + _message[i].getGlobalBounds().width + 10, variableY);
        variableY += _message[i].getGlobalBounds().height + 10;
    }
}

void Debuggeur::setValeurs(std::string xPac, std::string yPac, std::string posMatricielPac, std::string posMatricielCase)
{
    _valeur[0].setString(xPac);
    _valeur[1].setString(yPac);
    _valeur[3].setString(posMatricielPac);
    _valeur[4].setString(posMatricielCase);
}

void Debuggeur::setCollision(std::string collision)
{
    _valeur[2].setString(collision);
}