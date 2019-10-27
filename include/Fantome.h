//
//  Fantome.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 17/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Fantome__
#define __ProjetPacman__Fantome__

#include <SFML/Graphics.hpp>
#include "GraphicDispatcher.h"
#include "Temps.h"
#include "Pacman.h"

class Fantome
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
        Bas,
        Gauche,
        Droite,
        Aucune
    };
    
    enum class TypeMouvement
    {
        BoucheOuverte,
        BoucheFerme
    };
    
    enum class TypemouvementPeur
    {
        FormeBleu,
        FormeBlanche
    };
    
    int                 _id;
    int                 _positionLigne;
    int                 _positionColonne;
    int                 _positionMatriciel;
    bool                _enVie;
    bool                _sortieCage;
    float               _vitesse;
    sf::Vector2f        _positionPlateau;
    float               _tempsRafraichissement;
    
    Etat                _etat;
    Direction           _direction;
    Direction           _directionSecondaire;
    TypeMouvement       _typeMouvement;
    TypemouvementPeur   _typeMouvementPeur;
    char                _directionPrincipalPrivilegie;
    char                _directionSecondairePrivilegie;
    
    std::string         _difficulte;
    bool                _faible;
    bool                _invulnerabiliteFaiblesse; //Si ils ont déjà été mangé
    
    sf::Sprite          _sprite;
    Temps               _rafraichissementDirection;
    Temps               _rafraichissementMouvement;
    Temps*               _rafraichissementMouvementPeur;
    
    //IA _IA;
    
public:
    
    Fantome(sf::Vector2f positionDepart, sf::Vector2f positionPlateau, int idFantome, std::string difficulte);
    //Fantome(const Fantome& fantome) = delete;
    ~Fantome();
    
    void jouer();
    char choisirDirection();
    char choisirDirectionForce();
    void draw(sf::RenderWindow& renderer);
    void processEvent(char direction);
    void update(sf::Time& delta);
    void updateTime();
    
    void reinitialiserSortie();
    void orienterDeplacement();
    void analyserPositionPacman(const Pacman& pacman);
    void analyserPositionMatriciel(int directionMatriciel);
    
    int  analyserDistancePacman(const Pacman& pacman);
    char directionPrincipaleAppeure(const Pacman& pacman);
    char directionSecondaireAppeure(const Pacman& pacman);
    char directionPrincipalSortirSpawn();
    char directionSecondaireSortirSpawn();
    char seDirigerVersPositionPrincipal(int directionMatriciel);
    char seDirigerVersPositionSecondaire(int directionMatriciel);
    char seDirigerAleatoirement();
    
    char directionInky(const Pacman& pacman);
    char directionClynde(const Pacman& pacman);
    char directionPinky(const Pacman& pacman);
    char directionBlinky(const Pacman& pacman);
    
    bool estSorti()const;
    bool estFaible()const;
    
    void devenirFaible();
    void devenirInvulnerable();
    void enleverInvulnerabilite();
    void redevenirNormal();
    
    void arreterDeplacement();
    void setPositionMatriciel(int position);
    void setPosition(sf::Vector2f position);
    
    sf::Vector2f getPosition()const;
    int getPositionMatriciel()const;
    char getDirection()const;
    char getDirectionSecondaire()const;
    int getVitesse()const;
    const sf::Sprite& getSprite()const;
    
    Fantome operator=(const Fantome& fantome) = delete;
};


#endif /* defined(__ProjetPacman__Fantome__) */
