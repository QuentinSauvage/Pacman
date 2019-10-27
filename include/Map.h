//
//  Map.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 05/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Map__
#define __ProjetPacman__Map__

#include "Case.h"
#include "GraphicDispatcher.h"
#include "Debuggeur.h"
#include <fstream>
#include <vector>

class Map
{
    
private:
    
    //Partie logique de la carte (invisible)
    std::vector<Case>   _map;
    bool                _ableGrid;
    
    int                 _nbLigne;
    int                 _nbColonne;
    int                 _width;
    int                 _posX;
    int                 _posY;
    int                 _tailleXMap;
    int                 _tailleYMap;    
    int                 _levelMap;
    
    //Partie Graphique
    sf::VertexArray     _mapVertices;
    sf::VertexArray     _grille;
    
    void buildMapGraphique();
    void buildGrille();
    void loadMapInfo();
    
public:
    
    Map(int level, sf::Vector2f position);
    Map(Map& map) = delete;
    ~Map();
    
    void draw(sf::RenderWindow& renderer);
    Case& getCase(int index);
    int getSize()const;
    
    Map operator= (Map& map) = delete;
    
    
};

#endif /* defined(__ProjetPacman__Map__) */
