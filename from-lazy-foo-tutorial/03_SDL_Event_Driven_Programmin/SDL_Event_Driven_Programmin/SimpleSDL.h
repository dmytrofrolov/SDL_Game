//
//  SimpleSDL.h
//  SDL_Event_Driven_Programmin
//
//  Created by Dmytro Frolov on 11.02.15.
//  Copyright (c) 2015 Dmytro Frolov. All rights reserved.
//

#ifndef SDL_Event_Driven_Programmin_SimpleSDL_h
#define SDL_Event_Driven_Programmin_SimpleSDL_h

#include "SDL2/SDL.h"

class SimpleSDL{
    
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    
public:
    //initialization
    SimpleSDL();
    ~SimpleSDL();
    void eventHandler();
    //for background image
    bool loadMedia(char * bmpName = (char *)("hello_world.bmp"));
    
private:
    //main window
    SDL_Window * mainWindow = NULL;
    
    //surface what window contain
    SDL_Surface * mainSurface = NULL;
    
    //surface for image
    SDL_Surface * imageSurface = NULL;
    
    //eventHandler vars
    bool quit = false;
    SDL_Event eventH;
};



#endif
