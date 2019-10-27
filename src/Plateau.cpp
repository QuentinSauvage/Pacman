//
//  Plateau.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 03/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Plateau.h"
#include <iostream>
#include <random>
#include "OutilsDivers.h"

Plateau::Plateau(sf::Vector2f position, int niveau, std::string difficulte, Joueur& joueur):
_joueur(joueur),
_pacman(sf::Vector2f(position.x+32, position.y+32), position),
_map(niveau, position),
_niveau(niveau),
_deplacementPacman(DeplacementEnCours::Aucun),
_autoriseSaisieDeplacement(true),
_positionPlateau(position),
_pacgommeMange(0),
_nbFantomeKillParPacgomme(0),
_fruit(nullptr),
_score(0),
_dejaChoisitTest(false),
_directionSuivante('a'),
_superPacmanActive(false),
_tempsSuperPacman(nullptr),
_pause(false),
_difficulte(difficulte),
_vie10000donnee(false),
_vie20000donnee(false)
{
    _lesFantomes.push_back(Fantome(sf::Vector2f(position.x + 352, 288),position, 0,_difficulte));
    _lesFantomes.push_back(Fantome(sf::Vector2f(position.x + 352, 352),position, 1,_difficulte));
    _lesFantomes.push_back(Fantome(sf::Vector2f(position.x + 384, 352),position, 2,_difficulte));
    _lesFantomes.push_back(Fantome(sf::Vector2f(position.x + 416, 352),position, 3,_difficulte));
    
    
    _deplacementFantome.push_back(DeplacementEnCours::Aucun);
    _deplacementFantome.push_back(DeplacementEnCours::Aucun);
    _deplacementFantome.push_back(DeplacementEnCours::Aucun);
    _deplacementFantome.push_back(DeplacementEnCours::Aucun);
    
    _deplacementSecondaireFantome.push_back(DeplacementEnCours::Aucun);
    _deplacementSecondaireFantome.push_back(DeplacementEnCours::Aucun);
    _deplacementSecondaireFantome.push_back(DeplacementEnCours::Aucun);
    _deplacementSecondaireFantome.push_back(DeplacementEnCours::Aucun);
}

Plateau::~Plateau()
{
    
}

void Plateau::mettrePause()
{
    _pause = true;
    if(_tempsSuperPacman != nullptr)
        _tempsSuperPacman->pause();
}

void Plateau::stopperPause()
{
    _pause = false;
    if(_tempsSuperPacman != nullptr)
        _tempsSuperPacman->reprendre();
}

void Plateau::reinitialiserPositionPacman()
{
    _pacman.setPosition(sf::Vector2f(_positionPlateau.x + 32, _positionPlateau.y+32));
    _pacman.setPositionMatriciel(1*24+1);
    _deplacementPacman = DeplacementEnCours::Aucun;
    
    for(int i = 0; i< _lesFantomes.size(); i++)
    {
        _lesFantomes[i].enleverInvulnerabilite();
        _lesFantomes[i].redevenirNormal();
    }
    
    _pacman.setVitesse(2);
    _tempsSuperPacman = nullptr;
    _superPacmanActive = false;
}

void Plateau::reinitialiserPositionFantome()
{
    _lesFantomes[0].setPosition(sf::Vector2f(_positionPlateau.x + 352, 288));
    _lesFantomes[1].setPosition(sf::Vector2f(_positionPlateau.x + 352, 352));
    _lesFantomes[2].setPosition(sf::Vector2f(_positionPlateau.x + 384, 352));
    _lesFantomes[3].setPosition(sf::Vector2f(_positionPlateau.x + 416, 352));
    
    for(int i = 0; i < _lesFantomes.size(); i++)
        _lesFantomes[i].reinitialiserSortie();
}

void Plateau::reinitialiserPositionFantome(int indexFantome)
{
    switch (indexFantome)
    {
        case(0):
        {
            _lesFantomes[0].setPosition(sf::Vector2f(_positionPlateau.x + 352, 288));
            _lesFantomes[0].arreterDeplacement();
            _lesFantomes[0].reinitialiserSortie();
            break;
        }
        case(1):
        {
            _lesFantomes[1].setPosition(sf::Vector2f(_positionPlateau.x + 352, 352));
            _lesFantomes[1].arreterDeplacement();
            _lesFantomes[1].reinitialiserSortie();
            break;
        }
        case(2):
        {
            _lesFantomes[2].setPosition(sf::Vector2f(_positionPlateau.x + 384, 352));
            _lesFantomes[2].arreterDeplacement();
            _lesFantomes[2].reinitialiserSortie();
            break;
        }
        case(3):
        {
            _lesFantomes[3].setPosition(sf::Vector2f(_positionPlateau.x + 416, 352));
            _lesFantomes[3].arreterDeplacement();
            _lesFantomes[3].reinitialiserSortie();
            break;
        }
    }
}

int Plateau::getScore()const
{
    return _score;
}

void Plateau::setScore(int score)
{
    _score = score;
}

int Plateau::getViePacman()const
{
    return _pacman.getVie();
}

int Plateau::getNbPacgommeMange()const
{
    return _pacgommeMange;
}

bool Plateau::toutLesPacGommeMange()
{
    for(int i = 0; i < _map.getSize(); i++)
    {
        if(_map.getCase(i).pacGommePresente())
            return false;
    }
    return true;
}

void Plateau::draw(sf::RenderWindow& renderer)
{
    _map.draw(renderer);
    _pacman.draw(renderer);

    for(int i = 0; i < _lesFantomes.size(); i++)
    {
        _lesFantomes[i].draw(renderer);
    }
    
    if(_fruit != nullptr)
        _fruit->draw(renderer);
    
    
    //_debuggeur.draw(renderer);
}

bool Plateau::fruitPresent()const
{
    return _fruit!=nullptr;
}
void Plateau::genererFruit()
{
    //Generer un nombre aléatoire pour la ligne et la colonne, et tester si on peut poser le fruit à cette endroit.
    if(_fruit == nullptr)
    {
        sf::Vector2f positionMatriciel = sf::Vector2f(11, 13);
        _fruit = std::make_unique<Fruit>(positionMatriciel.x, positionMatriciel.y, _niveau);
        _fruit->setPosition(sf::Vector2f(_positionPlateau.x + (_fruit->getPositionMatriciel().x*32),
                                         _positionPlateau.y + (_fruit->getPositionMatriciel().y*32)));
    }
}

void Plateau::gestionFantomes(sf::Time& delta)
{
    for(int i = 0; i < _lesFantomes.size(); i++)
    {
        
        char directionSuivante;
        _lesFantomes[i].analyserPositionPacman(_pacman);
        char directionPremiere = _lesFantomes[i].choisirDirection();
        if(directionPremiere != 'a')
        {
            //Deplacement principal
            if(directionPremiere == 'z')
                _deplacementFantome[i] = DeplacementEnCours::Haut;
            else if(directionPremiere == 's')
                _deplacementFantome[i] = DeplacementEnCours::Bas;
            else if(directionPremiere == 'q')
                _deplacementFantome[i] = DeplacementEnCours::Gauche;
            else if(directionPremiere == 'd')
                _deplacementFantome[i] = DeplacementEnCours::Droite;
            
            //Deplacement secondaire
        }
        
        switch (_deplacementFantome[i])
        {
            case(DeplacementEnCours::Haut):
            {
                if(deplacementFantome(delta, 'z', _lesFantomes[i]))
                {
                    if(_deplacementSecondaireFantome[i] != DeplacementEnCours::Haut)
                    {
                        switch(_deplacementSecondaireFantome[i])
                        {
                            case(DeplacementEnCours::Bas):
                            {
                                if(deplacementFantome(delta, 's', _lesFantomes[i]))
                                {
                                    //arreter = true;
                                    _deplacementFantome[i] = DeplacementEnCours::Haut;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                break;
                            }
                            case(DeplacementEnCours::Gauche):
                            {
                                if(deplacementFantome(delta, 'q', _lesFantomes[i]))
                                {
                                    _deplacementFantome[i] = DeplacementEnCours::Haut;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                break;
                            }
                            case(DeplacementEnCours::Droite):
                            {
                                if(deplacementFantome(delta, 'd', _lesFantomes[i]))
                                {
                                    _deplacementFantome[i] = DeplacementEnCours::Haut;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                break;
                            }
                        }
                    }
                    
                }
                else
                {
                    _lesFantomes[i].arreterDeplacement();
                    choisirDirectionSecondaireFantome(i);
                }
                
                break;
            }
            case(DeplacementEnCours::Bas):
            {
                if(deplacementFantome(delta, 's', _lesFantomes[i]))
                {
                    if(_deplacementSecondaireFantome[i] != DeplacementEnCours::Bas)
                    {
                        switch(_deplacementSecondaireFantome[i])
                        {
                            case(DeplacementEnCours::Haut):
                            {
                                if(deplacementFantome(delta, 'z', _lesFantomes[i]))
                                {
                                    _deplacementFantome[i] = DeplacementEnCours::Haut;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                break;
                            }
                            case(DeplacementEnCours::Gauche):
                            {
                                if(deplacementFantome(delta, 'q', _lesFantomes[i]))
                                {
                                    _deplacementFantome[i] = DeplacementEnCours::Gauche;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                break;
                            }
                            case(DeplacementEnCours::Droite):
                            {
                                if(deplacementFantome(delta, 'd', _lesFantomes[i]))
                                {
                                    _deplacementFantome[i] = DeplacementEnCours::Droite;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                break;
                            }
                        }
                    }
                }
                else
                {
                    _lesFantomes[i].arreterDeplacement();
                    _directionSuivante = 'a';
                    choisirDirectionSecondaireFantome(i);
                }
                
                break;
            }
            case(DeplacementEnCours::Gauche):
            {
                if(deplacementFantome(delta, 'q', _lesFantomes[i]))
                {
                    if(_deplacementSecondaireFantome[i] != DeplacementEnCours::Gauche)
                    {
                        switch(_deplacementSecondaireFantome[i])
                        {
                            case(DeplacementEnCours::Haut):
                            {
                                if(deplacementFantome(delta, 'z', _lesFantomes[i]))
                                {
                                    _deplacementFantome[i] = DeplacementEnCours::Haut;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                break;
                            }
                            case(DeplacementEnCours::Bas):
                            {
                                if(deplacementFantome(delta, 's', _lesFantomes[i]))
                                {
                                    _deplacementFantome[i] = DeplacementEnCours::Bas;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                break;
                            }
                            case(DeplacementEnCours::Droite):
                            {
                                if(deplacementFantome(delta, 'd', _lesFantomes[i]))
                                {
                                    _deplacementFantome[i] = DeplacementEnCours::Droite;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                break;
                            }
                        }
                    }
                }
                else
                {
                    _lesFantomes[i].arreterDeplacement();
                    _directionSuivante = 'a';
                    choisirDirectionSecondaireFantome(i);
                }
                
                break;
            }
            case(DeplacementEnCours::Droite):
            {
                if(deplacementFantome(delta, 'd', _lesFantomes[i]))
                {
                    if(_deplacementSecondaireFantome[i] != DeplacementEnCours::Droite)
                    {
                        switch(_deplacementSecondaireFantome[i])
                        {
                            case(DeplacementEnCours::Haut):
                            {
                                if(deplacementFantome(delta, 'z', _lesFantomes[i]))
                                {
                                    _deplacementFantome[i] = DeplacementEnCours::Haut;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                else
                                {
                                    _lesFantomes[i].arreterDeplacement();
                                }
                                break;
                            }
                            case(DeplacementEnCours::Bas):
                            {
                                if(deplacementFantome(delta, 's', _lesFantomes[i]))
                                {
                                    _deplacementFantome[i] = DeplacementEnCours::Bas;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                else
                                {
                                    _lesFantomes[i].arreterDeplacement();
                                }
                                break;
                            }
                            case(DeplacementEnCours::Gauche):
                            {
                                if(deplacementFantome(delta, 'q', _lesFantomes[i]))
                                {
                                    _deplacementFantome[i] = DeplacementEnCours::Gauche;
                                    _deplacementSecondaireFantome[i] = DeplacementEnCours::Aucun;
                                }
                                else
                                {
                                    _lesFantomes[i].arreterDeplacement();
                                }
                                break;
                            }
                        }
                    }
                }
                else
                {
                    _lesFantomes[i].arreterDeplacement();
                    _directionSuivante = 'a';
                    choisirDirectionSecondaireFantome(i);
                }
                
                break;
            }
        }
        
        _lesFantomes[i].updateTime();
    }
}

void Plateau::gestionPacman(sf::Time& delta)
{
    switch (_deplacementPacman)
    {
            /**
             * Test des collisions avec les trois Cases devant le pacman ainsi:
             *   1  1 2 3   1
             * P 2    P     2 P     P
             *   3          3     1 2 3
             */
        case(DeplacementEnCours::Haut):
        {
            
            if(!deplacementPacman(delta, 'z'))
            {
                if(_pacman.getDirection() != 'z')
                {
                    switch(_pacman.getDirection())
                    {
                        case('s'):
                        {
                            if(!deplacementPacman(delta, 's'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                            break;
                        }
                        case('q'):
                        {
                            if(!deplacementPacman(delta, 'q'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                            break;
                        }
                        case('d'):
                        {
                            if(!deplacementPacman(delta, 'd'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                            break;
                        }
                    }
                }
                else
                {
                    _deplacementPacman = DeplacementEnCours::Aucun;
                }
            }
            break;
        }
            
        case(DeplacementEnCours::Bas):
        {
            
            if(!deplacementPacman(delta, 's'))
            {
                if(_pacman.getDirection() != 's')
                {
                    switch(_pacman.getDirection())
                    {
                        case('z'):
                        {
                            if(!deplacementPacman(delta, 'z'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                            break;
                        }
                        case('q'):
                        {
                            if(!deplacementPacman(delta, 'q'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                            break;
                        }
                        case('d'):
                        {
                            if(!deplacementPacman(delta, 'd'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                            break;
                        }
                    }
                }
                else
                {
                    _deplacementPacman = DeplacementEnCours::Aucun;
                }
            }
            break;
        }
            
        case(DeplacementEnCours::Gauche):
        {
            
            if(!deplacementPacman(delta, 'q'))
            {
                if(_pacman.getDirection() != 'q')
                {
                    switch(_pacman.getDirection())
                    {
                        case('z'):
                        {
                            if(!deplacementPacman(delta, 'z'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                            break;
                        }
                        case('s'):
                        {
                            if(!deplacementPacman(delta, 's'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                            break;
                        }
                        case('d'):
                        {
                            if(!deplacementPacman(delta, 'd'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                            break;
                        }
                    }
                }
                else
                {
                    _deplacementPacman = DeplacementEnCours::Aucun;
                }
            }
            break;
        }
        case(DeplacementEnCours::Droite):
        {
            if(!deplacementPacman(delta, 'd'))
            {
                if(_pacman.getDirection() != 'd')
                {
                    switch(_pacman.getDirection())
                    {
                        case('z'):
                        {
                            if(!deplacementPacman(delta, 'z'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                            break;
                        }
                        case('s'):
                        {
                            if(!deplacementPacman(delta, 's'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                        }
                            break;
                        case('q'):
                        {
                            if(!deplacementPacman(delta, 'q'))
                                _deplacementPacman = DeplacementEnCours::Aucun;
                            break;
                        }
                    }
                }
                else
                {
                    _deplacementPacman = DeplacementEnCours::Aucun;
                }
            }
            break;
        }
    }
}

void Plateau::setViePacman(int vie)
{
    _pacman.setVie(vie);
}

void Plateau::mangerFruit(int position)
{
    _joueur.updateIncrementPoint("pacgommeMange", 1);
    _joueur.updateIncrementPoint("score", _map.getCase(position).getPointPacGomme());
    _map.getCase(position).desactiverPacGomme();
    _map.getCase(position).setType(0);
    _score += _map.getCase(position).getPointPacGomme();
    _pacgommeMange++;
    if(!GestionnaireSon::enLecture())
        GestionnaireSon::jouer("miamPacgommeBis.wav");
    
    if(_joueur.recupererScore("pacgommeMange") >= _joueur.getListeSucces().getValeurSucces("MangeurDePacgommeAmateur"))
    {
        _joueur.validerSucces(3);
    }
    if(_joueur.recupererScore("pacgommeMange") >= _joueur.getListeSucces().getValeurSucces("MangeurDePacgommeEvolue"))
    {
        _joueur.validerSucces(4);
    }
    if(_joueur.recupererScore("pacgommeMange") >= _joueur.getListeSucces().getValeurSucces("MangeurDePacgommeExpert"))
    {
        _joueur.validerSucces(5);
    }
    
    if(_joueur.recupererScore("score") >= _joueur.getListeSucces().getValeurSucces("JoueurDebutant"))
    {
        _joueur.validerSucces(0);
    }
    if(_joueur.recupererScore("score") >= _joueur.getListeSucces().getValeurSucces("JoueurAssidue"))
    {
        _joueur.validerSucces(1);
    }
    if(_joueur.recupererScore("score") >= _joueur.getListeSucces().getValeurSucces("JoueurAccro"))
    {
        _joueur.validerSucces(2);
    }
}

bool Plateau::deplacementPacman(sf::Time& delta, char direction)
{
    switch (direction)
    {
        case ('z'):
        {
            sf::Vector2f savePositionPacman = _pacman.getPosition();
            _pacman.setPosition(sf::Vector2f(_pacman.getPosition().x , _pacman.getPosition().y - _pacman.getVitesse()));
            
            int positionCaseATester1 = _pacman.getPositionMatrice() - 25;
            int positionCaseATester2 = _pacman.getPositionMatrice() - 24;
            int positionCaseATester3 = _pacman.getPositionMatrice() - 23;
            
            bool conditionCollision1 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester1));
            bool conditionCollision2 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester2));
            bool conditionCollision3 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester3));
            
            _pacman.setPosition(savePositionPacman);
            
            if(!conditionCollision1 && !conditionCollision2 && !conditionCollision3)
            {
                _pacman.processEvent('z');
                _pacman.update(delta);
                
                int positionATester = _pacman.getPositionMatrice();
                if(GestionnaireCollision::collisionPacgomme(_pacman, _map.getCase(positionATester), 'z'))
                {
                    if(_map.getCase(positionATester).getType() == 5)
                    {
                        GestionnaireSon::jouer("pacman_extrapac.wav");
                        _nbFantomeKillParPacgomme = 0;
                        _superPacmanActive = true;
                        _tempsSuperPacman = std::make_unique<Temps>();
                        
                        _lesFantomes[0].enleverInvulnerabilite();
                        _lesFantomes[1].enleverInvulnerabilite();
                        _lesFantomes[2].enleverInvulnerabilite();
                        _lesFantomes[3].enleverInvulnerabilite();
                        
                    }
                    mangerFruit(positionATester);
                }
                return true;
            }
            else
            {
                return false;
            }
            
            break;
        }
        case ('s'):
        {
            sf::Vector2f savePositionPacman = _pacman.getPosition();
            _pacman.setPosition(sf::Vector2f(_pacman.getPosition().x , _pacman.getPosition().y + _pacman.getVitesse()));
            
            int positionCaseATester1 = _pacman.getPositionMatrice() + 23;
            int positionCaseATester2 = _pacman.getPositionMatrice() + 24;
            int positionCaseATester3 = _pacman.getPositionMatrice() + 25;
            
            
            bool conditionCollision1 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester1));
            bool conditionCollision2 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester2));
            bool conditionCollision3 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester3));
            
            _pacman.setPosition(savePositionPacman);
            
            if(!conditionCollision1 && !conditionCollision2 && !conditionCollision3)
            {
                _pacman.processEvent('s');
                _pacman.update(delta);
                
                int positionATester = _pacman.getPositionMatrice() + 24;
                if(GestionnaireCollision::collisionPacgomme(_pacman, _map.getCase(positionATester), 's'))
                {
                    if(_map.getCase(positionATester).getType() == 5)
                    {
                        GestionnaireSon::jouer("pacman_extrapac.wav");
                        _nbFantomeKillParPacgomme = 0;
                        _superPacmanActive = true;
                        _tempsSuperPacman = std::make_unique<Temps>();
                        
                        _lesFantomes[0].enleverInvulnerabilite();
                        _lesFantomes[1].enleverInvulnerabilite();
                        _lesFantomes[2].enleverInvulnerabilite();
                        _lesFantomes[3].enleverInvulnerabilite();
                    }
                    mangerFruit(positionATester);
                }
                return true;
            }
            else
            {
                return false;
            }
            
            break;
        }
        case ('q'):
        {
            sf::Vector2f savePositionPacman = _pacman.getPosition();
            _pacman.setPosition(sf::Vector2f(_pacman.getPosition().x  - _pacman.getVitesse(), _pacman.getPosition().y));
            
            int positionCaseATester1 = _pacman.getPositionMatrice() - 25;
            int positionCaseATester2 = _pacman.getPositionMatrice() - 1;
            int positionCaseATester3 = _pacman.getPositionMatrice() + 23;
            
            bool conditionCollision1 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester1));
            bool conditionCollision2 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester2));
            bool conditionCollision3 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester3));
            
            _pacman.setPosition(savePositionPacman);
            
            if(!conditionCollision1 && !conditionCollision2 && !conditionCollision3)
            {
                _pacman.processEvent('q');
                _pacman.update(delta);
                
                int positionATester = _pacman.getPositionMatrice();
                if(GestionnaireCollision::collisionPacgomme(_pacman, _map.getCase(positionATester), 'q'))
                {
                    if(_map.getCase(positionATester).getType() == 5)
                    {
                        GestionnaireSon::jouer("pacman_extrapac.wav");
                        _nbFantomeKillParPacgomme = 0;
                        _superPacmanActive = true;
                        _tempsSuperPacman = std::make_unique<Temps>();

                        _lesFantomes[0].enleverInvulnerabilite();
                        _lesFantomes[1].enleverInvulnerabilite();
                        _lesFantomes[2].enleverInvulnerabilite();
                        _lesFantomes[3].enleverInvulnerabilite();
                    }
                    mangerFruit(positionATester);
                }
                return true;
            }
            else
            {
                return false;
            }
            
            break;
        }
        case ('d'):
        {
            sf::Vector2f savePositionPacman = _pacman.getPosition();
            _pacman.setPosition(sf::Vector2f(_pacman.getPosition().x  + _pacman.getVitesse(), _pacman.getPosition().y));
            
            int positionCaseATester1 = _pacman.getPositionMatrice() - 23;
            int positionCaseATester2 = _pacman.getPositionMatrice() + 1;
            int positionCaseATester3 = _pacman.getPositionMatrice() + 25;
            
            bool conditionCollision1 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester1));
            bool conditionCollision2 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester2));
            bool conditionCollision3 = GestionnaireCollision::collisionMur(_pacman, _map.getCase(positionCaseATester3));
            
            _pacman.setPosition(savePositionPacman);
            
            if(!conditionCollision1 && !conditionCollision2 && !conditionCollision3)
            {
                _pacman.processEvent('d');
                _pacman.update(delta);
                
                int positionATester = _pacman.getPositionMatrice() + 1;
                if(GestionnaireCollision::collisionPacgomme(_pacman, _map.getCase(positionATester), 'd'))
                {
                    if(_map.getCase(positionATester).getType() == 5)
                    {
                        GestionnaireSon::jouer("pacman_extrapac.wav");
                        _nbFantomeKillParPacgomme = 0;
                        _superPacmanActive = true;
                        _tempsSuperPacman = std::make_unique<Temps>();

                        _lesFantomes[0].enleverInvulnerabilite();
                        _lesFantomes[1].enleverInvulnerabilite();
                        _lesFantomes[2].enleverInvulnerabilite();
                        _lesFantomes[3].enleverInvulnerabilite();
                    }
                    mangerFruit(positionATester);
                }
                return true;
            }
            else
            {
                return false;
            }
            
            break;
        }
    }
}

bool Plateau::deplacementFantome(sf::Time& delta, char direction, Fantome& fantome)
{
    switch (direction)
    {
        case ('z'):
        {
            sf::Vector2f savePositionFantome = fantome.getPosition();
            fantome.setPosition(sf::Vector2f(fantome.getPosition().x , fantome.getPosition().y - fantome.getVitesse()));
            
            int positionCaseATester1 = fantome.getPositionMatriciel() - 25;
            int positionCaseATester2 = fantome.getPositionMatriciel() - 24;
            int positionCaseATester3 = fantome.getPositionMatriciel() - 23;
            
            bool conditionCollision1 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester1));
            bool conditionCollision2 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester2));
            bool conditionCollision3 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester3));
            
            fantome.setPosition(savePositionFantome);
            
            if(!conditionCollision1 && !conditionCollision2 && !conditionCollision3)
            {
                fantome.processEvent('z');
                fantome.update(delta);
                return true;
            }
            else
            {
                return false;
            }

            break;
        }
        case ('s'):
        {
            sf::Vector2f savePositionFantome = fantome.getPosition();
            fantome.setPosition(sf::Vector2f(fantome.getPosition().x , fantome.getPosition().y + fantome.getVitesse()));
            
            int positionCaseATester1 = fantome.getPositionMatriciel() + 23;
            int positionCaseATester2 = fantome.getPositionMatriciel() + 24;
            int positionCaseATester3 = fantome.getPositionMatriciel() + 25;
            
            bool conditionCollision1 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester1));
            bool conditionCollision2 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester2));
            bool conditionCollision3 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester3));
            
            fantome.setPosition(savePositionFantome);
            
            if(!conditionCollision1 && !conditionCollision2 && !conditionCollision3)
            {
                fantome.processEvent('s');
                fantome.update(delta);
                return true;
            }
            else
            {
                return false;
            }

            break;
        }
        case ('q'):
        {
            sf::Vector2f savePositionFantome = fantome.getPosition();
            fantome.setPosition(sf::Vector2f(fantome.getPosition().x  - fantome.getVitesse() , fantome.getPosition().y));
            
            int positionCaseATester1 = fantome.getPositionMatriciel() - 25;
            int positionCaseATester2 = fantome.getPositionMatriciel() - 1;
            int positionCaseATester3 = fantome.getPositionMatriciel() + 23;
            
            bool conditionCollision1 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester1));
            bool conditionCollision2 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester2));
            bool conditionCollision3 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester3));
            
            fantome.setPosition(savePositionFantome);
            
            if(!conditionCollision1 && !conditionCollision2 && !conditionCollision3)
            {
                fantome.processEvent('q');
                fantome.update(delta);
                return true;
            }
            else
            {
                return false;
            }

            break;
        }
        case ('d'):
        {
            sf::Vector2f savePositionFantome = fantome.getPosition();
            fantome.setPosition(sf::Vector2f(fantome.getPosition().x + fantome.getVitesse(), fantome.getPosition().y));
            
            int positionCaseATester1 = fantome.getPositionMatriciel() - 23;
            int positionCaseATester2 = fantome.getPositionMatriciel() + 1;
            int positionCaseATester3 = fantome.getPositionMatriciel() + 25;
            
            bool conditionCollision1 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester1));
            bool conditionCollision2 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester2));
            bool conditionCollision3 = GestionnaireCollision::collisionMur(fantome, _map.getCase(positionCaseATester3));
            
            fantome.setPosition(savePositionFantome);
            
            if(!conditionCollision1 && !conditionCollision2 && !conditionCollision3)
            {
                fantome.processEvent('d');
                fantome.update(delta);
                return true;
            }
            else
            {
                return false;
            }

            break;
        }
    }
}

void Plateau::supprimerFruit()
{
    _fruit = nullptr;
}

void Plateau::choisirDirectionSecondaireFantome(int idFantome)
{
    if(_directionSuivante == 'a')
    {
        _directionSuivante = _lesFantomes[idFantome].choisirDirectionForce();
        if(_directionSuivante == 'z')
            _deplacementSecondaireFantome[idFantome] = DeplacementEnCours::Haut;
        else if(_directionSuivante == 's')
            _deplacementSecondaireFantome[idFantome] = DeplacementEnCours::Bas;
        else if(_directionSuivante == 'q')
            _deplacementSecondaireFantome[idFantome] = DeplacementEnCours::Gauche;
        else if(_directionSuivante == 'd')
            _deplacementSecondaireFantome[idFantome] = DeplacementEnCours::Droite;
        
    }
}

void Plateau::update(sf::Time& delta)
{
    //On test pendant chaque update si pacman est en collision avec le fruit si celui ci existe
    if(_fruit != nullptr)
    {
        if(_pacman.getSprite().getGlobalBounds().intersects(_fruit->getGlobalBouds()))
        {
            GestionnaireSon::jouer("pacman_eatfruit.wav");
            _joueur.updateIncrementPoint("score", _fruit->getPoint());
            _joueur.updateIncrementPoint("fruitMange", 1);
            _score += _fruit->getPoint();
            supprimerFruit();
            
            if(_joueur.recupererScore("score") >= _joueur.getListeSucces().getValeurSucces("JoueurDebutant"))
            {
                _joueur.validerSucces(0);
            }
            if(_joueur.recupererScore("score") >= _joueur.getListeSucces().getValeurSucces("JoueurAssidue"))
            {
                _joueur.validerSucces(1);
            }
            if(_joueur.recupererScore("score") >= _joueur.getListeSucces().getValeurSucces("JoueurAccro"))
            {
                _joueur.validerSucces(2);
            }
            
            if(_joueur.recupererScore("fruitMange") >= _joueur.getListeSucces().getValeurSucces("GloutonAmateur"))
            {
                _joueur.validerSucces(6);
            }
            if(_joueur.recupererScore("fruitMange") >= _joueur.getListeSucces().getValeurSucces("GloutonIntermediaire"))
            {
                _joueur.validerSucces(7);
            }
            if(_joueur.recupererScore("fruitMange") >= _joueur.getListeSucces().getValeurSucces("GloutonDevoreur"))
            {
                _joueur.validerSucces(8);
            }
        }
    }
    
    gestionFantomes(delta);
    gestionPacman(delta);

    if(_superPacmanActive)
    {
        for(int i = 0; i< _lesFantomes.size(); i++)
            _lesFantomes[i].devenirFaible();
        
        _pacman.setVitesse(4);
    }
    if(_tempsSuperPacman != nullptr)
    {
        _tempsSuperPacman->update();
        if(_tempsSuperPacman->getTempsSecondes() > 6)
        {
            for(int i = 0; i< _lesFantomes.size(); i++)
            {
                _lesFantomes[i].enleverInvulnerabilite();
                _lesFantomes[i].redevenirNormal();
            }
            
            _pacman.setVitesse(2);
            _tempsSuperPacman = nullptr;
            _superPacmanActive = false;
        }
    }
    
    if(_deplacementPacman == DeplacementEnCours::Aucun)
    {
        _pacman.processEvent('a');
    }
    
    //Gestion des collisions avec les fantomes
    for(int i = 0; i < _lesFantomes.size(); i++)
    {
        if(GestionnaireCollision::collisionFantome(_lesFantomes[i], _pacman))
        {
            if(_superPacmanActive && _lesFantomes[i].estFaible())
            {
                //Il faut encore donner les points pour manger les fantomes
                GestionnaireSon::jouer("pacman_eatghost.wav");
                reinitialiserPositionFantome(i);
                _lesFantomes[i].redevenirNormal();
                _lesFantomes[i].devenirInvulnerable();
                _joueur.updateIncrementPoint("fantomeMange", 1);
                
                if(_joueur.recupererScore("fantomeMange") >= _joueur.getListeSucces().getValeurSucces("Tueur"))
                {
                    _joueur.validerSucces(21);
                }
                if(_joueur.recupererScore("fantomeMange") >= _joueur.getListeSucces().getValeurSucces("Farouche"))
                {
                    _joueur.validerSucces(22);
                }
                if(_joueur.recupererScore("fantomeMange") >= _joueur.getListeSucces().getValeurSucces("Destructeur"))
                {
                    _joueur.validerSucces(23);
                }
                
                int nbPointGagne = puissance(200, _nbFantomeKillParPacgomme);
                _joueur.updateIncrementPoint("score", nbPointGagne);
                _score += nbPointGagne;
                _nbFantomeKillParPacgomme++;
                
                if(_joueur.recupererScore("score") >= _joueur.getListeSucces().getValeurSucces("JoueurDebutant"))
                {
                    _joueur.validerSucces(0);
                }
                if(_joueur.recupererScore("score") >= _joueur.getListeSucces().getValeurSucces("JoueurAssidue"))
                {
                    _joueur.validerSucces(1);
                }
                if(_joueur.recupererScore("score") >= _joueur.getListeSucces().getValeurSucces("JoueurAccro"))
                {
                    _joueur.validerSucces(2);
                }
            }
            else
            {
                _joueur.updateIncrementPoint("viePerdue", 1);
                _pacman.perdreVie();
                _superPacmanActive = false;
                reinitialiserPositionPacman();
                reinitialiserPositionFantome();
                
                for(int i = 0; i< _lesFantomes.size(); i++)
                {
                    _lesFantomes[i].enleverInvulnerabilite();
                    _lesFantomes[i].redevenirNormal();
                }
                
                _pacman.setVitesse(2);
                _tempsSuperPacman = nullptr;
                _superPacmanActive = false;
                
                if(_joueur.recupererScore("viePerdue") >= _joueur.getListeSucces().getValeurSucces("Martyr"))
                {
                    _joueur.validerSucces(18);
                }
                if(_joueur.recupererScore("viePerdue") >= _joueur.getListeSucces().getValeurSucces("SouffreDouleur"))
                {
                    _joueur.validerSucces(19);
                }
                if(_joueur.recupererScore("viePerdue") >= _joueur.getListeSucces().getValeurSucces("GrandMartyr"))
                {
                    _joueur.validerSucces(20);
                }
            }
            update(delta);
        }
    }
    if(_score > 10000 && !_vie10000donnee)
    {
        if(_pacman.getVie() < 3)
        {
            _pacman.setVie(_pacman.getVie()+1);
            _vie10000donnee = true;
        }
    }
    if(_score > 20000 && !_vie20000donnee)
    {
        if(_pacman.getVie() < 3)
        {
            _pacman.setVie(_pacman.getVie()+1);
            _vie20000donnee = true;
        }
    }
}

void Plateau::processEvent(const sf::Event& evt)
{
    if(evt.type == sf::Event::KeyPressed)
    {
        if(evt.key.code == sf::Keyboard::Escape)
        {
            //crée le menu pause
            _deplacementPacman = DeplacementEnCours::Aucun;
        }
        
        //Interaction pour le pacman
        if(_autoriseSaisieDeplacement)
        {
            if(evt.key.code == sf::Keyboard::Z || evt.key.code == sf::Keyboard::Up)
            {
                _deplacementPacman = DeplacementEnCours::Haut;
            }
            else if(evt.key.code == sf::Keyboard::S || evt.key.code == sf::Keyboard::Down)
            {
                _deplacementPacman = DeplacementEnCours::Bas;
            }
            else if(evt.key.code == sf::Keyboard::Q || evt.key.code == sf::Keyboard::Left)
            {
                _deplacementPacman = DeplacementEnCours::Gauche;
            }
            else if(evt.key.code == sf::Keyboard::D || evt.key.code == sf::Keyboard::Right)
            {
                _deplacementPacman = DeplacementEnCours::Droite;
            }
        }
    }
}