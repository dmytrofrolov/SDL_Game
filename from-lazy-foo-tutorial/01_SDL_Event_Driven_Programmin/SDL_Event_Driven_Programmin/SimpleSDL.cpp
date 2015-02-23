//
//  SimpleSDL.cpp
//  SDL_Event_Driven_Programmin
//
//  Created by Dmytro Frolov on 11.02.15.
//  Copyright (c) 2015 Dmytro Frolov. All rights reserved.
//

#include <stdio.h>
#include "SimpleSDL.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

SimpleSDL::SimpleSDL(){
    //is initializing success
    bool success = false;
    if(SDL_Init(SDL_INIT_VIDEO) >= 0){
        //Create window
        mainWindow = SDL_CreateWindow("Event driven SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if(mainWindow==NULL){
            printf("Error in window creating! SDL_Error: %s\n", SDL_GetError() );
        }else{
            success = true;
            mainSurface = SDL_GetWindowSurface(mainWindow);
        }
        
    }else{
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    
}

//bmp name is for main image surface
bool SimpleSDL::loadMedia(char * bmpName){
    bool success = true;
    imageSurface = loadSurface(bmpName);
    if(imageSurface==NULL) {
        success = false;
        printf("Error in image loading! SDL_Error: %s\n", SDL_GetError());
    }else{
        SDL_BlitSurface( imageSurface, NULL, mainSurface, NULL );
        SDL_UpdateWindowSurface( mainWindow );
    }
    
    keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = IMG_Load((char * )("img/loaded.png"));
    keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface((char * )("img/key_up.bmp"));
    keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface((char * )("img/key_down.bmp"));
    keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface((char * )("img/key_left.bmp"));
    keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface((char * )("img/key_right.bmp"));

    
    return success;
}

SDL_Surface * SimpleSDL::loadSurface(char * bmpName){
    //The final optimized image
    SDL_Surface * optimizedSurface = NULL;
    SDL_Surface * tempSurface = SDL_LoadBMP(bmpName);
    if(tempSurface==NULL){
        printf( "Unable to load image %s! SDL Error: %s\n", bmpName, SDL_GetError() );
    }else{
        optimizedSurface = SDL_ConvertSurface(tempSurface, tempSurface->format, NULL);
        if(optimizedSurface==NULL){
            printf("Unable to optimize image %s! SDL Error:\n", SDL_GetError());
        }
        SDL_FreeSurface( tempSurface );
    }
    //Apply the image stretched
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;
    SDL_BlitScaled( optimizedSurface, NULL, optimizedSurface, &stretchRect );
    return optimizedSurface;
}

void SimpleSDL::eventHandler(){
    while( !quit ) {
        while(SDL_PollEvent(&eventH)!=0){
            //User requests quit
            if( eventH.type == SDL_QUIT || (eventH.type == SDL_KEYDOWN && eventH.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
            }else if (eventH.type == SDL_KEYDOWN){
                switch (eventH.key.keysym.sym) {
                    case SDLK_UP:
                        imageSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
                        break;
                    case SDLK_DOWN:
                        imageSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                        break;
                    case SDLK_LEFT:
                        imageSurface = keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                        break;
                    case SDLK_RIGHT:
                        imageSurface = keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;

                    default:
                        imageSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                }
            }
            
            SDL_BlitSurface(imageSurface, NULL, mainSurface, NULL);
            SDL_UpdateWindowSurface(mainWindow);
            SDL_Delay(20);
            
        }
    }
    SDL_Delay( 10 );
}

SimpleSDL::~SimpleSDL(){
    SDL_FreeSurface(mainSurface);
    mainSurface = NULL;
    
    SDL_FreeSurface(imageSurface);
    imageSurface = NULL;
    
    SDL_DestroyWindow(mainWindow);
    mainWindow = NULL;
    
    SDL_Quit();
}
