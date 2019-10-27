//
//  MenuStatistiques.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 05/06/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "MenuStatistiques.h"
#include "GraphicDispatcher.h"
#include "OutilsDivers.h"
#include <fstream>
#include <iostream>


MenuStatistiques::MenuStatistiques(sf::Vector2f taillePlateau, Joueur& joueur):
_joueur(joueur),
_taillePlateau(taillePlateau),
_titre("Statistiques", GraphicDispatcher::getFont(4), 120),
_texteRevenirMenu("Revenir menu", GraphicDispatcher::getFont(4), 50),
_fond(taillePlateau),
_revenirMenu(false),
_focus(Focus::Aucun),
_etatScroll(Scroll::Aucun)
{
    _fond.setPosition(0,0);
    _fond.setFillColor(sf::Color::Black);
    //Initialisation des textes
    _titre.setPosition((_taillePlateau.x - _titre.getGlobalBounds().width)/2, 0);
    _texteRevenirMenu.setPosition(_titre.getPosition().x + _titre.getGlobalBounds().width + 120 , 300);
    std::ifstream statsJoueur("Joueur/"+_joueur.getPseudo()+".txt");
    std::string recuperateur;
    if(statsJoueur)
    {
        while(std::getline(statsJoueur,recuperateur))
        {
            if(!(decouperPhrase(recuperateur, 0) == "Succes"))
                _statistiques.push_back(sf::Text(reformerPhraseColle(recuperateur),GraphicDispatcher::getFont(4),30));
        }
    }
    else
        throw("Erreur d'ouverture");
    
    placerStatistiques();
}

MenuStatistiques::~MenuStatistiques()
{
    
}

int MenuStatistiques::getNombreSucces()const
{
    return ListeSucces::getNombreSucces();
}

std::string MenuStatistiques::getBouttonAppuyer()const
{
    if(_revenirMenu)
    {
        return "revenirMenu";
    }
    else
    {
        return "nonDefini";
    }
}

std::string MenuStatistiques::getEtatScroll()const
{
    switch (_etatScroll)
    {
        case (Scroll::Haut):
        {
            return "haut";
            break;
        }
        case (Scroll::Bas):
        {
            return "bas";
            break;
        }
        case (Scroll::Aucun):
        {
            return "aucun";
            break;
        }
    }
}

void MenuStatistiques::placerStatistiques()
{
    int positionY = 200;
    for(int i = 0; i < _statistiques.size(); i++)
    {
        _statistiques[i].setPosition((_taillePlateau.x - _statistiques[i].getGlobalBounds().width)/2, positionY);
        positionY += 30;
    }
}

void MenuStatistiques::processEvent(sf::Event& evt)
{
    //Evenement clavier
    if(evt.type == sf::Event::KeyPressed)
    {
        if(evt.key.code == sf::Keyboard::Escape)
        {
            _revenirMenu = true;
            _focus = Focus::revenirMenu;
        }
        if(evt.key.code == sf::Keyboard::Return && _focus == Focus::revenirMenu)
        {
            _revenirMenu = true;
        }
    }
    
    //Evenement souris
    if(evt.type == sf::Event::MouseButtonPressed)
    {
        if(_texteRevenirMenu.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
            _focus = Focus::revenirMenu;
    }
    if(evt.type == sf::Event::MouseWheelMoved)
    {
        if(evt.mouseWheel.delta > 0)
        {
            //Il faut faire bouger la camero vers le haut si on est pas déjà tout en haut
            _etatScroll = Scroll::Haut;
        }
        else if(evt.mouseWheel.delta < 0)
        {
            //il faut faire bouger la camera vers le bas si on est pas déjà tout en bas
            _etatScroll = Scroll::Bas;
        }
        else
        {
            _etatScroll = Scroll::Aucun;
        }
    }
}

void MenuStatistiques::update(sf::Time& delta)
{
    switch (_focus)
    {
        case (Focus::revenirMenu):
        {
            _texteRevenirMenu.setColor(sf::Color::Yellow);
            break;
        }
    }
    _joueur.updateSucces(delta);
}

void MenuStatistiques::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_fond);
    renderer.draw(_titre);
    renderer.draw(_texteRevenirMenu);
    for(auto i : _statistiques)
        renderer.draw(i);
    _joueur.drawSucces(renderer);
}