//
//  Succes.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 25/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include <fstream>
#include "GraphicDispatcher.h"
#include "Succes.h"
#include "OutilsDivers.h"

Succes::Succes(std::pair<std::string, int> info, std::string typeSucces, int idSucces):
_information(info),
_typeSucces(typeSucces),
_valider(false),
_id(idSucces),
_informationSucces(reformerPhraseColle(info.first), GraphicDispatcher::getFont(4), 30),
_nombreRequis("Requis: "+std::to_string(info.second), GraphicDispatcher::getFont(4), 30),
_etatSucces("Pas accompli", GraphicDispatcher::getFont(4), 30)
{
}

Succes::~Succes()
{
    
}

void Succes::construireCadreSucces(sf::Vector2f position)
{
    //Construction du cadre
    _cadre.setSize(sf::Vector2f(500, 150));
    _cadre.setPosition(position);
    _cadre.setFillColor(sf::Color::Black);
    _cadre.setOutlineColor(sf::Color::White);
    _cadre.setOutlineThickness(2.0);
    
    //Construction de la validation
    _etatValidation.setSize(sf::Vector2f(32,32));
    _etatValidation.setOutlineColor(sf::Color::White);
    _etatValidation.setOutlineThickness(2.0);
    _etatValidation.setPosition((_cadre.getPosition().x + _cadre.getSize().x) - 50, _cadre.getPosition().y + 75);
    
    //Construction de l'icone
    _icone.setSize(sf::Vector2f(32,32));
    attribuerIcone();
    _icone.setOutlineColor(sf::Color::White);
    _icone.setOutlineThickness(2.0);
    _icone.setPosition(_cadre.getPosition().x + 10, _cadre.getPosition().y + 10);
    
    _informationSucces.setPosition(_cadre.getPosition().x + 60, _cadre.getPosition().y + 20);
    _nombreRequis.setPosition(_informationSucces.getPosition().x,
                            _informationSucces.getPosition().y   + _informationSucces.getGlobalBounds().height + 10);
    _etatSucces.setPosition(_informationSucces.getPosition().x,
                            _nombreRequis.getPosition().y  + _nombreRequis.getGlobalBounds().height + 10);
}

std::string Succes::getNomSucces()const
{
    return _information.first;
}

int Succes::getScoreSucces()const
{
    return _information.second;
}

void Succes::attribuerIcone()
{
    if(_typeSucces == "score")
        _icone.setTexture(&GraphicDispatcher::getIconeTexture(0));
    else if(_typeSucces == "pacgomme")
        _icone.setTexture(&GraphicDispatcher::getIconeTexture(1));
    else if(_typeSucces == "fruit")
        _icone.setTexture(&GraphicDispatcher::getIconeTexture(2));
    else if(_typeSucces == "lotr")
        _icone.setTexture(&GraphicDispatcher::getIconeTexture(3));
    else if(_typeSucces == "pacman")
        _icone.setTexture(&GraphicDispatcher::getIconeTexture(4));
    else if(_typeSucces == "vieGarde")
        _icone.setTexture(&GraphicDispatcher::getIconeTexture(5));
    else if(_typeSucces == "viePerdue")
        _icone.setTexture(&GraphicDispatcher::getIconeTexture(6));
    else if(_typeSucces == "fantome")
        _icone.setTexture(&GraphicDispatcher::getIconeTexture(7));
    
}

void Succes::deverouillerSucces()
{
    _valider = true;
}

void Succes::update(sf::Time &delta)
{
    if(_valider)
    {
        _etatSucces.setString("Accompli");
    }
}

void Succes::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_cadre);
    renderer.draw(_icone);
    renderer.draw(_informationSucces);
    renderer.draw(_nombreRequis);
    if(_valider)
    {
        _etatSucces.setString("Accompli");
        _etatValidation.setTexture(&GraphicDispatcher::getIconeTexture(8));
    }
    else
    {
        _etatValidation.setTexture(&GraphicDispatcher::getIconeTexture(9));
    }
    
    renderer.draw(_etatSucces);
    renderer.draw(_etatValidation);
}

bool Succes::getEtat()const
{
    return _valider;
}
