//
//  main.cpp
//  SDL_Event_Driven_Programmin
//
//  Created by Dmytro Frolov on 11.01.15.
//  Copyright (c) 2015 Dmytro Frolov. All rights reserved.
//


#include <stdio.h>  //for printf
#include <SDL2/SDL.h>
#include "SimpleSDL.h"


int main(int argc, const char * argv[]) {
    system("pwd"); //print the current folder path
    
    SimpleSDL game;
    game.loadMedia();
    game.eventHandler();

    return 0;
}
