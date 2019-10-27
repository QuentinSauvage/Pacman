//
//  GestionnairePartie.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 22/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__GestionnairePartie__
#define __ProjetPacman__GestionnairePartie__

#include "Partie.h"
#include "Temps.h"
#include "MenuEntrePlateau.h"
#include "ListeSucces.h"
#include "Joueur.h"

class GestionnairePartie
{
private:
    
    std::unique_ptr<Partie>             _partie;
    int                                 _niveauActuel;
    sf::Vector2f                        _positionPlateau;
    sf::Vector2f                        _taillePlateau;
    bool                                _quitterJeu;
    bool                                _partieCompleteGagne;
    std::string                         _difficulte;
    
    int                                 _sauvegardeVie;
    int                                 _sauvegardeScore;
    Temps                               _sauvegardeTemps;
    std::unique_ptr<MenuEntrePlateau>   _entrePartie;
    Joueur&                             _joueur;
    
public:
    
    GestionnairePartie(sf::Vector2f taillePlateau, std::string theme,std::string difficulte, Joueur& joueur, int niveau);
    GestionnairePartie(const GestionnairePartie& gP) = delete;
    ~GestionnairePartie();
    
    bool getPartieCompleteGagne()const;
    bool getQuitterPartie()const;
    bool retournerMenuPrincipal()const;
    bool partiePerdu()const;
    bool enPause()const;
    bool entrePartieActive()const;
    
    void passerNiveauSuivant();
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    
    GestionnairePartie operator=(const GestionnairePartie& gP) = delete;
};

#endif /* defined(__ProjetPacman__GestionnairePartie__) */
