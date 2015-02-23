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
    
    //Key press surfaces constants
    enum KeyPressSurfaces {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };
    
    const int SCREEN_WIDTH = 690;
    const int SCREEN_HEIGHT = 490;
    
public:
    //initialization
    SimpleSDL();
    ~SimpleSDL();
    //key press handler
    void eventHandler();
    //for background image
    bool loadMedia(char * bmpName = (char *)("img/hello_world.bmp"));
    
    SDL_Texture * loadTexture(char * imgPath = (char *)("img/hello_world.bmp"));


private:
    //main window
    SDL_Window * mainWindow = NULL;
    
    //surface what window contain
    SDL_Surface * mainSurface = NULL;
    
    //The window renderer
    SDL_Renderer* mainRenderer = NULL;
    
    //current shown texture
    SDL_Texture * mainTexture = NULL;
    
    //surface for image
    SDL_Surface * imageSurface = NULL;
    
    //eventHandler vars
    bool quit = false;
    SDL_Event eventH;
    
    //The textures that correspond to a keypress
    SDL_Texture* keyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
};



#endif
