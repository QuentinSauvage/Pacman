//
//  Succes.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 25/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Succes__
#define __ProjetPacman__Succes__

#include <iostream>
#include <SFML/Graphics.hpp>

class Succes
{
    
private:
    
    std::pair<std::string, int> _information;
    std::string                 _typeSucces;
    int                         _id;
    bool                        _valider;
    
    sf::RectangleShape          _cadre;
    sf::RectangleShape          _icone;
    sf::RectangleShape          _etatValidation;
    sf::Text                    _informationSucces;
    sf::Text                    _nombreRequis;
    sf::Text                    _etatSucces;
    
    
    void attribuerIcone();
    
public:
    
    Succes(std::pair<std::string, int> information, std::string typeSucces, int idSucces);
    ~Succes();
    
    void deverouillerSucces();
    
    std::string getNomSucces()const;
    int getScoreSucces()const;
    void construireCadreSucces(sf::Vector2f position);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    bool getEtat()const;
    
};

#endif /* defined(__ProjetPacman__Succes__) */
