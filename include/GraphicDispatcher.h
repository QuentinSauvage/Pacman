//
//  GraphicDispatcher.h
//  ProjetPacman
//
//  Created by Nicolas Serf on 30/04/2015.
//  Copyright (c) 2015 Nicolas Serf. All rights reserved.
//

#ifndef __ProjetPacman__GraphicDispatcher__
#define __ProjetPacman__GraphicDispatcher__

#include <SFML/Graphics.hpp>
#include <vector>

class GraphicDispatcher
{
    
private:
    
    //Nom
    static std::vector<std::string>                             _nomFont;
    static std::string                                          _themeChoisit;
    
    //Element Graphique
    static sf::Texture                                          _entireMapTexture;
    static std::vector<sf::Font>                                _fontListe;
    static std::vector<sf::Texture>                             _textureMap;
    static std::vector<sf::Texture>                             _pacmanTexture;
    static std::vector<sf::Texture>                             _fantomeTexture;
    static std::vector<sf::Texture>                             _statsIcone;
    static std::vector<sf::Texture>                             _fruitTexture;
    static std::vector<sf::Texture>                             _fantomeFaible;
    static std::vector<std::pair<std::string, sf::Texture>>     _imageFondPacman;
    static std::vector<std::pair<std::string, sf::Texture>>     _imageFondLotr;
    
    static int                                                  _nbFond;
    
public:
    
    static void ajouterNouvelleFont(std::string emplacementFont);
    static void definirTheme(std::string theme);
    
    static void loadFond();
    
    static void loadImageFondPacman();
    static void loadImageFondLotr();
    
    static void loadTextureEtFont();
    static void loadStatsTexture();
    static void loadPacmanTexture();
    static void loadFantomeTexture();
    static void loadMapTexture();
    static void loadFruitTexture();
    static void loadFantomeFaibleTexture();
    static void loadFont();
    
    static const sf::Texture& getFondPacman(std::string nomFond);
    static const sf::Texture& getFondLotr(std::string nomFond);
    
    static const sf::Texture& getTexturePacman(int index);
    static const sf::Texture& getIconeTexture(int index);
    static const sf::Texture& getTextureFantomeFaible(int index);
    static const sf::Texture& getTextureFantome(int index);
    static const sf::Texture& getTextureFruit(int index);
    static const sf::Texture& getTextureMap(int index);
    static const sf::Texture& getEntireMapTexture();
    static const sf::Font& getFont(int index);
    
};

#endif /* defined(__ProjetPacman__GraphicDispatcher__) */
