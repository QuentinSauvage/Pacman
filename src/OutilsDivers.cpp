//
//  OutilsDivers.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 24/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "OutilsDivers.h"
#include <random>

int getRandom(int borneInf, int borneSup)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(borneInf, borneSup);
    
    return dis(gen);
}

int puissance(int nombre, int puissance)
{
    int resultat = nombre;
    for(int i = 0; i <= puissance; i++)
    {
        resultat += nombre*i;
    }
    return resultat;
}

/**Cette fonction découpe une phrase à chaque espace, et reenvoie la valeur de la position du mot dans la phrase.
 * exemple: defi = 1
 * defi = positionMotVoulu[0]
 * =    = position 2
 * 1    = position 3
 */
std::string decouperPhrase(std::string phrase, int positionMotVoulu)
{
    std::vector<std::string> ensembleMot;
    std::string mot = "";
    for(auto i : phrase)
    {
        if(i != ' ')
            mot.push_back(i);
        else
        {
            ensembleMot.push_back(mot);
            mot.clear();
        }
    }
    //On insére le dernier mot
    ensembleMot.push_back(mot);
    
    return ensembleMot[positionMotVoulu];
}

//La fonction recoit une phrase tout coller (enregistré dans un fichier par exemple) et la retour avec des espaces
std::string reformerPhraseColle(std::string phrase)
{
    std::string phraseReforme = "";
    for(int i = 0; i < phrase.size(); i++)
    {
        if(phrase[i] >= 65 && phrase[i] <= 90)
        {
            if(i == 0)
                phraseReforme += phrase[i];
            else
            {
                phraseReforme += ' ';
                phraseReforme += std::tolower(phrase[i]);
            }
        }
        else
        {
            phraseReforme += phrase[i];
        }
    }
    return phraseReforme;
}