//
//  Informateur.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 07/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Informateur.h"

Informateur::Informateur(sf::Vector2f positionHautGauche):
_posX(positionHautGauche.x),
_posY(positionHautGauche.y),
_valeurEspacement(10),
_voirInformateur(true),
_idInfo(0)
{
    //+ 20 Pour aéré par rapport au plateau.
    _posXSuivant = _posX + 70;
    _posYSuivant = _posY + 20;
}

Informateur::Informateur(sf::Vector2f positionHautGauche, sf::Vector2f espacement, int interligne, bool autoriserCadre):
_posX(positionHautGauche.x),
_posY(positionHautGauche.y),
_valeurEspacement(interligne),
_cadreAutorise(autoriserCadre),
_cadre(nullptr),
_idInfo(0)
{
    _posXSuivant = _posX + espacement.x;
    _posYSuivant = _posY + 33 + espacement.y;
}

Informateur::~Informateur()
{
    
}

void Informateur::desactiverInformateur()
{
    _voirInformateur = false;
}

void Informateur::activerInformateur()
{
    _voirInformateur = true;
}

void Informateur::update(sf::Time& delta)
{
    if(_cadreAutorise)
    {
        if(_listeTexte.size() == 0)
        {
            _cadre = std::make_unique<sf::RectangleShape>(sf::Vector2f(0,0));
            _cadre->setPosition(_posX, _posY);
        }
        else
        {
            int nbLigne = _listeTexte.size();
            int tailleX = 250;
            int tailleY = 320;
            //int tailleY = (_listeTexte[0].getCharacterSize() * _listeTexte.size()) + ((_listeTexte.size() - 1) * _valeurEspacement);
            _cadre = std::make_unique<sf::RectangleShape>(sf::Vector2f(tailleX, tailleY));
            _cadre->setPosition(sf::Vector2f(_posX, _posY));
            _cadre->setTexture(&GraphicDispatcher::getFondLotr("parchemin.png"));
            //il faudra charger une texture de background en type parchemin par exemple
            
        }
    }
}

void Informateur::draw(sf::RenderWindow& renderer)
{
    if(_voirInformateur)
    {
        if(_cadre != nullptr)
            renderer.draw(*_cadre);
        for(int i = 0; i < _listeTexte.size(); ++i)
        {
            renderer.draw(_listeTexte[i]);
        }
    }
}

/**
 * La structure de l'informateur est comme ceci:
 * 0 = Score
 * 1 = Vie
 * ...
 * ...
 */
void Informateur::initialiserInformation(std::string info)
{
    _listeTexte.push_back(sf::Text(info, GraphicDispatcher::getFont(0), 40));
    _listeTexte[_idInfo].setPosition(_posXSuivant, _posYSuivant);
    _posYSuivant += _listeTexte[_idInfo].getGlobalBounds().height + _valeurEspacement;
    _idInfo++;
}

void Informateur::initialiserInformation(std::string info, int tailleFont)
{
    _listeTexte.push_back(sf::Text(info, GraphicDispatcher::getFont(0), tailleFont));
    _listeTexte[_idInfo].setPosition(_posXSuivant, _posYSuivant);
    _posYSuivant += _listeTexte[_idInfo].getGlobalBounds().height + _valeurEspacement;
    _idInfo++;
}

//Pour modifier le score, c'est l'indice 0
void Informateur::modifierScore(std::string score)
{
    _listeTexte[0].setString(score);
}

//Pour modifier la vie, c'est l'indice 1
void Informateur::modifierVie(std::string vie)
{
    _listeTexte[1].setString(vie);
}

//Pour modifier le temps, c'est l'indice 2
void Informateur::modifierTemps(std::string temps)
{
    _listeTexte[2].setString(temps);
}
