//
//  MenuConnexion.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 28/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__MenuConnexion__
#define __ProjetPacman__MenuConnexion__

#include <SFML/Graphics.hpp>
#include <vector>

#include "OutilsMenu.h"
#include "GestionnaireConnexion.h"
#include "Informateur.h"

class MenuConnexion
{
    
private:
    
    enum class Focus
    {
        BarrePseudo = 0,
        CreerCompte = 1,
        Connexion = 2,
        Quitter = 3
        
    };
    
    enum class EtatBulleInformation
    {
        Activer,
        Desactiver
    };
    
    GestionnaireConnexion   _connexionVerificateur;
    sf::RectangleShape      _fond;
    std::vector<sf::Text>   _listeTexte;
    Focus                   _focus;
    bool                    _retournerEtat;
    
    ZoneATexte              _zoneTexte;
    sf::Vector2f            _taillePlateau;
    
    Informateur             _informateurEtatConnexion;
    sf::CircleShape         _bulleInformation;
    EtatBulleInformation    _etatBulle;
    
    void placerTexte();
    void construireZoneTexte();
    
public:
    
    MenuConnexion(sf::Vector2f taillePlateau, std::string theme);
    ~MenuConnexion();
    
    
    bool seConnecter();
    bool creerCompte();
    
    std::string getBouttonAppuyer()const;
    std::string getPseudoJoueur()const;
    
    void desactiverEntree();
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
};

#endif /* defined(__ProjetPacman__MenuConnexion__) */
