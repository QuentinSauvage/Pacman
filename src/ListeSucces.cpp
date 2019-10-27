//
//  ListeSucces.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 27/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "ListeSucces.h"
#include "OutilsDivers.h"
#include <fstream>

int     ListeSucces::_nbSucces = 0;

ListeSucces::ListeSucces(sf::Vector2f taillePlateau):
_taillePlateau(taillePlateau)
{
    
    std::string nomFichier = "Succes/listeSucces.txt";
    std::ifstream fichierSucces(nomFichier);
    
    std::string recuperateurInformation;
    std::pair<std::string, int> information;
    int cpt = 0;
    int positionY = 550;
    while(std::getline(fichierSucces,recuperateurInformation))
    {
        _nbSucces++;
        information.first  = decouperPhrase(recuperateurInformation, 1);
        information.second = std::stoi(decouperPhrase(recuperateurInformation, 3));
        
        _listeSucces.push_back(Succes(information, decouperPhrase(recuperateurInformation, 0),cpt));
        _listeSucces[cpt].construireCadreSucces(sf::Vector2f((_taillePlateau.x - 500)/2,positionY) );
        cpt++;
        positionY += 220;
    }
}

ListeSucces::~ListeSucces()
{
    
}

int ListeSucces::getValeurSucces(std::string nomSucces)const
{
    for(auto i : _listeSucces)
        if(i.getNomSucces() == nomSucces)
            return i.getScoreSucces();
}

int ListeSucces::getNombreSucces()
{
    return _nbSucces;
}

void ListeSucces::update(sf::Time &delta)
{
    for(auto i : _listeSucces)
        i.update(delta);
}

void ListeSucces::draw(sf::RenderWindow &renderer)
{
    for(auto i : _listeSucces)
        i.draw(renderer);
}

void ListeSucces::deverouillerSucces(int index)
{
    if(index < 0 || index > _listeSucces.size())
        throw ("Pas ce type de succes");
    
    _listeSucces[index].deverouillerSucces();
}
