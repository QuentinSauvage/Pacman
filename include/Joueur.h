//
//  Joueur.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 07/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__Joueur__
#define __ProjetPacman__Joueur__

#include <iostream>
#include <vector>

#include "Succes.h"
#include "ListeSucces.h"

class Joueur
{
    
private:
    
    std::vector<std::pair<std::string, int>>    _informationStatistique;
    std::vector<int>                            _idSuccesValide;
    ListeSucces                                 _listeSucces;
    
    std::string             _pseudo;
    
    void chargerInformation();
    
    
public:
    
    Joueur(std::string pseudo);
    ~Joueur();
    
    std::string getPseudo()const;
    
    void sauvegarderDonnees();
    
    //La méthode va retourner le score du nom de l'information ex: nbThemeLotrJouer
    int recupererScore(std::string nomInformations);
    void validerSucces(int index);
    void updateIncrementPoint(std::string nomSucces, int nbIncrement);
    const ListeSucces& getListeSucces()const;
    const std::vector<int> getIdSuccesValide()const;
    
    void updateSucces(sf::Time& delta);
    void drawSucces(sf::RenderWindow& renderer);
    
    Joueur operator=(Joueur& joueur) = delete;
};

#endif /* defined(__ProjetPacman__Joueur__) */
