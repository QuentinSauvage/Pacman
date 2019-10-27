
//
// Disclamer:
// ----------
///Users/nicolasserf
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include "Application.h"
#include "GraphicDispatcher.h"
#include "GestionnaireSon.h"
#include <unistd.h>

int main(int, char const**)
{
    //Une fonction aprés pour charger les éléments graphiques
    GraphicDispatcher::ajouterNouvelleFont("font/Marathon.ttf");
    GraphicDispatcher::ajouterNouvelleFont("font/Poseidon.ttf");
    GraphicDispatcher::ajouterNouvelleFont("font/Roman.ttf");
    GraphicDispatcher::ajouterNouvelleFont("font/Darleston.otf");
    GraphicDispatcher::ajouterNouvelleFont("font/Stonehen.ttf");
    GraphicDispatcher::ajouterNouvelleFont("font/Carolingia.ttf");
    
    GraphicDispatcher::loadFont();
    GraphicDispatcher::loadFond();
    //GestionnaireSon::chargerSons("themeLotr");
    
    Application appli;
    appli.processEvent();


    
    return 0;
}
