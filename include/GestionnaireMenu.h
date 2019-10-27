//
//  GestionnaireMenu.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 28/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__GestionnaireMenu__
#define __ProjetPacman__GestionnaireMenu__

#include "GestionnaireMenu.h"
#include "MenuPrincipal.h"
#include "MenuChoixTheme.h"
#include "MenuConnexion.h"
#include "MenuStatistiques.h"
#include "MenuOption.h"
#include "GestionnairePartie.h"
#include "MenuVictoire.h"
#include "GameOver.h"
#include "Joueur.h"
#include "Vue.h"
#include "Temps.h"
#include <SFML/Graphics.hpp>


class GestionnaireMenu
{
    
private:
    
    //Les differentes fenetres
    std::unique_ptr<MenuChoixTheme>     _choixTheme;
    std::unique_ptr<MenuConnexion>      _connexion;
    std::unique_ptr<MenuPrincipal>      _menuPrincipal;
    std::unique_ptr<MenuOption>         _option;
    std::unique_ptr<MenuStatistiques>   _statistiques;
    std::unique_ptr<GestionnairePartie> _gestionnairePartie;
    std::unique_ptr<GameOver>           _gameOver;
    std::unique_ptr<MenuVictoire>       _menuVictoire;
    
    std::unique_ptr<Joueur>             _joueur;
    
    
    std::unique_ptr<Temps>              _horlogeGetReady;
    
    bool                                _quitterJeu;
    
    //Caracteristiques necessaire à l'application
    std::string                         _pseudoJoueur;
    std::string                         _theme;
    sf::Vector2f                        _taillePlateau;
    
    std::string                         _difficulte;
    std::string                         _volume;
    bool                                _modeHardcore;
    bool                                _musiqueFond;
    
    
    //reference sur la vue de l'application pour différente utilisation
    Vue&                                 _vueFenetre;
    
public:
    
    GestionnaireMenu(sf::Vector2f taillePlateau, Vue& vue);
    ~GestionnaireMenu();
    
    bool quitterPartie();
    
    sf::Vector2f getMouvementCamera()const;
    
    void chargerOption();
    
    void evenementTheme();
    void evenementConnexion();
    void evenementPrincipal();
    void evenementStatistiques();
    void evenementOption();
    void evenementPlateau();
    void evenementGameOver();
    void evenementVictoire();
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    
    
};

#endif /* defined(__ProjetPacman__GestionnaireMenu__) */
