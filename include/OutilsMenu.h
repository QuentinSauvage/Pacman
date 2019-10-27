//
//  OutilsMenu.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 28/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__OutilsMenu__
#define __ProjetPacman__OutilsMenu__

#include <SFML/Graphics.hpp>
#include "GraphicDispatcher.h"
#include "Temps.h"

class ZoneATexte
{
    
private:
    
    sf::Text            _texte;
    sf::RectangleShape  _zone;
    int                 _nbLettreMax;
    
    //Va servir pour affichier/desafficher le petit clignotement pour voir que l'on peut taper son pseudo
    Temps               _horlogeRafraichissement;
    sf::Text            _barreClignotante;
    bool                _haveFocus;
    
public:
    
    ZoneATexte(sf::Vector2f taillePlateau);
    ~ZoneATexte();
    
    std::string getTexte()const;
    
    void gagnerFocus();
    void perdreFocus();
    
    void ajouterLettreTexte(char caractere);
    void supprimerLettre();
    bool contains(int posXSouris, int posYSouris)const;
    
    void draw(sf::RenderWindow& renderer);
    
    
};

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

class BarreValeurVariable
{
    
private:
    
    sf::RectangleShape  _barreComplete;
    sf::RectangleShape  _barreVariable;
    sf::Text            _nomBarre;
    sf::Text            _volumeEffectif;
    std::string         _volume;
    
public:
    
    BarreValeurVariable(sf::Vector2f position);
    ~BarreValeurVariable();
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    
    std::string getVolume()const;
    void setVolume(std::string volume);
    
    
};

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

class CheckBox
{
    
private:
    
    sf::RectangleShape                  _boite;
    std::unique_ptr<sf::RectangleShape> _boiteCoche;
    sf::Text                            _texte;
    
public:
    
    CheckBox(sf::Vector2f position, std::string texte);
    ~CheckBox();
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);
    
    void setEstCoche(bool valeur);
    
    bool estCoche()const;
    
};

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

class BoutonChoixDifficulte
{
    
private:
    
    std::string         _difficulte;
    sf::Text            _texteExterieur;
    sf::Text            _texteInterieur;
    
    sf::RectangleShape  _cadre;
    
   
public:
    
    BoutonChoixDifficulte(sf::Vector2f position);
    ~BoutonChoixDifficulte();
    
    std::string getDifficulte()const;
    void setDifficulte(std::string difficulte);
    
    void processEvent(sf::Event& evt);
    void update(sf::Time& delta);
    void draw(sf::RenderWindow& renderer);

};

#endif /* defined(__ProjetPacman__OutilsMenu__) */
