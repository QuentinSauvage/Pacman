//
//  GraphicDispatcher.cpp
//  ProjetPacman
//
//  Created by Nicolas Serf on 30/04/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#include "GraphicDispatcher.h"
#include <iostream>
#include <fstream>
#include <random>

std::string                                         GraphicDispatcher::_themeChoisit;
std::vector<std::string>                            GraphicDispatcher::_nomFont;
std::vector<sf::Font>                               GraphicDispatcher::_fontListe;
std::vector<sf::Texture>                            GraphicDispatcher::_textureMap;
std::vector<sf::Texture>                            GraphicDispatcher::_pacmanTexture;
std::vector<sf::Texture>                            GraphicDispatcher::_fantomeTexture;
std::vector<sf::Texture>                            GraphicDispatcher::_fruitTexture;
std::vector<sf::Texture>                            GraphicDispatcher::_statsIcone;
std::vector<sf::Texture>                            GraphicDispatcher::_fantomeFaible;
sf::Texture                                         GraphicDispatcher::_entireMapTexture;
std::vector<std::pair<std::string, sf::Texture>>    GraphicDispatcher::_imageFondPacman;
std::vector<std::pair<std::string, sf::Texture>>    GraphicDispatcher::_imageFondLotr;
int                                                 GraphicDispatcher::_nbFond = 0;

void GraphicDispatcher::ajouterNouvelleFont(std::string emplacementFont)
{
    _nomFont.push_back(emplacementFont);
}

void GraphicDispatcher::definirTheme(std::string theme)
{
    _themeChoisit = theme;
}


void GraphicDispatcher::loadFond()
{
    loadImageFondLotr();
    loadImageFondPacman();
}


void GraphicDispatcher::loadTextureEtFont()
{
    loadPacmanTexture();
    loadFantomeTexture();
    loadFruitTexture();
    loadStatsTexture();
    loadFantomeFaibleTexture();
    loadFont();
    loadMapTexture();
}

void GraphicDispatcher::loadFantomeFaibleTexture()
{
    std::string nomFantomeWeak = "Texture/"+_themeChoisit+"/weakFantome.png";
    sf::Texture texture;
    if(!texture.loadFromFile(nomFantomeWeak))
        throw("Pas de fichier de ce nom pour les tile Pacman");
    
    int sizeXTexture = texture.getSize().x;
    int sizeYTexture = texture.getSize().y;
    
    //Une tile de texture fait 32 * 32
    int cpt = 0;
    for(int i = 1; i < sizeYTexture; i+= 33)
    {
        for(int j = 1; j < sizeXTexture; j+= 33)
        {
            _fantomeFaible.push_back(sf::Texture());
            _fantomeFaible[cpt].loadFromFile(nomFantomeWeak, sf::IntRect(j,i,32,32));
            
            cpt++;
        }
    }
}

void GraphicDispatcher::loadImageFondPacman()
{
    std::vector<std::string> chemins;
    std::ifstream fichier("Texture/nomFond.txt");
    std::string lecture;
    while(getline(fichier, lecture))
    {
        chemins.push_back(lecture);
    }
    
    for(int i = 0; i < chemins.size(); i++)
    {
        std::pair<std::string, sf::Texture> tmp;
        tmp.first = chemins[i];
        sf::Texture toLoad;
        if(!toLoad.loadFromFile("Texture/themePacman/fond/"+chemins[i]))
            throw ("Problème de chargement de fond");
        tmp.second= sf::Texture(toLoad);
        
        _imageFondPacman.push_back(tmp);
        _nbFond++;
    }
}

void GraphicDispatcher::loadImageFondLotr()
{
    std::vector<std::string> chemins;
    std::ifstream fichier("Texture/nomFond.txt");
    std::string lecture;
    while(getline(fichier, lecture))
    {
        chemins.push_back(lecture);
    }
    
    for(int i = 0; i < chemins.size(); i++)
    {
        std::pair<std::string, sf::Texture> tmp;
        tmp.first = chemins[i];
        sf::Texture toLoad;
        if(!toLoad.loadFromFile("Texture/themeLotr/fond/"+chemins[i]))
            throw ("Problème de chargement de fond");
        tmp.second= sf::Texture(toLoad);
        _imageFondLotr.push_back(tmp);
    }
}

void GraphicDispatcher::loadPacmanTexture()
{
    std::string nomPacTexture = "Texture/"+_themeChoisit+"/pacman.png";
    sf::Texture texture;
    if(!texture.loadFromFile(nomPacTexture))
        throw("Pas de fichier de ce nom pour les tile Pacman");
    
    int sizeXTexture = texture.getSize().x;
    int sizeYTexture = texture.getSize().y;
    
    //Une tile de texture fait 32 * 32
    int cpt = 0;
    for(int i = 1; i < sizeYTexture; i+= 33)
    {
        for(int j = 1; j < sizeXTexture; j+= 33)
        {
            _pacmanTexture.push_back(sf::Texture());
            _pacmanTexture[cpt].loadFromFile(nomPacTexture, sf::IntRect(j,i,32,32));
            
            cpt++;
        }
    }
}

void GraphicDispatcher::loadFantomeTexture()
{
    std::string nomPacTexture = "Texture/"+_themeChoisit+"/fantome.png";
    sf::Texture texture;
    if(!texture.loadFromFile(nomPacTexture))
        throw("Pas de fichier de ce nom pour les tile Pacman");
    
    int sizeXTexture = texture.getSize().x;
    int sizeYTexture = texture.getSize().y;
    
    //Une tile de texture fait 32 * 32
    int cpt = 0;
    for(int i = 1; i < sizeYTexture; i+= 33)
    {
        for(int j = 1; j < sizeXTexture; j+= 33)
        {
            _fantomeTexture.push_back(sf::Texture());
            _fantomeTexture[cpt].loadFromFile(nomPacTexture, sf::IntRect(j,i,32,32));
            
            cpt++;
        }
    }
}

void GraphicDispatcher::loadFruitTexture()
{
    std::string nomPacTexture = "Texture/"+_themeChoisit+"/fruit.png";
    sf::Texture texture;
    if(!texture.loadFromFile(nomPacTexture))
        throw("Pas de fichier de ce nom pour les tile Pacman");
    
    int sizeXTexture = texture.getSize().x;
    int sizeYTexture = texture.getSize().y;
    
    //Une tile de texture fait 32 * 32
    int cpt = 0;
    for(int i = 1; i < sizeYTexture; i+= 33)
    {
        for(int j = 1; j < sizeXTexture; j+= 33)
        {
            _fruitTexture.push_back(sf::Texture());
            _fruitTexture[cpt].loadFromFile(nomPacTexture, sf::IntRect(j,i,32,32));
            cpt++;
        }
    }
}

void GraphicDispatcher::loadStatsTexture()
{
    std::string nomStatIcone = "Texture/"+_themeChoisit+"/iconeStat.png";
    sf::Texture texture;
    if(!texture.loadFromFile(nomStatIcone))
        throw("Pas de fichier de ce nom pour les tile Pacman");
    
    int sizeXTexture = texture.getSize().x;
    int sizeYTexture = texture.getSize().y;
    
    //Une tile de texture fait 32 * 32
    int cpt = 0;
    for(int i = 1; i < sizeYTexture; i+= 33)
    {
        for(int j = 1; j < sizeXTexture; j+= 33)
        {
            _statsIcone.push_back(sf::Texture());
            _statsIcone[cpt].loadFromFile(nomStatIcone, sf::IntRect(j,i,32,32));
            cpt++;
        }
    }
}

void GraphicDispatcher::loadMapTexture()
{
    std::string nomMapTexture = "Texture/"+_themeChoisit+"/mapTileTest3.png";
    sf::Texture texture;
    if(!(texture.loadFromFile(nomMapTexture)))
        throw("Pas de fichier de ce nom pour les tileMap");
    
    _entireMapTexture = texture;
    
    int sizeXTexture = texture.getSize().x;
    int sizeYTexture = texture.getSize().y;
    
    //Une tile de texture fait 32 * 32
    int cpt = 0;
    for(int i = 1; i < sizeXTexture; i+= 32)
    {
        for(int j = 1; j < sizeYTexture; j+= 32)
        {
            _textureMap.push_back(sf::Texture());
            _textureMap[cpt].loadFromFile(nomMapTexture, sf::IntRect(i,j,32,32));
            cpt++;
        }
    }
}
void GraphicDispatcher::loadFont()
{
    for(size_t i = 0; i < _nomFont.size(); ++i)
    {
        _fontListe.push_back(sf::Font());
        if(!_fontListe[i].loadFromFile(_nomFont[i])){
            throw("error");
        }
    }
}

const sf::Texture& GraphicDispatcher::getFondPacman(std::string nomFond)
{
    for(int i = 0; i < _imageFondPacman.size(); i++)
    {
        if(_imageFondPacman[i].first == nomFond)
            return _imageFondPacman[i].second;
    }
    throw ("Pas de fond de ce nom");
}

const sf::Texture& GraphicDispatcher::getFondLotr(std::string nomFond)
{
    for(int i = 0; i < _imageFondLotr.size(); i++)
    {
        if(_imageFondLotr[i].first == nomFond)
            return _imageFondLotr[i].second;
    }
    throw ("Pas de fond de ce nom");
}

const sf::Texture& GraphicDispatcher::getTextureFantomeFaible(int index)
{
    if(index < 0 || index > _fantomeFaible.size())
        throw("Pas de texture");
    
    return _fantomeFaible[index];
}

const sf::Texture& GraphicDispatcher::getIconeTexture(int index)
{
    if(index < 0 || index > _statsIcone.size())
        throw ("Pas de texture");

    return _statsIcone[index];
}
const sf::Texture& GraphicDispatcher::getTexturePacman(int index)
{
    if(index < 0 || index > _pacmanTexture.size())
        throw("Pas de texture");
    
    return _pacmanTexture[index];
}

const sf::Texture& GraphicDispatcher::getTextureFantome(int index)
{
    if(index < 0 || index > _fantomeTexture.size())
        throw ("Pas de texture");
    
    return _fantomeTexture[index];
}

const sf::Texture& GraphicDispatcher::getTextureFruit(int index)
{
    if(index < 0 || index > _fruitTexture.size())
        throw ("Pas de texture");
    
    return _fruitTexture[index];
}

const sf::Texture& GraphicDispatcher::getTextureMap(int index)
{
    if(index < 0 || index > _textureMap.size())
        throw("Pas de texture");
    
    return _textureMap[index];
}

const sf::Texture& GraphicDispatcher::getEntireMapTexture()
{
    return _entireMapTexture;
}

const sf::Font& GraphicDispatcher::getFont(int index)
{
    if(index < 0 || index > _fontListe.size())
        throw("Pas de font");
    
    return _fontListe[index];
}