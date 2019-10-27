//
//  Vue.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 24/04/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Vue__
#define __ProjetPacman__Vue__


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Vue
{
private:
    
    sf::View        _vue;
    float           _zoomValue;
    sf::View        _vueParDefaut;
    
public:

    Vue(int xCenter, int yCenter, int xSize, int ySize);
    Vue(const sf::View vue);
    //Vue(const Vue& vue) = delete;
    ~Vue();
    
    sf::View        getVue()const;
    sf::Vector2f    getCenter()const;
    sf::Vector2f    setCenter(sf::Vector2f position);
    void            setZoom(float ratio);
    float           getZoom()const;
    void            rotate(float degres);
    
    void            setRotation(float degres);
    int             getRotation()const;
    void            setVueParDefaut();
    
    void            move(int y, int minY, int maxY);
    
    Vue operator=(const Vue& vue) = delete;
    
    
};

#endif /* defined(__ProjetPacman__Vue__) */
