//
//  Partie.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 07/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Partie.h"

Partie::Partie(sf::Vector2f tailleFenetre, int niveauPartie,std::string difficulte, Joueur& joueur):
_tailleFenetre(tailleFenetre),
_taillePlateau(sf::Vector2f((32 * 24),(32*24))),  //24 tiles de 32 pixels
_positionPlateau(sf::Vector2f((tailleFenetre.x - _taillePlateau.x)/2, (tailleFenetre.y - _taillePlateau.y)/2)), //Centre au milieu
_plateau(sf::Vector2f(_positionPlateau.x,_positionPlateau.y), niveauPartie, difficulte, joueur),
_informateur(sf::Vector2f(_positionPlateau.x + _taillePlateau.x, 30)),
_pause(nullptr),
_perdu(false),
_gagne(false),
_retournerMenuPrincipal(false),
_quitterPartie(false),
_premierFruitSortie(false),
_deuxiemeFruitSortie(false),
_joueur(joueur),
_temps(),
_apparitionFruit(nullptr)
{
    _informateur.initialiserInformation("Score : \n"+ std::to_string(_plateau.getScore()));
    _informateur.initialiserInformation("Vie : "+std::to_string(_plateau.getViePacman()));
    _informateur.initialiserInformation("Temps Ecoule : \n"+std::to_string(0));
}

Partie::~Partie()
{
    
}

int Partie::getViePacman()const
{
    _plateau.getViePacman();
}

void Partie::setViePacman(int vie)
{
    _plateau.setViePacman(vie);
}

bool Partie::getQuitterPartie()const
{
    return _quitterPartie;
}

bool Partie::getPartieGagne()const
{
    if(_gagne)
    {
        return true;
    }
    else
        return false;
}

bool Partie::getPartiePerdu()const
{
    return _perdu;
}

bool Partie::retournerMenuPrincipal()const
{
    return _retournerMenuPrincipal;
}

int  Partie::getScore()const
{
    _plateau.getScore();
}

void Partie::setScore(int score)
{
    _plateau.setScore(score);
}

Temps Partie::getTemps()const
{
    return _temps;
}
void Partie::setTemps(Temps& temps)
{
    _temps = temps;
}



void Partie::evenementPause()
{
    if(_pause != nullptr)
    {
        std::string reponse = _pause->getBoutonAppuyer();
        if(reponse == "reprendre")
        {
            _pause = nullptr;
            _temps.reprendre();
            if(_apparitionFruit != nullptr)
            {
                _apparitionFruit->reprendre();
            }
            _plateau.stopperPause();
        }
        else if(reponse == "menuPrincipal")
        {
            _retournerMenuPrincipal = true;
        }
        else if(reponse == "quitter")
        {
            _quitterPartie = true;
        }
    }

}

void Partie::processEvent(sf::Event& evt)
{
    if(evt.type == sf::Event::KeyPressed)
    {
        if(evt.key.code == sf::Keyboard::Escape)
        {
            if(_pause == nullptr)
            {
                _temps.pause();
                if(_apparitionFruit != nullptr)
                    _apparitionFruit->pause();
                _pause = std::make_unique<Pause>(_tailleFenetre);
                _plateau.mettrePause();
            }
            else
            {
                _pause = nullptr;
                _temps.reprendre();
                if(_apparitionFruit != nullptr)
                    _apparitionFruit->reprendre();
                _plateau.stopperPause();
            }
        }
    }
    
    if(_pause != nullptr)
        _pause->processEvent(evt);
    
    if(_pause == nullptr && !_perdu)
    {
        _plateau.processEvent(evt);
    }
}

bool Partie::getPartieEnPause()const
{
    if(_pause != nullptr)
        return true;
    
    return false;
}

void Partie::update(sf::Time& delta)
{
    _gagne = _plateau.toutLesPacGommeMange();
    _perdu = _plateau.getViePacman() <= 0;
    
    if(_pause != nullptr)
        _pause->update();
    
    this->evenementPause();
    
    if(_perdu)
    {
        _informateur.modifierVie("Vie : "+std::to_string(_plateau.getViePacman()));
    }

    
    if(_pause == nullptr && !_perdu)
    {
        _temps.update();
        _informateur.modifierScore("Score : \n"+ std::to_string(_plateau.getScore()));
        _informateur.modifierVie("Vie : "+std::to_string(_plateau.getViePacman()));
        _informateur.modifierTemps("Temps ecoule: \n"+ std::to_string(_temps.getTempsSecondes()));
        _plateau.update(delta);
        
        if(_plateau.getNbPacgommeMange() == 75 && !_plateau.fruitPresent() && !_premierFruitSortie)
        {
            _plateau.genererFruit();
            _apparitionFruit = std::make_unique<Temps>();
            _premierFruitSortie = true;
        }
        
        if(_plateau.getNbPacgommeMange() == 150 && !_plateau.fruitPresent() && !_deuxiemeFruitSortie)
        {
            _plateau.genererFruit();
            _apparitionFruit = std::make_unique<Temps>();
            _deuxiemeFruitSortie = true;
        }
        
        if(_apparitionFruit != nullptr)
        {
            _apparitionFruit->update();
            if(_apparitionFruit->getTempsSecondes() > 8)
            {
                _plateau.supprimerFruit();
                _apparitionFruit = nullptr;
            }
        }
    }
}

void Partie::draw(sf::RenderWindow& renderer)
{

    if(_pause == nullptr)
    {
        _plateau.draw(renderer);
        _informateur.draw(renderer);
    }
    else
    {
        _pause->draw(renderer);
    }
}