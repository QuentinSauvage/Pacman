//
//  Application.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 24/04/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Application__
#define __ProjetPacman__Application__

#include <SFML/Graphics.hpp>
#include "GestionnaireCollision.h"
#include "GestionnaireMenu.h"
#include "Vue.h"

class Application
{
private:
    
    int                     _width;
    int                     _height;
    sf::RenderWindow        _window;
    Vue                     _vue;

    GestionnaireMenu        _gestionnaireMenu;
    
public:
    
    Application();
    Application(const Application& app) = delete;
    ~Application();
    
    void processEvent();
    void draw();
    void update();
    
    sf::Vector2f getCoordonneeSourisExacte();

    Application operator=(const Application& app) = delete;
    
};

#endif /* defined(__ProjetPacman__Application__) */
