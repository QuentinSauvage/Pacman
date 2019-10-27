//
//  OutilsMenu.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 28/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "OutilsMenu.h"
#include <iostream>
#include "GraphicDispatcher.h"

ZoneATexte::ZoneATexte(sf::Vector2f taillePlateau):
_zone(),
_nbLettreMax(15),
_texte("", GraphicDispatcher::getFont(4)),
_horlogeRafraichissement(),
_barreClignotante("/", GraphicDispatcher::getFont(0), 60),
_haveFocus(true)
{
    _barreClignotante.setStyle(sf::Text::Bold);
    
    _texte.setCharacterSize(40);
    _zone.setSize(sf::Vector2f(450, _texte.getCharacterSize() + 50));
    
    int xOccupe = (taillePlateau.x - _zone.getSize().x) / 2;
    
    _zone.setPosition(sf::Vector2f(xOccupe, 300));
    _texte.setPosition(xOccupe + 15, 315);
    _zone.setTexture(&GraphicDispatcher::getFondLotr("textbox.png"));
    
}

ZoneATexte::~ZoneATexte()
{
    
}

void ZoneATexte::gagnerFocus()
{
    _haveFocus = true;
}

void ZoneATexte::perdreFocus()
{
    _haveFocus = false;
}

std::string ZoneATexte::getTexte()const
{
    return static_cast<std::string>(_texte.getString());
}

void ZoneATexte::ajouterLettreTexte(char caractere)
{
    if(_texte.getString().getSize() < _nbLettreMax)
    {
        _texte.setString(_texte.getString()+caractere);
    }
    else
    {}
}

bool ZoneATexte::contains(int posXSouris, int posYSouris)const
{
    return _zone.getGlobalBounds().contains(posXSouris, posYSouris);
}

void ZoneATexte::supprimerLettre()
{
    if(_texte.getString().getSize() == 0)
    {}
    else
    {
        sf::String nouvelleChaine = _texte.getString();
        nouvelleChaine.erase(nouvelleChaine.getSize()-1);
        _texte.setString(nouvelleChaine);
    }
}

void ZoneATexte::draw(sf::RenderWindow& renderer)
{
    _horlogeRafraichissement.update();
    
    renderer.draw(_zone);
    renderer.draw(_texte);
    
    if(_haveFocus)
    {
        _barreClignotante.setPosition(_texte.getPosition().x + _texte.getGlobalBounds().width + 10, 300);
        if(_horlogeRafraichissement.getTempsReel().asSeconds() > 0.4)
        {
            _horlogeRafraichissement.redemarrer();
        }
        else
        {
            renderer.draw(_barreClignotante);
        }
    }
}

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

BarreValeurVariable::BarreValeurVariable(sf::Vector2f position):
_volumeEffectif("100%", GraphicDispatcher::getFont(4), 50),
_nomBarre("Volume", GraphicDispatcher::getFont(4), 50),
_barreComplete(sf::Vector2f(300,50)),
_barreVariable(sf::Vector2f(300, 50))
{
    _barreComplete.setPosition(position);
    _barreVariable.setPosition(position.x, position.y);
    
    _barreVariable.setFillColor(sf::Color::Yellow);
    
    
    _volumeEffectif.setPosition(position.x + _barreComplete.getGlobalBounds().width + 10, position.y);
}

BarreValeurVariable::~BarreValeurVariable()
{
    
}

void BarreValeurVariable::setVolume(std::string volume)
{
    _volume = volume;
    _barreVariable.setSize(sf::Vector2f(std::stoi(_volume)*3, 50));
}

std::string BarreValeurVariable::getVolume()const
{
    return _volume;
}

void BarreValeurVariable::processEvent(sf::Event& evt)
{
    if(evt.type == sf::Event::MouseButtonPressed)
    {
        if(_barreComplete.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
        {
            _barreVariable.setSize(sf::Vector2f(evt.mouseButton.x - _barreComplete.getPosition().x, 50));
        }
    }
}

void BarreValeurVariable::update(sf::Time& delta)
{
    int tailleBarreComplete = _barreComplete.getGlobalBounds().width;
    int tailleBarreVariable = _barreVariable.getGlobalBounds().width;
    int volume = ((tailleBarreVariable/3) - (tailleBarreComplete/3))+100;
    _volume = std::to_string(volume);
    _volumeEffectif.setString(_volume+"%");
}

void BarreValeurVariable::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_barreComplete);
    renderer.draw(_barreVariable);
    renderer.draw(_volumeEffectif);
}

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

CheckBox::CheckBox(sf::Vector2f position, std::string texte):
_boite(sf::Vector2f(32,32)),
_boiteCoche(nullptr),
_texte(texte, GraphicDispatcher::getFont(4), 32)
{
    _texte.setPosition(position);
    _boite.setPosition(position.x + _texte.getGlobalBounds().width + 20, position.y);
    _boite.setFillColor(sf::Color::Black);
    _boite.setOutlineColor(sf::Color::White);
    _boite.setOutlineThickness(3.0);
}

CheckBox::~CheckBox()
{
    
}

void CheckBox::setEstCoche(bool valeur)
{
    if(valeur)
    {
        _boiteCoche = std::make_unique<sf::RectangleShape>(sf::Vector2f(16,16));
        _boiteCoche->setPosition(_boite.getPosition().x + 8, _boite.getPosition().y + 8);
    }
    else
    {
        if(_boiteCoche != nullptr)
            _boiteCoche = nullptr;
    }
}

void CheckBox::processEvent(sf::Event& evt)
{
    if(evt.type == sf::Event::MouseButtonPressed)
    {
        if(_boite.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
        {
            if(_boiteCoche == nullptr)
            {
                _boiteCoche = std::make_unique<sf::RectangleShape>(sf::Vector2f(16,16));
                _boiteCoche->setPosition(_boite.getPosition().x + 8, _boite.getPosition().y + 8);
            }
            else
                _boiteCoche = nullptr;
                
        }
    }
}

bool CheckBox::estCoche()const
{
    return _boiteCoche!=nullptr;
}

void CheckBox::update(sf::Time& delta)
{
    
}

void CheckBox::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_boite);
    if(_boiteCoche!=nullptr)
        renderer.draw(*_boiteCoche);

    renderer.draw(_texte);
    
}

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

BoutonChoixDifficulte::BoutonChoixDifficulte(sf::Vector2f position):
_difficulte("intermediaire"),
_texteExterieur("Difficulte: ", GraphicDispatcher::getFont(4), 30),
_texteInterieur("<    "+_difficulte+"    >", GraphicDispatcher::getFont(4), 30),
_cadre(sf::Vector2f(_texteInterieur.getGlobalBounds().width, _texteInterieur.getGlobalBounds().height + 20))
{
    _texteExterieur.setPosition(position);
    _cadre.setPosition(_texteExterieur.getPosition().x + _texteExterieur.getGlobalBounds().width + 10, position.y);
    _texteInterieur.setPosition(_cadre.getPosition());
    
    _cadre.setFillColor(sf::Color::Black);
    _cadre.setOutlineColor(sf::Color::White);
    _cadre.setOutlineThickness(2.0);
    
}

BoutonChoixDifficulte::~BoutonChoixDifficulte()
{
    
}

void BoutonChoixDifficulte::setDifficulte(std::string difficulte)
{
    _difficulte = difficulte;
}

std::string BoutonChoixDifficulte::getDifficulte()const
{
    return _difficulte;
}

void BoutonChoixDifficulte::processEvent(sf::Event& evt)
{
    if(evt.type == sf::Event::MouseButtonPressed)
    {
        if(_cadre.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
        {
            if(evt.mouseButton.x < (_cadre.getPosition().x + (_cadre.getGlobalBounds().width)/2))
            {
                if(_difficulte == "facile")
                    _difficulte = "asynchrone";
                else if(_difficulte == "intermediaire")
                    _difficulte = "facile";
                else if(_difficulte == "difficile")
                    _difficulte = "intermediaire";
                else
                    _difficulte = "difficile";
            }
            else
            {
                if(_difficulte == "facile")
                    _difficulte = "intermediaire";
                else if(_difficulte == "intermediaire")
                    _difficulte = "difficile";
                else if(_difficulte == "difficile")
                    _difficulte = "asynchrone";
                else
                    _difficulte = "facile";
            }
        }
    }
}

void BoutonChoixDifficulte::update(sf::Time& delta)
{
    _texteInterieur.setString("<   "+_difficulte+"   >");
    
    int tailleTexte = _texteInterieur.getGlobalBounds().width;
    int tailleCadre = _cadre.getGlobalBounds().width;
    int positionX = (tailleCadre - tailleTexte)/2;
                    
    _texteInterieur.setPosition(positionX + _cadre.getPosition().x, _cadre.getPosition().y);
}

void BoutonChoixDifficulte::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_cadre);
    renderer.draw(_texteInterieur);
    renderer.draw(_texteExterieur);
}
