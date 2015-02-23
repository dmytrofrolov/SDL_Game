//
//  main.cpp
//  SDL_Geometry_rendering
//
//  Created by Dmytro Frolov on 23.02.15.
//  Copyright (c) 2015 Dmytro Frolov. All rights reserved.
//

#include <iostream>
#include "SDL2/SDL.h"
#include "SimpleSDL.h"


int main(int argc, const char * argv[]) {
    //find path to executable file
    system("pwd");
    
    //create new game
    SimpleSDL * theGame = new SimpleSDL;
    theGame->loadMedia();
    theGame->eventHandler();
    delete theGame;
    return 0;
}
