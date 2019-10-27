//
//  GestionnaireConnexion.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 28/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "GestionnaireConnexion.h"
#include <fstream>


GestionnaireConnexion::GestionnaireConnexion():
_nomFichierPseudo("Joueur/listeJoueurs.txt")
{
    recupererPseudo();
}


GestionnaireConnexion::~GestionnaireConnexion()
{
    
}

void GestionnaireConnexion::recupererPseudo()
{
    std::ifstream flux(_nomFichierPseudo);
    
    if(flux)
    {
        std::string recuperateur;
        while(std::getline(flux, recuperateur))
        {
            _listePseudo.push_back(recuperateur);
        }
    }
    else
    {
        throw ("Impossible d'ouvrir le fichier");
    }
}

void GestionnaireConnexion::ecrirePseudo()
{
    std::ofstream flux(_nomFichierPseudo);
    
    if(flux)
    {
        for(std::string i : _listePseudo)
            flux << i+"\n";
    }
    else
    {
        throw ("Erreur d'ouverture");
    }
}

bool GestionnaireConnexion::verifierPseudo(std::string pseudo)
{
    for(std::string i : _listePseudo)
        if(i == pseudo)
            return true;
    
    return false;
}

/*void GestionnaireConnexion::supprimerCompte(std::string pseudo)
{
    if(verifierPseudo(pseudo))
    {
        for(int i = 0; i< _listePseudo.size(); i++)
        {
            if(_listePseudo[i] == pseudo)
            {
                //On swap le pseudo avec le dernier et on supprime
                std::string tmp = _listePseudo[i];
                _listePseudo[i] = _listePseudo[_listePseudo.size() - 1];
                _listePseudo[_listePseudo.size() - 1] = tmp;
                
                _listePseudo.resize(_listePseudo.size() - 1);
                ecrirePseudo();
            }
        }
    }
}*/


bool GestionnaireConnexion::seConnecter(std::string pseudo)
{
    return verifierPseudo(pseudo);
}

bool GestionnaireConnexion::creerCompte(std::string pseudo)
{
    if(verifierPseudo(pseudo) || pseudo.size() == 0)
    {
        return false;
    }
    else
    {
        _listePseudo.push_back(pseudo);
        ecrirePseudo();
        std::ofstream flux("Joueur/"+pseudo+".txt");
        std::vector<std::string> items;
        items.push_back("score = 0");
        items.push_back("pacgommeMange = 0");
        items.push_back("fruitMange = 0");
        items.push_back("nbThemePacmanJouer = 0");
        items.push_back("nbThemeLotrJouer = 0");
        items.push_back("vieGarde = 0");
        items.push_back("viePerdue = 0");
        items.push_back("fantomeMange = 0");
        for(int i = 0; i < items.size(); i++)
        {
            if(i == items.size() - 1)
            {
                flux << items[i];
            }
            else
            {
                flux << items[i]+"\n";
            }
        }
        return true;
    }
}