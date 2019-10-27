//
//  MenuOption.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 09/06/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "MenuOption.h"
#include "GraphicDispatcher.h"
#include "GestionnaireSon.h"
#include "OutilsDivers.h"

#include <fstream>
#include <iostream>

MenuOption::MenuOption(sf::Vector2f taillePlateau):
_taillePlateau(taillePlateau),
_titreTexte("Options", GraphicDispatcher::getFont(4), 120),
_barreVolume(sf::Vector2f(150,300)),
_modeTourni(sf::Vector2f(150,450) ,"Mode hardcore"),
_boutonDifficulte(sf::Vector2f(800, 400)),
_activerSonFond(sf::Vector2f(800,550), "Musique de fond"),
_texteSauvegarde("Appliquer", GraphicDispatcher::getFont(4), 50),
_texteRevenirMenu("Revenir au menu", GraphicDispatcher::getFont(4), 50),
_retournerEtat(false),
_focus(Focus::Aucun)
{
    int positionXOccupe = (_taillePlateau.x - _titreTexte.getGlobalBounds().width)/2;
    _titreTexte.setPosition(positionXOccupe, 0);
    _texteSauvegarde.setPosition(150, 650);
    _texteRevenirMenu.setPosition(900, 650);
    
    chargerOption();
}

MenuOption::~MenuOption()
{
    
}

void MenuOption::chargerOption()
{
    std::ifstream flux("option/option.txt");
    if(flux)
    {
        std::string recuperateur;
        while(std::getline(flux, recuperateur))
        {
            if(decouperPhrase(recuperateur, 0) == "hardcore")
            {
                if(decouperPhrase(recuperateur, 2) == "oui")
                    _modeTourni.setEstCoche(true);
                else
                    _modeTourni.setEstCoche(false);
            }
            else if(decouperPhrase(recuperateur, 0) == "volume")
            {
                _barreVolume.setVolume(decouperPhrase(recuperateur, 2));
            }
            else if(decouperPhrase(recuperateur, 0) == "difficulte")
            {
                _boutonDifficulte.setDifficulte(decouperPhrase(recuperateur, 2));
            }
            else if(decouperPhrase(recuperateur, 0) == "musiqueFond")
            {
                if(decouperPhrase(recuperateur, 2) == "oui")
                    _activerSonFond.setEstCoche(true);
                else
                    _activerSonFond.setEstCoche(false);
            }
        }
    }
    else
    {
        throw "Erreur d'ouverture du fichier option";
    }
}

void MenuOption::reinitialiserEntree()
{
    _retournerEtat = false;
}

std::string MenuOption::retournerReponse()const
{
    if(_retournerEtat)
    {
        if(_focus == Focus::RevenirMenu)
            return "retournerMenu";
        else if(_focus == Focus::Appliquer)
            return "appliquer";
    }
    else
    {
        return "nonDefini";
    }
}

void MenuOption::sauvegarderOptions()
{
    std::ofstream flux("option/option.txt", std::ios::trunc);
    if(flux)
    {
        if(_modeTourni.estCoche())
            flux << "hardcore = oui\n";
        else
            flux << "hardcore = non\n";
        
        flux << "volume = " <<_barreVolume.getVolume()<<"\n";
        flux << "difficulte = "<<_boutonDifficulte.getDifficulte()<<"\n";
        
        if(_activerSonFond.estCoche())
            flux << "musiqueFond = oui";
        else
            flux << "musiqueFond = non";
    }
    else
    {
        throw("Probleme d'ouverture fichier sauvegarde");
    }
}

void MenuOption::processEvent(sf::Event& evt)
{
    _barreVolume.processEvent(evt);
    _modeTourni.processEvent(evt);
    _activerSonFond.processEvent(evt);
    _boutonDifficulte.processEvent(evt);
    
    //Evenement souris
    if(evt.type == sf::Event::MouseButtonPressed)
    {
        if(_texteSauvegarde.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
        {
            GestionnaireSon::jouer("changementFocus.wav");
            _focus = Focus::Appliquer;
        }
        else if(_texteRevenirMenu.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
        {
            GestionnaireSon::jouer("changementFocus.wav");
            _focus = Focus::RevenirMenu;
        }
    }
    
    //Evenement clavier
    if(evt.type == sf::Event::KeyPressed)
    {
        if(evt.key.code == sf::Keyboard::Return)
        {
            _retournerEtat = true;
        }
    }
}

void MenuOption::update(sf::Time& delta)
{
    switch(_focus)
    {
        case(Focus::Appliquer):
        {
            _texteSauvegarde.setColor(sf::Color::Yellow);
            _texteRevenirMenu.setColor(sf::Color::White);
            break;
        }
        case(Focus::RevenirMenu):
        {
            _texteSauvegarde.setColor(sf::Color::White);
            _texteRevenirMenu.setColor(sf::Color::Yellow);
            break;
        }
    }
    _barreVolume.update(delta);
    _modeTourni.update(delta);
    _activerSonFond.update(delta);
    _boutonDifficulte.update(delta);
}
void MenuOption::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_titreTexte);
    renderer.draw(_texteSauvegarde);
    renderer.draw(_texteRevenirMenu);
    _barreVolume.draw(renderer);
    _modeTourni.draw(renderer);
    _activerSonFond.draw(renderer);
    _boutonDifficulte.draw(renderer);
}