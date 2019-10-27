//
//  Pacman.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 30/04/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Pacman.h"
#include <iostream>

Pacman::Pacman(sf::Vector2f positionDepart, sf::Vector2f positionPlateau):
_positionPlateau(positionPlateau),
_vieMax(3),
_vieActuel(_vieMax),
_etat(Etat::Arret),
_direction(Direction::Aucune),
_vitesse(2),
_sprite(GraphicDispatcher::getTexturePacman(0)),
_typeMouvement(TypeMouvement::BoucheFerme),
_tempsRafraichissement(0.15),
_rafraichissementSprite()
{
    _sprite.setPosition(positionDepart);
    _positionColonne = 1;
    _positionLigne = 1;
    _positionMatriciel = _positionLigne * 24 + _positionColonne;
}

Pacman::~Pacman()
{
    
}

void Pacman::setPosition(sf::Vector2f newPos)
{
    _sprite.setPosition(newPos);
}

sf::Vector2f Pacman::getPosition()const
{
    return _sprite.getPosition();
}

const sf::Sprite& Pacman::getSprite()const
{
    return _sprite;
}

int Pacman::getVitesse()const
{
    return _vitesse;
}

int Pacman::getLigne()const
{
    return _positionLigne;
}

int Pacman::getColonne()const
{
    return _positionColonne;
}

int Pacman::getPositionMatrice()const
{
    return _positionMatriciel;
}

int Pacman::getVie()const
{
    return _vieActuel;
}

void Pacman::setVie(int vie)
{
    _vieActuel = vie;
}

char Pacman::getDirection()const
{
    switch(_direction)
    {
        case(Direction::Haut):
        {
            return 'z';
            break;
        }
        case(Direction::Bas):
        {
            return 's';
            break;
        }
        case(Direction::Gauche):
        {
            return 'q';
            break;
        }
        case(Direction::Droite):
        {
            return 'd';
            break;
        }
        case(Direction::Aucune):
        {
            return 'a';
            break;
        }
    }
}

void Pacman::setVitesse(float vitesse)
{
    _vitesse = vitesse;
}

bool Pacman::enVie()const
{
    return _vieActuel > 0;
}

void Pacman::perdreVie()
{
    _vieActuel--;
    if(_vieActuel < 0)
        _vieActuel = 0;
}


void Pacman::processEvent(char direction)
{
    switch (direction)
    {
        case 'z':
        {
            _direction = Direction::Haut;
            _etat = Etat::EnMouvement;
            break;
        }
        case 's':
        {
            _direction = Direction::Bas;
            _etat = Etat::EnMouvement;
            break;
        }
        case 'q':
        {
            _direction = Direction::Gauche;
            _etat = Etat::EnMouvement;
            break;
        }
        case 'd':
        {
            _direction = Direction::Droite;
            _etat = Etat::EnMouvement;
            break;
        }
        case 'a': // Pour signifier "a"ucun déplacement
        {
            _direction = Direction::Aucune;
            _etat = Etat::Arret;
        }
    }
}

void Pacman::setPositionMatriciel(int newPos)
{
    _positionMatriciel = newPos;
}

void Pacman::draw(sf::RenderTarget& renderer)
{
    renderer.draw(_sprite);
}

void Pacman::update(sf::Time& delta)
{
    _rafraichissementSprite.update();
    switch (_etat)
    {
        case (Etat::Arret):
        {
            break;
        }
        case (Etat::EnMouvement):
        {
            switch (_direction)
            {
                case (Direction::Haut):
                {
                    //Partie Graphique
                    if(_typeMouvement == TypeMouvement::BoucheFerme && _rafraichissementSprite.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementSprite.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheOuverte;
                        _sprite.setTexture(GraphicDispatcher::getTexturePacman(7));
                    }
                    else if (_typeMouvement == TypeMouvement::BoucheOuverte && _rafraichissementSprite.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementSprite.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheFerme;
                        _sprite.setTexture(GraphicDispatcher::getTexturePacman(6));
                    }
                    
                    _sprite.move(0, - _vitesse);
                    
                    //Partie logique
                    _positionColonne = (_sprite.getPosition().x - _positionPlateau.x)/32;
                    _positionLigne = (_sprite.getPosition().y / 32);
                    _positionMatriciel = _positionLigne * 24 + _positionColonne;
                    break;
                }
                case (Direction::Bas):
                {
                    //Partie graphique
                    if(_typeMouvement == TypeMouvement::BoucheFerme && _rafraichissementSprite.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementSprite.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheOuverte;
                        _sprite.setTexture(GraphicDispatcher::getTexturePacman(3));
                    }
                    else if (_typeMouvement == TypeMouvement::BoucheOuverte && _rafraichissementSprite.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementSprite.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheFerme;
                        _sprite.setTexture(GraphicDispatcher::getTexturePacman(2));
                    }

                    _sprite.move(0, _vitesse);
                    
                    //Partie logique
                    _positionColonne = (_sprite.getPosition().x - _positionPlateau.x)/32;
                    _positionLigne = _sprite.getPosition().y / 32;
                    _positionMatriciel = _positionLigne * 24 + _positionColonne;

                    break;
                }
                case (Direction::Gauche):
                {
                    //Partie graphique
                    if(_typeMouvement == TypeMouvement::BoucheFerme && _rafraichissementSprite.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementSprite.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheOuverte;
                        _sprite.setTexture(GraphicDispatcher::getTexturePacman(5));
                    }
                    else if (_typeMouvement == TypeMouvement::BoucheOuverte && _rafraichissementSprite.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementSprite.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheFerme;
                        _sprite.setTexture(GraphicDispatcher::getTexturePacman(4));
                    }
                    
                    _sprite.move(- _vitesse, 0);
                    
                    //Partie logique
                    _positionColonne = ((_sprite.getPosition().x - _positionPlateau.x)/32);
                    _positionLigne = _sprite.getPosition().y / 32;
                    _positionMatriciel = _positionLigne * 24 + _positionColonne;
                    
                    break;
                }
                case (Direction::Droite):
                {
                    //Partie graphique
                    if(_typeMouvement == TypeMouvement::BoucheFerme && _rafraichissementSprite.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementSprite.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheOuverte;
                        _sprite.setTexture(GraphicDispatcher::getTexturePacman(1));
                    }
                    else if (_typeMouvement == TypeMouvement::BoucheOuverte && _rafraichissementSprite.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementSprite.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheFerme;
                        _sprite.setTexture(GraphicDispatcher::getTexturePacman(0));
                    }
                    _sprite.move(_vitesse, 0);
                    
                    _positionColonne = (_sprite.getPosition().x - _positionPlateau.x)/32;
                    _positionLigne = _sprite.getPosition().y / 32;
                    _positionMatriciel = _positionLigne * 24 + _positionColonne;

                    break;
                }
                default:
                {
                    std::cout<<"Nothing"<<std::endl;
                    break;
                }
            }
        }
    }
}



