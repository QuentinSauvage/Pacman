//
//  Vue.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 24/04/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Vue.h"
#include <iostream>

Vue::Vue(int xCenter, int yCenter, int xSize, int ySize):
_vue(sf::Vector2f(xCenter, yCenter), sf::Vector2f(xSize, ySize)),
_zoomValue(1.0)
{
    _vue.zoom(_zoomValue);
}

Vue::Vue(const sf::View vue):
_zoomValue(1.0),
_vue(vue),
_vueParDefaut(vue)
{
    _vue = vue;
    _vue.zoom(_zoomValue);
}

Vue::~Vue()
{
    
}

//Fonction pour bouger la camera tout en s'assurant que celle ci n'aille pas n'importe ou
void Vue::move(int y, int minY, int maxY)
{
    if(y > 0)
    {
        if(_vue.getCenter().y + (_vue.getSize().y/2) < maxY)
            _vue.move(0,y);
    }
    else
    {
        if(_vue.getCenter().y - (_vue.getSize().y/2) > minY)
            _vue.move(0,y);
    }
}

void Vue::setRotation(float degres)
{
    _vue.setRotation(degres);
}

int Vue::getRotation()const
{
    return _vue.getRotation();
}

void Vue::rotate(float degres)
{
    _vue.rotate(degres);
}

void Vue::setVueParDefaut()
{
    _vue = _vueParDefaut;
}

sf::View Vue::getVue()const
{
    return _vue;
}

sf::Vector2f Vue::getCenter()const
{
    return _vue.getCenter();
}

sf::Vector2f Vue::setCenter(sf::Vector2f position)
{
    _vue.setCenter(sf::Vector2f(position));
}

void Vue::setZoom(float ratio)
{
    _zoomValue += ratio;
    _vue.zoom(_zoomValue);
}

float Vue::getZoom()const
{
    return _zoomValue;
}