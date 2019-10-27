//
//  MenuConnexion.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 28/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "MenuConnexion.h"
#include "GraphicDispatcher.h"
#include "OutilsDivers.h"
#include "GestionnaireSon.h"

MenuConnexion::MenuConnexion(sf::Vector2f taillePlateau, std::string theme):
_fond(taillePlateau),
_taillePlateau(taillePlateau),
_zoneTexte(taillePlateau),
_focus(Focus::BarrePseudo),
_retournerEtat(false),
_connexionVerificateur(),
_informateurEtatConnexion(sf::Vector2f(970,300), sf::Vector2f(20,2), 5, true),
_bulleInformation(10, 50),
_etatBulle(EtatBulleInformation::Activer)
{
    if(theme == "themePacman")
        _fond.setTexture(&GraphicDispatcher::getFondPacman("fond"+std::to_string(getRandom(1, 4))+".png"));
    else
        _fond.setTexture(&GraphicDispatcher::getFondLotr("fond"+std::to_string(getRandom(1, 4))+".png"));
    
    _listeTexte.push_back(sf::Text("Menu de connexion", GraphicDispatcher::getFont(0), 140));
    _listeTexte.push_back(sf::Text("Creer", GraphicDispatcher::getFont(0), 70));
    _listeTexte.push_back(sf::Text("Connexion", GraphicDispatcher::getFont(0), 70));
    _listeTexte.push_back(sf::Text("Quitter", GraphicDispatcher::getFont(0), 70));
    
    _bulleInformation.setPosition(935, 300);
    _bulleInformation.setFillColor(sf::Color(156,105,39));
    _bulleInformation.setOutlineColor(sf::Color::Black);
    _bulleInformation.setOutlineThickness(2.0);
    
    _informateurEtatConnexion.initialiserInformation("Bienvenue sur le jeu\nrentrez votre pseudo\nattention respectez\nla case.\nSi vous n'avez pas de\ncompte rentrez\nvotre pseudo et\nappuyez sur creer.\nVous pouvez ensuite\nvous connecter",  23);
    
    placerTexte();
    
}

MenuConnexion::~MenuConnexion()
{
    
}

std::string MenuConnexion::getPseudoJoueur()const
{
    return _zoneTexte.getTexte();
}

std::string MenuConnexion::getBouttonAppuyer()const
{
    if(_retournerEtat)
    {
        switch(_focus)
        {
            case(Focus::BarrePseudo):
            {
                return "seConnecter";
                break;
            }
            case(Focus::CreerCompte):
            {
                return "creerCompte";
                break;
            }
            case(Focus::Connexion):
            {
                return "seConnecter";
                break;
            }
            case(Focus::Quitter):
            {
                return "Quitter";
                break;
            }
        }
    }
    else
    {
        return "PasDefini";
    }
}

bool MenuConnexion::seConnecter()
{
    if(_connexionVerificateur.seConnecter(_zoneTexte.getTexte()))
    {
        return true;
    }
    else
    {
        _informateurEtatConnexion.modifierScore("Impossible de se\nconnecter.Verifier \nvotre pseudo en \nrespectant la case\nou creez vous un\ncompte.");
        _etatBulle = EtatBulleInformation::Activer;
        return false;
    }
}

bool MenuConnexion::creerCompte()
{
    if(_connexionVerificateur.creerCompte(_zoneTexte.getTexte()))
    {
        _informateurEtatConnexion.modifierScore("Creation du compte\nreussie,vous pouvez\nvous connecter.");
        _etatBulle = EtatBulleInformation::Activer;
        return true;
    }
    else
    {
        _informateurEtatConnexion.modifierScore("Impossible de creer le\ncompte, le pseudo\nest deja pris ou nul.\nReesayer");
        _etatBulle = EtatBulleInformation::Activer;
        return false;
    }
}

void MenuConnexion::desactiverEntree()
{
    _retournerEtat = false;
}

void MenuConnexion::placerTexte()
{
    int positionXTitre = (_taillePlateau.x - _listeTexte[0].getGlobalBounds().width ) / 2;
    int positionY = 0;
    
    _listeTexte[0].setPosition(positionXTitre, positionY);

    int espacementTexte = 200;
    int posXOccupe =    _listeTexte[1].getGlobalBounds().width +
                        _listeTexte[2].getGlobalBounds().width +
                        _listeTexte[3].getGlobalBounds().width +
                        espacementTexte + espacementTexte;
    
    int xTexte1 = (_taillePlateau.x - posXOccupe ) / 2;
    _listeTexte[1].setPosition(xTexte1,620);
    int xTexte2 = xTexte1 + _listeTexte[1].getGlobalBounds().width+espacementTexte;
    _listeTexte[2].setPosition(xTexte2, 620);
    int xTexte3 = xTexte2 + _listeTexte[2].getGlobalBounds().width+ espacementTexte;
    _listeTexte[3].setPosition(xTexte3,620);
}

void MenuConnexion::processEvent(sf::Event& evt)
{
    //Evenement clavier
    if(evt.type == sf::Event::KeyPressed)
    {
        if(evt.key.code == sf::Keyboard::Return)
        {
            _retournerEtat = true;
        }
        
        if(_focus == Focus::BarrePseudo)
        {
            if(evt.type == sf::Event::KeyPressed)
            {
                if(evt.key.code == sf::Keyboard::Down)
                {
                    GestionnaireSon::jouer("changementFocus.wav");
                    _focus = Focus::CreerCompte;
                }
                if(evt.key.code == sf::Keyboard::BackSpace)
                    _zoneTexte.supprimerLettre();
            }
        }
        if(_focus == Focus::CreerCompte)
        {
            if(evt.key.code == sf::Keyboard::Right)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::Connexion;
            }
            if(evt.key.code == sf::Keyboard::Up)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::BarrePseudo;
            }
        }
        else if(_focus == Focus::Connexion)
        {
            if(evt.key.code == sf::Keyboard::Right)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::Quitter;
            }
            if(evt.key.code == sf::Keyboard::Left)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::CreerCompte;
            }
            if(evt.key.code == sf::Keyboard::Up)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::BarrePseudo;
            }
        }
        else if(_focus == Focus::Quitter)
        {
            if(evt.key.code == sf::Keyboard::Left)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::Connexion;
            }
            if(evt.key.code == sf::Keyboard::Up)
            {
                GestionnaireSon::jouer("changementFocus.wav");
                _focus = Focus::BarrePseudo;
            }
        }
    }
    
    if(evt.type == sf::Event::TextEntered)
    {
        if(_focus == Focus::BarrePseudo)
        {
            if ((evt.text.unicode >= 65 && evt.text.unicode <= 90) ||
                (evt.text.unicode >= 97 && evt.text.unicode <= 122)||
                (evt.text.unicode >= 48 && evt.text.unicode <= 57)
                )
                _zoneTexte.ajouterLettreTexte(static_cast<char>(evt.text.unicode));
        }
    }
    
    //Evenement souris
    
    if(evt.type == sf::Event::MouseButtonPressed)
    {
        for(int i = 1; i < _listeTexte.size(); i++)
        {
            if(_listeTexte[i].getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
            {
                _focus = static_cast<Focus>(i);
                return;
            }
        }
        if(_zoneTexte.contains(evt.mouseButton.x, evt.mouseButton.y))
            _focus = Focus::BarrePseudo;
        
        if(_bulleInformation.getGlobalBounds().contains(evt.mouseButton.x, evt.mouseButton.y))
        {
            if(_etatBulle == EtatBulleInformation::Activer)
                _etatBulle = EtatBulleInformation::Desactiver;
            else
                _etatBulle = EtatBulleInformation::Activer;
        }
    }
}

void MenuConnexion::update(sf::Time& delta)
{
    _informateurEtatConnexion.update(delta);
    switch(_etatBulle)
    {
        case(EtatBulleInformation::Activer):
        {
            _informateurEtatConnexion.activerInformateur();
            break;
        }
        case(EtatBulleInformation::Desactiver):
        {
            _informateurEtatConnexion.desactiverInformateur();
            break;
        }
    }
    switch(_focus)
    {
        case(Focus::BarrePseudo):
        {
            //faire un clignotement dans la barre
            _zoneTexte.gagnerFocus();
            _listeTexte[1].setColor(sf::Color::White);
            _listeTexte[2].setColor(sf::Color::White);
            _listeTexte[3].setColor(sf::Color::White);
            break;
        }
        case(Focus::CreerCompte):
        {
            _zoneTexte.perdreFocus();
            _listeTexte[1].setColor(sf::Color::Yellow);
            _listeTexte[2].setColor(sf::Color::White);
            _listeTexte[3].setColor(sf::Color::White);
            break;
        }
        case(Focus::Connexion):
        {
            _zoneTexte.perdreFocus();
            _listeTexte[1].setColor(sf::Color::White);
            _listeTexte[2].setColor(sf::Color::Yellow);
            _listeTexte[3].setColor(sf::Color::White);
            break;
        }
        case(Focus::Quitter):
        {
            _zoneTexte.perdreFocus();
            _listeTexte[1].setColor(sf::Color::White);
            _listeTexte[2].setColor(sf::Color::White);
            _listeTexte[3].setColor(sf::Color::Yellow);
            break;
        }
    }
}

void MenuConnexion::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_fond);
    _zoneTexte.draw(renderer);
    for(int i = 0; i < _listeTexte.size(); i++)
    {
        renderer.draw(_listeTexte[i]);
    }
    renderer.draw(_bulleInformation);
    _informateurEtatConnexion.draw(renderer);
}
