//
//  Fantome.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 17/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "Fantome.h"
#include "OutilsDivers.h"
#include <cmath>
Fantome::Fantome(sf::Vector2f positionDepart, sf::Vector2f positionPlateau, int idFantome, std::string difficulte):
//_IA(),
_id(idFantome),
_positionPlateau(positionPlateau),
_positionColonne((positionDepart.x - positionPlateau.x)/32),
_positionLigne((positionDepart.y - positionPlateau.y)/32),
_enVie(true),
_vitesse(2),
_sprite(GraphicDispatcher::getTextureFantome(idFantome*2)),
_direction(Direction::Aucune),
_directionSecondaire(Direction::Aucune),
_rafraichissementDirection(),
_rafraichissementMouvement(),
_rafraichissementMouvementPeur(nullptr),
_typeMouvement(TypeMouvement::BoucheFerme),
_tempsRafraichissement(0.15),
_etat(Etat::Arret),
_sortieCage(false),
_directionPrincipalPrivilegie('a'),
_directionSecondairePrivilegie('s'),
_difficulte(difficulte),
_faible(false),
_typeMouvementPeur(TypemouvementPeur::FormeBlanche),
_invulnerabiliteFaiblesse(false)
{
    _positionMatriciel = _positionLigne * 24 + _positionColonne;
    _sprite.setPosition(positionDepart.x, positionDepart.y);
}

Fantome::~Fantome()
{
    delete _rafraichissementMouvementPeur;
    _rafraichissementMouvementPeur = nullptr;
}

void Fantome::arreterDeplacement()
{
    _etat = Etat::Arret;
}

void Fantome::devenirFaible()
{
    if(!_invulnerabiliteFaiblesse)
    {
        _faible = true;
    }
}

void Fantome::redevenirNormal()
{
    _faible = false;
}

char Fantome::directionPrincipalSortirSpawn()
{
    //Direction : 12 x et 11 y
    
    if(_positionLigne > 9)
    {
        return 'z';
    }
    else if(_positionLigne < 9)
    {
        return 's';
    }
    
    return 'a';
}

char Fantome::directionSecondaireSortirSpawn()
{
    if(_positionColonne > 11)
    {
        return 'q';
    }
    else if(_positionColonne < 11)
    {
        return 'd';
    }
    
    return 'a';
}

void Fantome::processEvent(char direction)
{
    switch(direction)
    {
        case ('z'):
        {
            _direction = Direction::Haut;
            _etat = Etat::EnMouvement;
            break;
        }
        case ('s'):
        {
            _direction = Direction::Bas;
            _etat = Etat::EnMouvement;
            break;
        }
        case ('q'):
        {
            _direction = Direction::Gauche;
            _etat = Etat::EnMouvement;
            break;
        }
        case ('d'):
        {
            _direction = Direction::Droite;
            _etat = Etat::EnMouvement;
            break;
        }
    }
}

void Fantome::setPositionMatriciel(int position)
{
    _positionMatriciel = position;
}

void Fantome::setPosition(sf::Vector2f position)
{
    _sprite.setPosition(position);
}

bool Fantome::estFaible()const
{
    return _faible;
}

void Fantome::devenirInvulnerable()
{
    _invulnerabiliteFaiblesse = true;
}

void Fantome::enleverInvulnerabilite()
{
    _invulnerabiliteFaiblesse = false;
}

sf::Vector2f Fantome::getPosition()const
{
    return _sprite.getPosition();
}

int Fantome::getPositionMatriciel()const
{
    return _positionMatriciel;
}

bool Fantome::estSorti()const
{
    return _sortieCage;
}

char Fantome::getDirection()const
{
    switch(_direction)
    {
        case(Direction::Haut):
        {
            return 'z';
            break;
        }
        case(Direction::Bas):
        {
            return 's';
            break;
        }
        case(Direction::Gauche):
        {
            return 'q';
            break;
        }
        case(Direction::Droite):
        {
            return 'd';
            break;
        }
        case(Direction::Aucune):
        {
            return 'a';
            break;
        }
    }
}

char Fantome::getDirectionSecondaire()const
{
    switch(_directionSecondaire)
    {
        case(Direction::Haut):
        {
            return 'z';
            break;
        }
        case(Direction::Bas):
        {
            return 's';
            break;
        }
        case(Direction::Gauche):
        {
            return 'q';
            break;
        }
        case(Direction::Droite):
        {
            return 'd';
            break;
        }
        case(Direction::Aucune):
        {
            return 'a';
            break;
        }
    }
}

int Fantome::getVitesse()const
{
    return _vitesse;
}

void Fantome::analyserPositionMatriciel(int directionMatriciel)
{
    int ligneDirection = directionMatriciel / 24;
    int colonneDirection = directionMatriciel % 24;
    
    int differenceColonne = _positionColonne   - ligneDirection;
    int differenceLigne   = _positionLigne     - colonneDirection;
    
    char directionPrincipal;
    char directionSecondaire;
    
    if(differenceLigne > 0)
    {
        _directionPrincipalPrivilegie = 'z';
    }
    else if (differenceLigne < 0)
    {
        _directionPrincipalPrivilegie = 's';
    }
    if(differenceColonne > 0)
    {
        _directionSecondairePrivilegie = 'q';
    }
    else if(differenceColonne < 0)
    {
        _directionSecondairePrivilegie = 'd';
    }
}


char Fantome::directionInky(const Pacman& pacman) //Embuscade
{
    if(_faible)
    {
        char directionPrincipalPeur = directionPrincipaleAppeure(pacman);
        char directionSecondairePeur = directionSecondaireAppeure(pacman);
    }
    else if(!_sortieCage)
    {
        char directionPrincipal = seDirigerVersPositionPrincipal(0);
        char directionSecondaire = seDirigerVersPositionSecondaire(0);
    }
    else
    {
        //Embuscade
    }
}

char Fantome::directionPinky(const Pacman& pacman) //Embuscade
{
    if(_faible)
    {
        char directionPrincipalPeur = directionPrincipaleAppeure(pacman);
        char directionSecondairePeur = directionSecondaireAppeure(pacman);
        
    }
    else if(!_sortieCage)
    {
        char directionPrincipal = seDirigerVersPositionPrincipal(0);
        char directionSecondaire = seDirigerVersPositionSecondaire(0);
    }
    else
    {
        //embuscade
    }
}

char Fantome::directionClynde(const Pacman& pacman) // Il se deplace completement aleatoirement
{
    if(_faible)
    {
        char directionPrincipalPeur = directionPrincipaleAppeure(pacman);
        char directionSecondairePeur = directionSecondaireAppeure(pacman);
    }
    else if(!_sortieCage)
    {
        char directionPrincipal = seDirigerVersPositionPrincipal(0);
        char directionSecondaire = seDirigerVersPositionSecondaire(0);
    }
    else
    {
        char directionPrincipal = seDirigerAleatoirement();
        char directionSecondaire = seDirigerAleatoirement();
    }
}


char Fantome::directionBlinky(const Pacman& pacman) //Il traque le pacman
{
    if(_faible)
    {
        char directionPrincipalPeur = directionPrincipaleAppeure(pacman);
        char directionSecondairePeur = directionSecondaireAppeure(pacman);
    }
    else if(!_sortieCage)
    {
        char directionPrincipal = seDirigerVersPositionPrincipal(0);
        char directionSecondaire = seDirigerVersPositionSecondaire(0);
    }
    else
    {
        char directionPrincipal = seDirigerVersPositionPrincipal(pacman.getPositionMatrice());
        char directionSecondaire = seDirigerVersPositionSecondaire(pacman.getPositionMatrice());
        
        
    }
}



int Fantome::analyserDistancePacman(const Pacman& pacman)
{
    return sqrt(pacman.getPosition().x - _sprite.getPosition().x) + sqrt(pacman.getPosition().y - _sprite.getPosition().y);
}

char Fantome::directionPrincipaleAppeure(const Pacman& pacman)
{
    int positionPacmanMatrice = pacman.getPositionMatrice();
    
    int lignePacman = positionPacmanMatrice / 24;
    
    int differenceLigne = _positionLigne - lignePacman;

    if(differenceLigne < 0)
    {
        return 's';
    }
    else if(differenceLigne > 0)
    {
        return 'z';
    }

}

char Fantome::directionSecondaireAppeure(const Pacman& pacman)
{
    int positionPacmanMatrice = pacman.getPositionMatrice();
    
    int colonnePacman = positionPacmanMatrice % 24;
    
    int differenceColonne = _positionColonne - colonnePacman;
    
    if(differenceColonne < 0)
    {
        return 'd';
    }
    else if(differenceColonne > 0)
    {
        return 'q';
    }
}




char Fantome::seDirigerVersPositionPrincipal(int directionMatriciel)
{
    int ligneDirection = directionMatriciel / 24;
    
    int differenceLigne   = _positionLigne     - ligneDirection;
    
    if(differenceLigne < 0)
    {
        return 'z';
    }
    else if(differenceLigne > 0)
    {
        return 's';
    }
}

char Fantome::seDirigerVersPositionSecondaire(int directionMatriciel)
{
    int colonneDirection = directionMatriciel % 24;
    
    int differenceColonne =_positionColonne - colonneDirection;
    
    if(differenceColonne < 0)
    {
        return 'q';
    }
    else if(differenceColonne > 0)
    {
        return 'd';
    }
}

char Fantome::seDirigerAleatoirement()
{
    int directionAleatoire = getRandom(1,4);
    
    if(directionAleatoire == 1)
    {
        return 'z';
    }
    else if(directionAleatoire == 2)
    {
        return 's';
    }
    else if(directionAleatoire == 3)
    {
        return 'q';
    }
    else if(directionAleatoire == 4)
    {
        return 'd';
    }
}



void Fantome::analyserPositionPacman(const Pacman& pacman)
{
    int lignePacman = pacman.getLigne();
    int colonnePacman = pacman.getColonne();
    
    int differenceColonne = _positionColonne   - colonnePacman;
    int differenceLigne   = _positionLigne     - lignePacman;
    
    char direction;
    char directionSecondaire;
    //Deplacement principal
    if(differenceLigne > 0)
    {
        _directionPrincipalPrivilegie = 'z';
    }
    else if(differenceLigne < 0)
    {
        _directionPrincipalPrivilegie = 's';
    }
    //Deplacement secondaire
    if(differenceColonne > 0)
    {
        _directionSecondairePrivilegie = 'q';
    }
    else if(differenceColonne < 0)
    {
        _directionSecondairePrivilegie = 'd';
    }
}

const sf::Sprite& Fantome::getSprite()const
{
    return _sprite;
}

void Fantome::jouer()
{
    choisirDirection();
}

char Fantome::choisirDirection()
{
    if(_difficulte == "intermediaire")
    {
        if(_etat == Etat::Arret)
        {
            
            int direction = getRandom(1,10);
            switch(_directionPrincipalPrivilegie)
            {
                case('z'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 'z';
                    else if(direction >= 5 && direction <= 6)
                        return 's';
                    else if(direction >= 7 && direction <= 8)
                        return 'q';
                    else if(direction >= 9 && direction <= 10)
                        return 'd';
                    
                    break;
                }
                case('s'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 's';
                    else if(direction >= 5 && direction <= 6)
                        return 'z';
                    else if(direction >= 7 && direction <= 8)
                        return 'q';
                    else if(direction >= 9 && direction <= 10)
                        return 'd';
                    break;
                }
                case('q'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 'q';
                    else if(direction >= 5 && direction <= 6)
                        return 'z';
                    else if(direction >= 7 && direction <= 8)
                        return 's';
                    else if(direction >= 9 && direction <= 10)
                        return 'd';
                    break;
                }
                case('d'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 'd';
                    else if(direction >= 5 && direction <= 6)
                        return 'z';
                    else if(direction >= 7 && direction <= 8)
                        return 's';
                    else if(direction >= 9 && direction <= 10)
                        return 'q';
                    break;
                }
            }
        }
        else
        {
            
            return 'a';
        }
    }
    
    else if(_difficulte == "difficile")
    {
        if(_etat == Etat::Arret)
        {
            
            int direction = getRandom(1,10);
            switch(_directionPrincipalPrivilegie)
            {
                case('z'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 'z';
                    else if(direction >= 5 && direction <= 6)
                        return 's';
                    else if(direction >= 7 && direction <= 8)
                        return 'q';
                    else if(direction >= 9 && direction <= 10)
                        return 'd';
                    break;
                }
                case('s'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 's';
                    else if(direction >= 5 && direction <= 6)
                        return 'z';
                    else if(direction >= 7 && direction <= 8)
                        return 'q';
                    else if(direction >= 9 && direction <= 10)
                        return 'd';
                    break;
                }
                case('q'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 'q';
                    else if(direction >= 5 && direction <= 6)
                        return 'z';
                    else if(direction >= 7 && direction <= 8)
                        return 's';
                    else if(direction >= 9 && direction <= 10)
                        return 'd';
                    break;
                }
                case('d'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 'd';
                    else if(direction >= 5 && direction <= 6)
                        return 'z';
                    else if(direction >= 7 && direction <= 8)
                        return 's';
                    else if(direction >= 9 && direction <= 10)
                        return 'q';
                    break;
                }
            }
        }
        else
        {
            
            return 'a';
        }
    }
    
    else
    {
        if(_etat == Etat::Arret)
        {
            int direction = getRandom(1,4);
        
            if(direction == 1)
                return 'z';
            else if(direction == 2)
                return 's';
            else if(direction == 3)
                return 'q';
            else if(direction == 4)//direction == 4
                return 'd';
        }
        else
        {
            
            return 'a';
        }
    }
}

void Fantome::reinitialiserSortie()
{
    _sortieCage = false;
}

char Fantome::choisirDirectionForce()
{
    if(_difficulte == "intermediaire")
    {
        if(_etat == Etat::Arret)
        {
            
            int direction = getRandom(1,10);
            switch(_directionPrincipalPrivilegie)
            {
                case('z'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 'z';
                    else if(direction >= 5 && direction <= 6)
                        return 's';
                    else if(direction >= 7 && direction <= 8)
                        return 'q';
                    else if(direction >= 9 && direction <= 10)
                        return 'd';
                    
                    break;
                }
                case('s'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 's';
                    else if(direction >= 5 && direction <= 6)
                        return 'z';
                    else if(direction >= 7 && direction <= 8)
                        return 'q';
                    else if(direction >= 9 && direction <= 10)
                        return 'd';
                    break;
                }
                case('q'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 'q';
                    else if(direction >= 5 && direction <= 6)
                        return 'z';
                    else if(direction >= 7 && direction <= 8)
                        return 's';
                    else if(direction >= 9 && direction <= 10)
                        return 'd';
                    break;
                }
                case('d'):
                {
                    if(direction >= 0 && direction <= 4)
                        return 'd';
                    else if(direction >= 5 && direction <= 6)
                        return 'z';
                    else if(direction >= 7 && direction <= 8)
                        return 's';
                    else if(direction >= 9 && direction <= 10)
                        return 'q';
                    break;
                }
            }
        }
        else
        {
            
            return 'a';
        }
    }
    
    if(_difficulte == "difficile")
    {
        if(_etat == Etat::Arret)
        {
            
            int direction = getRandom(1,10);
            switch(_directionSecondairePrivilegie)
            {
                case('z'):
                {
                    if(direction >= 0 && direction <= 7)
                        return 'z';
                    else if(direction == 8)
                        return 's';
                    else if(direction == 9)
                        return 'q';
                    else if(direction == 10)
                        return 'd';
                    break;
                }
                case('s'):
                {
                    if(direction >= 0 && direction <= 7)
                        return 's';
                    else if(direction == 8)
                        return 'z';
                    else if(direction == 9)
                        return 'q';
                    else if(direction == 10)
                        return 'd';
                    break;
                }
                case('q'):
                {
                    if(direction >= 0 && direction <= 7)
                        return 'q';
                    else if(direction == 8)
                        return 'z';
                    else if(direction == 9)
                        return 's';
                    else if(direction == 10)
                        return 'd';
                    break;
                }
                case('d'):
                {
                    if(direction >= 0 && direction <= 7)
                        return 'd';
                    else if(direction == 8)
                        return 'z';
                    else if(direction == 9)
                        return 's';
                    else if(direction == 10)
                        return 'q';
                    break;
                }
            }
        }
        else
        {
            return 'a';
        }
    }
    
    else
    {
        int direction = getRandom(1,4);

        if(direction == 1)
            return 'z';
        else if(direction == 2)
            return 's';
        else if(direction == 3)
            return 'q';
        else //direction == 4
            return 'd';
    }
}

void Fantome::updateTime()
{
    _rafraichissementDirection.update();
}

void Fantome::update(sf::Time& delta)
{
    _rafraichissementMouvement.update();
    if(_faible && _rafraichissementMouvementPeur == nullptr)
    {
        _rafraichissementMouvementPeur = new Temps();
    }
    if(!_faible && _rafraichissementMouvementPeur != nullptr)
    {
        delete _rafraichissementMouvementPeur;
        _rafraichissementMouvementPeur = nullptr;
    }
    
    if(_rafraichissementMouvementPeur != nullptr)
        _rafraichissementMouvementPeur->update();
    
    
    if( (_positionMatriciel ==  227 || _positionMatriciel == 228) && !_sortieCage)

    {
        _sortieCage = true;
    }
    
    
    if(_etat == Etat::EnMouvement)
    {
        if(_faible)
        {
            if(_typeMouvementPeur == TypemouvementPeur::FormeBleu && _rafraichissementMouvementPeur->getTempsReel().asSeconds() > _tempsRafraichissement)
            {
                _sprite.setTexture(GraphicDispatcher::getTextureFantomeFaible(0));
                if(_rafraichissementMouvementPeur->getTempsReel().asSeconds() > _tempsRafraichissement)
                {
                    _typeMouvementPeur = TypemouvementPeur::FormeBlanche;
                    _rafraichissementMouvementPeur->redemarrer();
                }
            }
            else if(_typeMouvementPeur == TypemouvementPeur::FormeBlanche && _rafraichissementMouvementPeur->getTempsReel().asSeconds() > _tempsRafraichissement)
            {
                _sprite.setTexture(GraphicDispatcher::getTextureFantomeFaible(3));
                if(_rafraichissementMouvementPeur->getTempsReel().asSeconds() > _tempsRafraichissement)
                {
                    _typeMouvementPeur = TypemouvementPeur::FormeBleu;
                    _rafraichissementMouvementPeur->redemarrer();
                }
            }
        }

        switch (_direction)
        {
            case (Direction::Haut):
            {
                //Partie Graphique
                if(!_faible)
                {
                    if(_typeMouvement == TypeMouvement::BoucheFerme && _rafraichissementMouvement.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _etat = Etat::EnMouvement;
                        _rafraichissementMouvement.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheOuverte;
                        _sprite.setTexture(GraphicDispatcher::getTextureFantome((_id * 2) + (3 * 8) + 1));
                    }
                    else if(_typeMouvement == TypeMouvement::BoucheOuverte && _rafraichissementMouvement.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementMouvement.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheFerme;
                        _sprite.setTexture(GraphicDispatcher::getTextureFantome((_id * 2) + (3 * 8)));
                    }
                }
            
                _sprite.move(0,- _vitesse);
            
                //Partie logique
                _etat = Etat::EnMouvement;
                _positionColonne = (_sprite.getPosition().x - _positionPlateau.x)/32;
                _positionLigne = _sprite.getPosition().y / 32;
                _positionMatriciel = _positionLigne * 24 + _positionColonne;
                break;
            }
            case (Direction::Bas):
            {
                //Partie Graphique
                if(!_faible)
                {
                    if(_typeMouvement == TypeMouvement::BoucheFerme && _rafraichissementMouvement.getTempsReel().asSeconds() >  _tempsRafraichissement)
                    {
                        _rafraichissementMouvement.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheOuverte;
                        _sprite.setTexture(GraphicDispatcher::getTextureFantome((_id * 2) + (1 * 8) + 1));
                    }
                    else if(_typeMouvement == TypeMouvement::BoucheOuverte && _rafraichissementMouvement.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementMouvement.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheFerme;
                        _sprite.setTexture(GraphicDispatcher::getTextureFantome((_id * 2) + (1 * 8)));
                    }
                }

                _sprite.move(0, _vitesse);
            
                //Partie logique
                _etat = Etat::EnMouvement;
                _positionColonne = (_sprite.getPosition().x - _positionPlateau.x)/32;
                _positionLigne = _sprite.getPosition().y / 32;
                _positionMatriciel = _positionLigne * 24 + _positionColonne;
                break;
            }
            case (Direction::Gauche):
            {
                //Partie Graphique
                if(!_faible)
                {
                    if(_typeMouvement == TypeMouvement::BoucheFerme && _rafraichissementMouvement.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementMouvement.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheOuverte;
                        _sprite.setTexture(GraphicDispatcher::getTextureFantome((_id * 2) + (2 * 8) + 1));
                    }
                    else if(_typeMouvement == TypeMouvement::BoucheOuverte && _rafraichissementMouvement.getTempsReel().asSeconds() >   _tempsRafraichissement)
                    {
                        _rafraichissementMouvement.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheFerme;
                        _sprite.setTexture(GraphicDispatcher::getTextureFantome((_id * 2) + (2 * 8)));
                    }
                }
            
                _sprite.move(-_vitesse, 0);
            
                //Partie Logique
                _etat = Etat::EnMouvement;
                _positionColonne = (_sprite.getPosition().x - _positionPlateau.x)/32;
                _positionLigne = _sprite.getPosition().y / 32;
                _positionMatriciel = _positionLigne * 24 + _positionColonne;
                break;
            }
            case (Direction::Droite):
            {
                //Partie Graphique
                if(!_faible)
                {
                    if(_typeMouvement == TypeMouvement::BoucheFerme && _rafraichissementMouvement.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementMouvement.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheOuverte;
                        _sprite.setTexture(GraphicDispatcher::getTextureFantome((_id * 2) + (0 * 8) + 1));
                    }
                    else if(_typeMouvement == TypeMouvement::BoucheOuverte && _rafraichissementMouvement.getTempsReel().asSeconds() > _tempsRafraichissement)
                    {
                        _rafraichissementMouvement.redemarrer();
                        _typeMouvement = TypeMouvement::BoucheFerme;
                        _sprite.setTexture(GraphicDispatcher::getTextureFantome((_id * 2) + (0 * 8)));
                    }
                }
            
                _sprite.move(_vitesse, 0);
                
                //Partie Logique
                _etat = Etat::EnMouvement;
                _positionColonne = (_sprite.getPosition().x - _positionPlateau.x)/32;
                _positionLigne = _sprite.getPosition().y / 32;
                _positionMatriciel = _positionLigne * 24 + _positionColonne;
            
                break;
            }
            default:
            {
                std::cout<<"Nothing"<<std::endl;
                break;
            }
        }
        
    }
}

void Fantome::draw(sf::RenderWindow& renderer)
{
    renderer.draw(_sprite);
}