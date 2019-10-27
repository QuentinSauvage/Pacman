//
//  GestionnaireSon.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 21/05/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "GestionnaireSon.h"
#include <fstream>
#include <iostream>

std::vector<std::string>                        GestionnaireSon::_chemins;
std::vector<sf::SoundBuffer>                    GestionnaireSon::_buffers;
std::vector<std::pair<std::string, sf::Sound>>  GestionnaireSon::_songs;
sf::Music                                       GestionnaireSon::_musiqueEnLecture;
bool                                            GestionnaireSon::_jouerMusiqueFond;

void GestionnaireSon::pasJouerMusiqueFond()
{
    _musiqueEnLecture.stop();
}

void GestionnaireSon::jouerMusiqueFond(std::string theme)
{
    if(_jouerMusiqueFond)
    {
        if(!_musiqueEnLecture.openFromFile("Son/"+theme+"/pacmanMusiqueTheme.ogg"))
        {
            throw "La musique n'a pas été trouve";
        }
        _musiqueEnLecture.play();
        setVolumeMusique();
        _musiqueEnLecture.setLoop(true);
    }
}

void GestionnaireSon::autoriserMusiqueFond(bool accept)
{
    _jouerMusiqueFond = accept;
}

void GestionnaireSon::chargerSons(std::string theme)
{
    std::ifstream fichier("Son/nomSons.txt");
    std::string lecture;
    while(getline(fichier, lecture))
    {
        _chemins.push_back(lecture);
    }
        std::cout << "mid1" << std::endl;

    //Chargement sound buffer
    for(int i = 0; i < _chemins.size(); i++)
    {
        std::cout << "Son/" << theme << "/" << _chemins[i] << std::endl;
        _buffers.push_back(sf::SoundBuffer());
         if(!_buffers[i].loadFromFile("Son/"+theme+"/"+_chemins[i]))
         {
         throw ("Probleme chargement son");
         }
    }

    std::cout << "mid2" << std::endl;
    //Construction des sons
    for(int i = 0; i < _chemins.size(); i++)
    {
        std::pair<std::string, sf::Sound> tmp;
        tmp.first = _chemins[i];
        tmp.second = sf::Sound(_buffers[i]);
        
        _songs.push_back(tmp);
    }
}

void GestionnaireSon::setVolumeGeneral(int volume)
{
    for(int i = 0; i < _songs.size(); i++)
        _songs[i].second.setVolume(volume);
    
    _musiqueEnLecture.setVolume(volume);
}

void GestionnaireSon::setVolumeMusique()
{
    if(_songs.size() == 0)
        _musiqueEnLecture.setVolume(20);
    else
        _musiqueEnLecture.setVolume(_songs[0].second.getVolume()/4.0);
}

void GestionnaireSon::stopToutesMusiques()
{
    for(auto i : _songs)
        i.second.stop();
    
    _musiqueEnLecture.stop();
}

int GestionnaireSon::getDuree(std::string titre)
{
    for(int i = 0; i < _songs.size(); i++)
        if(_songs[i].first == titre)
            return _buffers[i].getDuration().asSeconds();
}

bool GestionnaireSon::enLecture()
{
    for(int i = 0; i < _songs.size(); i++)
    {
        if(_songs[i].second.getStatus() == sf::Sound::Status::Playing)
        {
            return true;
        }
    }
    return false;
}

void GestionnaireSon::jouer(std::string titre)
{
    for(int i = 0; i < _songs.size(); i++)
    {
        if(_songs[i].first == titre)
        {
            _songs[i].second.play();
        }
    }
}

