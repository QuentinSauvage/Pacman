//
//  MenuOption.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 09/06/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__MenuOption__
#define __ProjetPacman__MenuOption__

#include <SFML/Graphics.hpp>
#include "OutilsMenu.h"

class MenuOption
{
  
private:
    
    enum class Focus
    {
        Appliquer,
        RevenirMenu,
        Aucun
    };
    
    sf::Vector2f            _taillePlateau;
    sf::Text                _titreTexte;
    sf::Text                _texteSauvegarde;
    sf::Text                _texteRevenirMenu;
    
    bool                    _retournerEtat;
    Focus                   _focus;
    
    BarreValeurVariable     _barreVolume;
    CheckBox                _modeTourni;
    CheckBox                _activerSonFond;
    BoutonChoixDifficulte   _boutonDifficulte;
    
public:
    
    MenuOption(sf::Vector2f taillePlateau);
    ~MenuOption();
    
    std::string retournerReponse()const;
    
    void chargerOption();
    void sauvegarderOptions();
    void reinitialiserEntree();
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    
};

#endif /* defined(__ProjetPacman__MenuOption__) */
