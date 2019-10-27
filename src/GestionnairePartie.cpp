//
//  GestionnairePartie.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 22/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "GestionnairePartie.h"

GestionnairePartie::GestionnairePartie(sf::Vector2f taillePlateau, std::string theme, std::string difficulte, Joueur& joueur, int niveau):
_joueur(joueur),
_difficulte(difficulte),
_partie(nullptr),
_niveauActuel(niveau),
_positionPlateau(taillePlateau),
_taillePlateau(taillePlateau),
_quitterJeu(false),
_entrePartie(nullptr),
_partieCompleteGagne(false)
{
    _partie = std::make_unique<Partie>(taillePlateau, niveau, _difficulte, joueur);

    if(theme == "themePacman")
    {
        _joueur.updateIncrementPoint("nbThemePacmanJouer", 1);
        if(_joueur.recupererScore("nbThemePacmanJouer") >= _joueur.getListeSucces().getValeurSucces("AmateurDeTradition"))
        {
            _joueur.validerSucces(12);
        }
        if(_joueur.recupererScore("nbThemePacmanJouer") >= _joueur.getListeSucces().getValeurSucces("NomPasTrouvePacman"))
        {
            _joueur.validerSucces(13);
        }
        if(_joueur.recupererScore("nbThemePacmanJouer") >= _joueur.getListeSucces().getValeurSucces("FerventDefenseurDesTraditions"))
        {
            _joueur.validerSucces(14);
        }
    }
    else
    {
        _joueur.updateIncrementPoint("nbThemeLotrJouer", 1);
        if(_joueur.recupererScore("nbThemeLotrJouer") >= _joueur.getListeSucces().getValeurSucces("AmateurDeLotr"))
        {
            _joueur.validerSucces(9);
        }
        if(_joueur.recupererScore("nbThemeLotrJouer") >= _joueur.getListeSucces().getValeurSucces("nomPasTrouveLotr"))
        {
            _joueur.validerSucces(10);
        }
        if(_joueur.recupererScore("nbThemeLotrJouer") >= _joueur.getListeSucces().getValeurSucces("FerventDefenseurDeLotr"))
        {
            _joueur.validerSucces(11);
        }
    }
}

GestionnairePartie::~GestionnairePartie()
{
    
}

bool GestionnairePartie::getPartieCompleteGagne()const
{
    return _partieCompleteGagne;
}

bool GestionnairePartie::retournerMenuPrincipal()const
{
    if(_partie != nullptr)
    {
        return _partie->retournerMenuPrincipal();
    }
}

bool GestionnairePartie::getQuitterPartie()const
{
    return _quitterJeu;
}

bool GestionnairePartie::partiePerdu()const
{
    if(_partie != nullptr)
        return _partie->getPartiePerdu();
    else
        return false;
}

bool GestionnairePartie::entrePartieActive()const
{
    if(_entrePartie != nullptr)
        return true;
        
    return false;
}

void GestionnairePartie::passerNiveauSuivant()
{    
    //Apparition du fond pour indiquer le niveau suivant
    _entrePartie = nullptr;
    _partie = std::make_unique<Partie>(_taillePlateau, ++_niveauActuel, _difficulte, _joueur);
    _partie->setScore(_sauvegardeScore);
    _partie->setTemps(_sauvegardeTemps);
    _partie->setViePacman(_sauvegardeVie);
}

void GestionnairePartie::processEvent(sf::Event& evt)
{
    //....//
    if(_partie != nullptr)
        _partie->processEvent(evt);
}

bool GestionnairePartie::enPause()const
{
    if(_partie != nullptr)
        return _partie->getPartieEnPause();
}

void GestionnairePartie::update(sf::Time &delta)
{
    if(_partie != nullptr)
    {
        _partie->update(delta);
        _quitterJeu = _partie->getQuitterPartie();
        
        if(_partie->getPartieGagne())
        {
            if(_niveauActuel == 5)
            {
                //On a termine la partie complete
                _joueur.updateIncrementPoint("vieGarde", _partie->getViePacman());
                
                if(_joueur.recupererScore("vieGarde") >= _joueur.getListeSucces().getValeurSucces("Defenseur"))
                {
                    _joueur.validerSucces(15);
                }
                if(_joueur.recupererScore("vieGarde") >= _joueur.getListeSucces().getValeurSucces("Protecteur"))
                {
                    _joueur.validerSucces(16);
                }
                if(_joueur.recupererScore("vieGarde") >= _joueur.getListeSucces().getValeurSucces("Gardien"))
                {
                    _joueur.validerSucces(17);
                }
                
                _partieCompleteGagne = true;
            }
            else
            {
                //On sauvegarde les données de la partie pour pouvoir continuer à avoir le score et le temps et on supprime le plateau du niveau inferieur
                _sauvegardeVie   = _partie->getViePacman();
                _sauvegardeScore = _partie->getScore();
                _sauvegardeTemps = _partie->getTemps();
                _partie = nullptr;
                //On va afficher pendant 2 secondes que l'on passe au niveau suivant
                _entrePartie = std::make_unique<MenuEntrePlateau>(_taillePlateau, "Niveau "+std::to_string(_niveauActuel+1));
            }
        }
    }

    if(_entrePartie != nullptr)
    {
        _entrePartie->update(delta);
    }
    
    if(_entrePartie != nullptr && _entrePartie->getTemps().getTempsSecondes() > 4)
    {
        passerNiveauSuivant();
    }
}

void GestionnairePartie::draw(sf::RenderWindow &renderer)
{
    if(_partie != nullptr)
        _partie->draw(renderer);
    if(_entrePartie != nullptr)
        _entrePartie->draw(renderer);
}
