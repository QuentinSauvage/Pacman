//
//  Informateur.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 07/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Informateur__
#define __ProjetPacman__Informateur__

#include <SFML/Graphics.hpp>
#include <vector>

#include "GraphicDispatcher.h"

class Informateur
{
    
private:
    
    std::vector<sf::Text>               _listeTexte;
    int                                 _posX;
    int                                 _posY;
    int                                 _posXSuivant;
    int                                 _posYSuivant;
    int                                 _idInfo;
    int                                 _valeurEspacement;
    
    bool                                _voirInformateur;
    bool                                _cadreAutorise;
    std::unique_ptr<sf::RectangleShape> _cadre;
    
public:
    
    Informateur(sf::Vector2f positionHautGauche);
    Informateur(sf::Vector2f positionHautGauche, sf::Vector2f espacement, int interligne, bool autoriserCadre);
    ~Informateur();
    
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    void initialiserInformation(std::string info);
    void initialiserInformation(std::string info, int tailleFont);
    
    void desactiverInformateur();
    void activerInformateur();
    
    void modifierScore(std::string score);
    void modifierVie(std::string vie);
    void modifierTemps(std::string temps);
};

#endif /* defined(__ProjetPacman__Informateur__) */
