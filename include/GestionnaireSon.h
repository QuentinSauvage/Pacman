//
//  GestionnaireSon.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 21/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__GestionnaireSon__
#define __ProjetPacman__GestionnaireSon__

#include <vector>
#include <SFML/Audio.hpp>

class GestionnaireSon {
    
private:
    static bool                                             _jouerMusiqueFond;
    static std::vector<std::string>                         _chemins; // Vecteur de chemins vers les fichiers à ouvrir.
    static std::vector<sf::SoundBuffer>                     _buffers; // Les buffers nécessaire aux sons.
    static std::vector<std::pair<std::string, sf::Sound>>   _songs; // Vecteur contenant les différents sons du jeu.
    static sf::Music                                        _musiqueEnLecture;
    static bool _enLecture;
    
public:

    static void pasJouerMusiqueFond();
    static void jouerMusiqueFond(std::string theme);
    
    static void autoriserMusiqueFond(bool accept);
    static void stopToutesMusiques();
    static void chargerSons(std::string theme);
    static void jouer(std::string titre);
    static bool enLecture();
    
    static void setVolumeGeneral(int volume);
    static void setVolumeMusique();
    
    static int getDuree(std::string titre);
};

#endif /* defined(__ProjetPacman__GestionnaireSon__) */
