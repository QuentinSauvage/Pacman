//
//  GestionnaireMenu.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 28/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "GestionnaireMenu.h"
#include "GestionnaireSon.h"
#include "OutilsDivers.h"
#include <fstream>

GestionnaireMenu::GestionnaireMenu(sf::Vector2f taillePlateau, Vue& vue):
_vueFenetre(vue),
_taillePlateau(taillePlateau),
_pseudoJoueur(""),
_choixTheme(std::make_unique<MenuChoixTheme>(taillePlateau)),
_connexion(nullptr),
_menuPrincipal(nullptr),
_statistiques(nullptr),
_option(nullptr),
_gestionnairePartie(nullptr),
_gameOver(nullptr),
_menuVictoire(nullptr),
_joueur(nullptr),
_horlogeGetReady(nullptr),
_quitterJeu(false),
_musiqueFond(false),
_theme("themePacman")
{
    chargerOption();
    if(_musiqueFond)
        GestionnaireSon::jouerMusiqueFond(_theme);
}

GestionnaireMenu::~GestionnaireMenu()
{
    
}


bool GestionnaireMenu::quitterPartie()
{
    return _quitterJeu;
}

void GestionnaireMenu::chargerOption()
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
                {
                    _modeHardcore = true;
                }
                else
                    _modeHardcore = false;
            }
            else if(decouperPhrase(recuperateur, 0) == "volume")
            {
                _volume = decouperPhrase(recuperateur, 2);
                GestionnaireSon::setVolumeGeneral(std::stoi(_volume));
            }
            else if(decouperPhrase(recuperateur, 0) == "difficulte")
            {
                _difficulte = decouperPhrase(recuperateur, 2);
            }
            else if(decouperPhrase(recuperateur, 0) == "musiqueFond")
            {
                if(decouperPhrase(recuperateur, 2) == "oui")
                {
                    _musiqueFond = true;
                    GestionnaireSon::autoriserMusiqueFond(true);
                    GestionnaireSon::jouerMusiqueFond(_theme);
                }
                else
                {
                    _musiqueFond = false;
                    GestionnaireSon::autoriserMusiqueFond(false);
                    GestionnaireSon::pasJouerMusiqueFond();
                }
            }
        }
    }
    else
    {
        throw "Impossible de charger les options";
    }
}

void GestionnaireMenu::evenementTheme()
{
    if(_choixTheme != nullptr)
    {
        std::string reponse = _choixTheme->getTheme();
        if(reponse == "pasDefini")
        {
            //On ne fait rien
        }
        else
        {
            if(reponse == "themePacman")
            {
                _theme = "themePacman";
                GraphicDispatcher::definirTheme(_theme);
                GraphicDispatcher::loadTextureEtFont();
                std::cout << "begin" << std::endl;
                GestionnaireSon::chargerSons("themePacman");
                std::cout << "end" << std::endl;
                _choixTheme = nullptr;
                _connexion = std::make_unique<MenuConnexion>(_taillePlateau, _theme);
            }
            else
            {
                _theme = "themeLotr";
                GraphicDispatcher::definirTheme(_theme);
                GraphicDispatcher::loadTextureEtFont();
                GestionnaireSon::chargerSons("themeLotr");
                _choixTheme = nullptr;
                _connexion = std::make_unique<MenuConnexion>(_taillePlateau, _theme);
            }
        }
    }
}

void GestionnaireMenu::evenementConnexion()
{
   
    if(_connexion != nullptr)
    {
        std::string reponse = _connexion->getBouttonAppuyer();
        if (reponse == "seConnecter")
        {
            if(_connexion->seConnecter())
            {
                //Connexion reussie
                _pseudoJoueur = _connexion->getPseudoJoueur();
                _joueur = std::make_unique<Joueur>(_pseudoJoueur);
                _connexion = nullptr;
                _menuPrincipal = std::make_unique<MenuPrincipal>(_taillePlateau, _theme, _pseudoJoueur);
            }
            else
            {
                //Connexion fail
                _connexion->desactiverEntree();
            }
        }
        else if(reponse == "creerCompte")
        {
            if(_connexion->creerCompte())
            {
                //creation compte reussie
                _connexion->desactiverEntree();
            }
            else
            {
                //Creation compte fail
                _connexion->desactiverEntree();
            }
        }
        else if(reponse == "Quitter")
        {
            _quitterJeu = true;
        }
        else
        {
        }
    }
}

void GestionnaireMenu::evenementStatistiques()
{
    if(_statistiques != nullptr)
    {
        std::string reponseScroll = _statistiques->getEtatScroll();
        /** Calcul de limiteMaxY:
         * _statistiques->getNombreSucces()*150    = espace total occupe par les cases succes
         * _statistiques->getNombreSucces()-1)*70  = espace total occupe par les marges entre chaque succes
         * 550 = Le debut des succes, avant il y a le titre et les statistiques
         */
        int limiteMaxY = ((_statistiques->getNombreSucces()*150) + (_statistiques->getNombreSucces()-1)*70)+550;
        if(reponseScroll == "haut")
        {
            _vueFenetre.move(-30, 0, limiteMaxY);
        }
        else if (reponseScroll == "bas")
        {
            _vueFenetre.move(30, 0, limiteMaxY);
        }
        else
        {
        }
        
        std::string reponse = _statistiques->getBouttonAppuyer();
        
        if(reponse == "revenirMenu")
        {
            _statistiques = nullptr;
            _vueFenetre.setVueParDefaut();
            _menuPrincipal = std::make_unique<MenuPrincipal>(_taillePlateau, _theme, _pseudoJoueur);
        }
        

    }
}

void GestionnaireMenu::evenementPrincipal()
{
    if(_menuPrincipal != nullptr)
    {
        std::string reponse = _menuPrincipal->getBouttonAppuyer();
        
        if(reponse == "Jouer")
        {
            _horlogeGetReady = std::make_unique<Temps>();
            GestionnaireSon::jouer("getReady.ogg");
            _menuPrincipal = nullptr;
            _gestionnairePartie = std::make_unique<GestionnairePartie>(_taillePlateau, _theme, _difficulte, *_joueur, 3);
        }
        else if(reponse == "Option")
        {
            _menuPrincipal = nullptr;
            _option = std::make_unique<MenuOption>(_taillePlateau);
            //Menu des options
        }
        else if(reponse == "Statistiques")
        {
            _menuPrincipal = nullptr;
            _statistiques = std::make_unique<MenuStatistiques>(_taillePlateau, *_joueur);
            
            //Menu des statistiques en fonction du joueur
        }
        else if(reponse == "Quitter")
        {
            _quitterJeu = true;
        }
    }
}

void GestionnaireMenu::evenementOption()
{
    if(_option != nullptr)
    {
        std::string reponse = _option->retournerReponse();
        if(reponse == "retournerMenu")
        {
            _option = nullptr;
            _menuPrincipal = std::make_unique<MenuPrincipal>(_taillePlateau, _theme, _pseudoJoueur);
        }
        else if(reponse == "appliquer")
        {
            _option->sauvegarderOptions();
            _option->reinitialiserEntree();
            
            chargerOption();
        }
    }
}

void GestionnaireMenu::evenementPlateau()
{
    if(_gestionnairePartie != nullptr)
    {
        if(_gestionnairePartie->partiePerdu())
        {
            _joueur->sauvegarderDonnees();
            _vueFenetre.setVueParDefaut();
            _gestionnairePartie = nullptr;
            _gameOver = std::make_unique<GameOver>(_taillePlateau);
            
        }
        else if(_gestionnairePartie->getQuitterPartie())
        {
            _quitterJeu = true;
        }
        else if(_gestionnairePartie->retournerMenuPrincipal())
        {
            _vueFenetre.setVueParDefaut();
            _gestionnairePartie = nullptr;
            _menuPrincipal = std::make_unique<MenuPrincipal>(_taillePlateau, _theme, _pseudoJoueur);
        }
        else if(_gestionnairePartie->getPartieCompleteGagne())
        {
            _joueur->sauvegarderDonnees();
            _vueFenetre.setVueParDefaut();
            _gestionnairePartie = nullptr;
            _menuVictoire = std::make_unique<MenuVictoire>(_taillePlateau, _theme);
        }
    }
}

void GestionnaireMenu::evenementGameOver()
{
    if(_gameOver != nullptr)
    {
        std::string reponse = _gameOver->recupererReponse();
        if(reponse == "oui")
        {
            _horlogeGetReady = std::make_unique<Temps>();
            GestionnaireSon::jouer("getReady.ogg");
            _gameOver = nullptr;
            _gestionnairePartie = std::make_unique<GestionnairePartie>(_taillePlateau, _theme, _difficulte, *_joueur, 1);
        }
        else if(reponse == "non")
        {
            _vueFenetre.setVueParDefaut();
            _gameOver = nullptr;
            _menuPrincipal = std::make_unique<MenuPrincipal>(_taillePlateau, _theme, _pseudoJoueur);
        }
    }
}

void GestionnaireMenu::evenementVictoire()
{
    if(_menuVictoire != nullptr)
    {
        std::string reponse = _menuVictoire->getBoutonAppuyer();
        if(reponse == "rejouer")
        {
            _joueur->sauvegarderDonnees();
            _menuVictoire = nullptr;
            _gestionnairePartie = std::make_unique<GestionnairePartie>(_taillePlateau, _theme, _difficulte, *_joueur, 1);
            
        }
        else if(reponse == "menuPrincipal")
        {
            _joueur->sauvegarderDonnees();
            _vueFenetre.setVueParDefaut();
            _menuVictoire = nullptr;
            _menuPrincipal = std::make_unique<MenuPrincipal>(_taillePlateau, _theme, _pseudoJoueur);
        }
        else if(reponse == "quitter")
        {
            _joueur->sauvegarderDonnees();
            _menuVictoire = nullptr;
            _quitterJeu = true;
        }
    }
}

void GestionnaireMenu::processEvent(sf::Event& evt)
{
    if(_choixTheme != nullptr)
        _choixTheme->processEvent(evt);
    if(_connexion != nullptr)
        _connexion->processEvent(evt);
    if(_menuPrincipal != nullptr)
        _menuPrincipal->processEvent(evt);
    if(_statistiques != nullptr)
        _statistiques->processEvent(evt);
    if(_option != nullptr)
        _option->processEvent(evt);
    if(_gestionnairePartie != nullptr)
    {
        if(_horlogeGetReady != nullptr)
        {
            if(_horlogeGetReady->getTempsSecondes() > GestionnaireSon::getDuree("getReady.ogg"))
            {
                _horlogeGetReady = nullptr;
            }
        }
        else
        {
            _horlogeGetReady = nullptr;
            _gestionnairePartie->processEvent(evt);
        }
    }
    if(_gameOver != nullptr)
        _gameOver->processEvent(evt);
    if(_menuVictoire != nullptr)
        _menuVictoire->processEvent(evt);
}

void GestionnaireMenu::update(sf::Time& delta)
{
    if(_horlogeGetReady != nullptr)
        _horlogeGetReady->update();
    
    
    //Fenetre
    
    if(_choixTheme != nullptr)
        _choixTheme->update(delta);
    if(_connexion != nullptr)
        _connexion->update(delta);
    if(_menuPrincipal != nullptr)
        _menuPrincipal->update(delta);
    if(_statistiques != nullptr)
        _statistiques->update(delta);
    if(_option != nullptr)
        _option->update(delta);
    if(_gestionnairePartie != nullptr)
    {
        //Si attente avant de lancer la partie
        if(_horlogeGetReady != nullptr)
        {
            if(_horlogeGetReady->getTempsSecondes() > GestionnaireSon::getDuree("getReady.ogg"))
            {
                _horlogeGetReady = nullptr;
            }
        }
        else
        {
            _horlogeGetReady = nullptr;
            _gestionnairePartie->update(delta);
            //Si hardcore(mode tourni active)
            if(_modeHardcore)
            {
                if(_gestionnairePartie->enPause())
                {
                    _vueFenetre.setVueParDefaut();
                }
                else
                {
                    _vueFenetre.rotate(1.0);
                }
            }
        }
        //Si entre partie Active
        if(_gestionnairePartie->entrePartieActive())
            _vueFenetre.setVueParDefaut();
    }
    if(_gameOver != nullptr)
        _gameOver->update(delta);
    if(_menuVictoire != nullptr)
        _menuVictoire->update(delta);
    
    evenementConnexion();
    evenementTheme();
    evenementPrincipal();
    evenementStatistiques();
    evenementOption();
    evenementPlateau();
    evenementGameOver();
    evenementVictoire();
}

void GestionnaireMenu::draw(sf::RenderWindow& renderer)
{
    if(_choixTheme != nullptr)
        _choixTheme->draw(renderer);
    if(_connexion != nullptr)
        _connexion->draw(renderer);
    if(_menuPrincipal != nullptr)
        _menuPrincipal->draw(renderer);
    if(_statistiques != nullptr)
        _statistiques->draw(renderer);
    if(_option != nullptr)
        _option->draw(renderer);
    if(_gestionnairePartie != nullptr)
        _gestionnairePartie->draw(renderer);
    if(_gameOver != nullptr)
        _gameOver->draw(renderer);
    if(_menuVictoire != nullptr)
        _menuVictoire->draw(renderer);
}