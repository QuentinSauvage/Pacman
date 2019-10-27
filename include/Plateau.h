//
//  Plateau.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 03/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Plateau__
#define __ProjetPacman__Plateau__

#include <SFML/Graphics.hpp>
#include "GestionnaireSon.h"
#include "Pacman.h"
#include "Fantome.h"
#include "Map.h"
#include "Fruit.h"
#include "Temps.h"
#include "Joueur.h"
#include <vector>

/**
 * Cette classe va contenir le pacman, les fantomes
 * La carte et le quadrillage
 * Elle représente une des scénes du jeu final.
 */

class Plateau
{
private:
    
    enum class DeplacementEnCours
    {
        Haut,
        Bas,
        Gauche,
        Droite,
        Aucun
    };
    
    //Debuggeur           _debuggeur;
    std::vector<Fantome>            _lesFantomes;
    std::vector<DeplacementEnCours> _deplacementFantome;
    std::vector<DeplacementEnCours> _deplacementSecondaireFantome;
    
    
    Joueur&                         _joueur;
    Pacman                          _pacman;
    Map                             _map;
    sf::Vector2f                    _positionPlateau;
    std::unique_ptr<Fruit>          _fruit;
    std::string                     _difficulte;
 
    int                             _niveau;
    int                             _score;
    int                             _pacgommeMange;
    int                             _nbFantomeKillParPacgomme;
    
    //Superpacgomme evenement
    bool                            _superPacmanActive;
    std::unique_ptr<Temps>          _tempsSuperPacman;
    
    bool                            _dejaChoisitTest;
    bool                            _autoriseSaisieDeplacement;
    bool                            _pause;
    bool                            _vie10000donnee;
    bool                            _vie20000donnee;
    
    DeplacementEnCours              _deplacementPacman;
    char                            _directionSuivante;
    
    void gestionFantomes(sf::Time& delta);
    void gestionPacman(sf::Time& delta);
    
public:
    
    Plateau(sf::Vector2f position, int niveau, std::string difficulte, Joueur& joueur);
    Plateau(const Plateau& plt) = delete;
    ~Plateau();
    
    
    void draw(sf::RenderWindow& renderer);
    void update(sf::Time& delta);
    void processEvent(const sf::Event& evt);
    bool deplacementPacman(sf::Time& delta, char direction);
    bool deplacementFantome(sf::Time& delta, char direction, Fantome& fantome);
    void mangerFruit(int position);
    void reinitialiserPositionPacman();
    void reinitialiserPositionFantome();
    void reinitialiserPositionFantome(int indexFantome);
    void choisirDirectionSecondaireFantome(int idFantome);
    
    void mettrePause();
    void stopperPause();
    
    void genererFruit();
    void supprimerFruit();
    
    bool fruitPresent()const;
    int  getNbPacgommeMange()const;
    int  getScore()const;
    void setScore(int score);
    int  getViePacman()const;
    void setViePacman(int vie);
    
    bool toutLesPacGommeMange();
    
    Plateau operator=(const Plateau& app) = delete;
    
};

#endif /* defined(__ProjetPacman__Plateau__) */
