//
//  Map.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 05/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Map.h"
#include <iostream>

Map::Map(int level, sf::Vector2f position):
_nbLigne(24),
_nbColonne(24),
_levelMap(level),
_width(24),
_ableGrid(true),
_posX(position.x),
_posY(position.y),
_tailleXMap(_nbColonne * 32),
_tailleYMap(_nbLigne * 32)
{
    loadMapInfo();
    buildMapGraphique();
    buildGrille();
}

Map::~Map()
{
    
}

/**
 * La fonction charge la partie logique de la carte
 * C'est à dire le type de la case (mur, rien, etc..), sa position et sa taille
 * La fonction va chercher les informations dans le fichier texte
 * Et envoie à chaque case son type.
 */

void Map::loadMapInfo()
{
    std::string nomFichier = "Map/level"+std::to_string(_levelMap)+".txt";
    std::ifstream fichier(nomFichier);
    
    if(fichier)
    {
        int getNombre;
    
        int startX = _posX;
        int startY = _posY;
        
        int posX = startX;
        int posY = startY;
        sf::Vector2f sizeCase = sf::Vector2f(32,32);
        for(int i = 0; i < _nbLigne; i++)
        {
            for(int j = 0; j < _nbColonne; j++)
            {
                fichier >> getNombre;
                sf::Vector2f posCase = sf::Vector2f(posX, posY);
                //Ici, on va initialiser de base les cases avec une pacgomme
                //On va donc leur donner l'identifiant 4 pour avoir la texture avec un pacgomme
                //C'est ensuite au cours du jeu qu'on repassera l'identifiant à 1 si on a mangé la pacgomme
                
                if(getNombre == 0)
                    getNombre += 4;
                if(getNombre == 5)
                    getNombre = 0;
                if(getNombre == 6)
                    getNombre = 5;
                
                //Si c'est une case ou l'on peut marcher, alors c'est que l'on peut manger les pacgommes.
                if(getNombre == 4)
                    _map.push_back( Case(getNombre, sizeCase, posCase, true) );
                else if(getNombre == 5)
                    _map.push_back(Case(getNombre, sizeCase, posCase, true));
                else
                    _map.push_back( Case(getNombre, sizeCase, posCase, false) );
                
                posX += 32;
            }
            posX = startX;
            posY += 32;
        }
    }
    else
    {
        std::cout<<"Probleme d'ouverture de la map"<<std::endl;
    }
}

void Map::buildGrille()
{
    _grille.setPrimitiveType(sf::Lines);
    _grille.resize((_nbLigne + 1 + _nbColonne + 1)*2);
    
    // Creation des lignes horizontales
    int constantXBegin = _posX;
    int constantXEnd = _posX + _tailleXMap;
    
    int variableYBegin = 0;
    int variableYEnd = 0;
    
    for(int i = 0; i < (_nbColonne+1)*2; i++)
    {
        if(i%2 == 0)
        {
            _grille[i].position = sf::Vector2f(constantXBegin,variableYBegin);
            _grille[i].color = sf::Color::White;
            variableYBegin += 32;
        }
        else
        {
            _grille[i].position = sf::Vector2f(constantXEnd, variableYEnd);
            _grille[i].color = sf::Color::White;
            variableYEnd += 32;
        }
    }
    
    //Creation des lignes verticales
    int constantYBegin = _posY;
    int constantYEnd = _posY + _tailleYMap;
    int variableXBegin = _posX;
    int variableXEnd = _posX;
    
    for(int i = (_nbColonne+1)*2; i < (_nbColonne+1 + _nbLigne+1)*2; i++)
    {
        if(i%2 == 0)
        {
            sf::Vector2f la = sf::Vector2f(variableXBegin,constantYBegin);
            _grille[i].position = la;
            _grille[i].color = sf::Color::White;
            variableXBegin += 32;
        }
        else
        {
            _grille[i].position = sf::Vector2f(variableXEnd, constantYEnd);
            _grille[i].color = sf::Color::White;
            variableXEnd += 32;
        }
    }
}


void Map::buildMapGraphique()
{    
    _mapVertices.setPrimitiveType(sf::Quads);
    _mapVertices.resize(_nbColonne * _nbLigne * 4);
    
    int sizeCase = 32;
    for(int i = 0; i < _nbLigne; i++)
    {
        for(int j = 0; j < _nbColonne; j++)
        {
            //int indexCase = i+j*_width;
            //sf::Vertex* quad = &_mapVertices[(i+j*_width)* 4];
            int indexCase = i*_width+j;
            sf::Vertex* quad = &_mapVertices[(i*_width+j)* 4];
            
            quad[0].position = sf::Vector2f(_map[indexCase].getPosition().x , _map[indexCase].getPosition().y);
            quad[1].position = sf::Vector2f(_map[indexCase].getPosition().x + sizeCase , _map[indexCase].getPosition().y);
            quad[2].position = sf::Vector2f(_map[indexCase].getPosition().x + sizeCase, _map[indexCase].getPosition().y + sizeCase);
            quad[3].position = sf::Vector2f(_map[indexCase].getPosition().x , _map[indexCase].getPosition().y + sizeCase);
            
            quad[0].texCoords = sf::Vector2f(_map[indexCase].getType() * sizeCase, 0);
            quad[1].texCoords = sf::Vector2f(_map[indexCase].getType() * sizeCase + sizeCase, 0);
            quad[2].texCoords = sf::Vector2f(_map[indexCase].getType() * sizeCase + sizeCase, sizeCase);
            quad[3].texCoords = sf::Vector2f(_map[indexCase].getType() * sizeCase, sizeCase);
            
        }
    }
}

Case& Map::getCase(int index)
{
    return _map[index];
}

int Map::getSize()const
{
    return _map.size();
}

void Map::draw(sf::RenderWindow& renderer)
{
    buildMapGraphique();
    renderer.draw(_mapVertices, &GraphicDispatcher::getEntireMapTexture());
    //renderer.draw(_grille);
}

