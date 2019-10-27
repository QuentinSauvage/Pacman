//
//  Joueur.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 07/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include <fstream>
#include "OutilsDivers.h"
#include "Joueur.h"

Joueur::Joueur(std::string pseudo):
_pseudo(pseudo),
_listeSucces(sf::Vector2f(1400, 768))
{
    chargerInformation();
}

Joueur::~Joueur()
{
    
}

void Joueur::updateSucces(sf::Time& delta)
{
    for(int i = 0; i < _idSuccesValide.size(); i++)
        _listeSucces.deverouillerSucces(_idSuccesValide[i]);
    
    _listeSucces.update(delta);
}

void Joueur::drawSucces(sf::RenderWindow& renderer)
{
    _listeSucces.draw(renderer);
}

std::string Joueur::getPseudo()const
{
    return _pseudo;
}

void Joueur::chargerInformation()
{
    //Chargement de la liste des caractéristiques du joueur
    std::string nomFichier = "Joueur/"+_pseudo+".txt";
    std::ifstream fluxJoueur(nomFichier);
    std::string ensembleSuccesValide;
    
    std::string recuperateurInformateur;
    int cpt = 0;
    while(std::getline(fluxJoueur,recuperateurInformateur))
    {
        if(decouperPhrase(recuperateurInformateur, 0) == "Succes")
        {
            ensembleSuccesValide = recuperateurInformateur;
        }
        else
        {
            _informationStatistique.push_back(std::pair<std::string, int>());
            _informationStatistique[cpt].first  = decouperPhrase(recuperateurInformateur, 0);
            _informationStatistique[cpt].second = std::stoi(decouperPhrase(recuperateurInformateur, 2));
            cpt++;
        }
    }
    
    std::string numeroSucces = "";
    for(int i = 0; i < ensembleSuccesValide.size(); i++)
    {
        if(ensembleSuccesValide[i] >= 48 && ensembleSuccesValide[i] <= 57)
        {
            numeroSucces += ensembleSuccesValide[i];
        }
        else if(ensembleSuccesValide[i] == ' ')
        {
            if(numeroSucces.size() > 0)
            {
                _idSuccesValide.push_back(std::stoi(numeroSucces));
                numeroSucces.clear();
            }
        }
    }
    if(numeroSucces.size() > 0)
        _idSuccesValide.push_back(std::stoi(numeroSucces));
}

const std::vector<int> Joueur::getIdSuccesValide()const
{
    return _idSuccesValide;
}

void Joueur::sauvegarderDonnees()
{
    std::string nomFichier = "Joueur/"+_pseudo+".txt";
    std::fstream fluxJoueur(nomFichier, std::ios::out|std::ios::trunc);
    
    if(fluxJoueur)
    {
        for(int i = 0; i < _informationStatistique.size(); i++)
        {
            std::string phrase = _informationStatistique[i].first + " = "+ std::to_string(_informationStatistique[i].second)+"\n";
            fluxJoueur << phrase;
        }
    
        std::string succes = "Succes ";
        for(int i = 0; i < _idSuccesValide.size(); i++)
        {
            
            if(i == (_idSuccesValide.size() - 1))
            {
                succes += std::to_string(_idSuccesValide[i]);
            }
            else
            {
                succes += std::to_string(_idSuccesValide[i])+" ";
            }
        }
        fluxJoueur << succes;
    }
    else
    {
        throw ("Probleme de sauvegarde");
    }
}

const ListeSucces& Joueur::getListeSucces()const
{
    return _listeSucces;
}

void Joueur::validerSucces(int index)
{
    for(auto i : _idSuccesValide)
        if(index == i)
            return;
    
    _listeSucces.deverouillerSucces(index);
    _idSuccesValide.push_back(index);
}

void Joueur::updateIncrementPoint(std::string nomSucces, int nbIncrement)
{
    for(int i = 0; i < _informationStatistique.size(); i++)
    {
        if(_informationStatistique[i].first == nomSucces)
            _informationStatistique[i].second += nbIncrement;
    }
}

int Joueur::recupererScore(std::string nomInformations)
{
    for(int i = 0; i < _informationStatistique.size(); i++)
    {
        if(_informationStatistique[i].first == nomInformations)
            return _informationStatistique[i].second;
    }
    throw ("Ce succes n'est pas repertorier dans le jeu");
}