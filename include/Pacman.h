//
//  Pacman.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 30/04/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Pacman__
#define __ProjetPacman__Pacman__

#include <SFML/Graphics.hpp>
#include "GraphicDispatcher.h"
#include "GestionnaireCollision.h"
#include "Temps.h"

class Pacman
{
    
private:
    
    enum class Etat
    {
        EnMouvement,
        Arret
    };
    
    enum class Direction
    {
        Haut,
        Gauche,
        Droite,
        Bas,
        Aucune
    };
    
    enum class TypeMouvement
    {
        BoucheOuverte,
        BoucheFerme
    };
    
    int                 _positionLigne;
    int                 _positionColonne;
    int                 _positionMatriciel;
    int                 _vieMax;
    int                 _vieActuel;
    float               _vitesse;
    sf::Vector2f        _positionPlateau;
    
    Etat                _etat;
    Direction           _direction;
    TypeMouvement       _typeMouvement;
    
    Temps               _rafraichissementSprite;
    float               _tempsRafraichissement;
    
    sf::Sprite         _sprite;
    
public:
    
    Pacman(sf::Vector2f positionDepart, sf::Vector2f positionPlateau); //envoie position pour faire le delta de la position
    Pacman(Pacman& pacman) = delete;
    ~Pacman();
    
    void processEvent(char direction);

    const sf::Sprite&   getSprite()const;
    int                 getPositionMatrice()const; // la fonction renvoie l'index dans le tableau 1D
    sf::Vector2f        getPosition()const;
    int                 getVitesse()const;
    char                getDirection()const;
    int                 getVie()const;
    bool                enVie()const;
    int                 getLigne()const;
    int                 getColonne()const;
    
    void                setPosition(sf::Vector2f newPos);
    void                setPositionMatriciel(int newPos);
    void                setVitesse(float vitesse);
    void                setVie(int vie);
    
    void                perdreVie();

    
    void draw(sf::RenderTarget& renderer);
    void update(sf::Time& delta);
    
    
    Pacman operator=(Pacman& pacman) = delete;
};

#endif /* defined(__ProjetPacman__Pacman__) */
