//
//  Partie.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 07/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Partie__
#define __ProjetPacman__Partie__

#include "Pause.h"
#include "Plateau.h"
#include "Joueur.h"
#include "Informateur.h"
#include "Temps.h"

#include <SFML/Graphics.hpp>

class Partie
{
    
private:
    
    sf::Vector2f            _taillePlateau;
    sf::Vector2f            _positionPlateau;
    sf::Vector2f            _tailleFenetre;
    std::string             _theme;
    Plateau                 _plateau;
    Informateur             _informateur;
    Temps                   _temps;
    bool                    _perdu;
    bool                    _gagne;
    bool                    _quitterPartie;
    bool                    _retournerMenuPrincipal;
    bool                    _premierFruitSortie;
    bool                    _deuxiemeFruitSortie;
    
    std::unique_ptr<Temps>  _apparitionFruit;
    std::unique_ptr<Pause>  _pause;

    Joueur&                  _joueur;
    
public:
    
    Partie(sf::Vector2f tailleFenetre, int niveauPartie, std::string difficulte, Joueur& joueur);
    Partie(Partie& partie) = delete;
    ~Partie();
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    
    int  getScore()const;
    void setScore(int score);
    int getViePacman()const;
    void setViePacman(int vie);
    
    Temps getTemps()const;
    void  setTemps(Temps& temps);
    
    bool getQuitterPartie()const;
    bool getPartieGagne()const;
    bool getPartiePerdu()const;
    bool getPartieEnPause()const;
    bool retournerMenuPrincipal()const;
    
    void evenementPause();
    
    Partie operator=(Partie& partie) = delete;
    
};

#endif /* defined(__ProjetPacman__Partie__) */
