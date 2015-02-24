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
        
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        mainWindow = SDL_CreateWindow("Event driven SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if(mainWindow==NULL){
            printf("Error in window creating! SDL_Error: %s\n", SDL_GetError() );
        }else{
            success = true;
            
            //create renderer for window
            mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
            
            if(mainRenderer==NULL){
                printf("Renderer cannot be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }else{
                //initialize renderer colour
                SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
            
        
        }
        
    }else{
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    
}

//bmp name is for main image surface
bool SimpleSDL::loadMedia(char * bmpName){
    bool success = true;
    mainTexture = loadTexture(bmpName);
    if(mainTexture==NULL) {
        success = false;
        printf("Error in image loading! SDL_Error: %s\n", SDL_GetError());
    }
    
    keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadTexture((char * )("img/key_up.bmp"));
    keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadTexture((char * )("img/key_up.bmp"));
    keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadTexture((char * )("img/key_down.bmp"));
    keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadTexture((char * )("img/key_left.bmp"));
    keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadTexture((char * )("img/key_right.bmp"));

    
    return success;
}

SDL_Texture * SimpleSDL::loadTexture(char * imgPath){
    //Loading success flag
    bool success = true;
    SDL_Texture * tempTexture = NULL;
    //Load PNG texture
    tempTexture = loadTexture( "texture.png" );
    if( tempTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    return tempTexture;
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
