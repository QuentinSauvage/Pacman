//
//  GestionnaireConnexion.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 28/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__GestionnaireConnexion__
#define __ProjetPacman__GestionnaireConnexion__

#include <iostream>
#include <vector>

class GestionnaireConnexion
{
    
private:
    
    std::string                 _nomFichierPseudo;
    std::vector<std::string>    _listePseudo;
    
    void recupererPseudo();
    void ecrirePseudo();
    
public:
    
    GestionnaireConnexion();
    ~GestionnaireConnexion();
    
    bool verifierPseudo(std::string pseudo);
    bool seConnecter(std::string pseudo);
    
    //void supprimerCompte(std::string pseudo);
    
    //le bool va retourner si l'on peut ou non créer le compte
    bool creerCompte(std::string pseudo);
    
    
};

#endif /* defined(__ProjetPacman__GestionnaireConnexion__) */
