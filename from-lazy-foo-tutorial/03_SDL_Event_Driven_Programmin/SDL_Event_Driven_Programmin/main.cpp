//
//  main.cpp
//  SDL_Event_Driven_Programmin
//
//  Created by Dmytro Frolov on 11.01.15.
//  Copyright (c) 2015 Dmytro Frolov. All rights reserved.
//


#include <stdio.h>  //for printf
#include <SDL2/SDL.h>

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
    
    //if(success==false) delete this;
}

bool SimpleSDL::loadMedia(char * bmpName){
    bool success = true;
    imageSurface = SDL_LoadBMP(bmpName);
    if(imageSurface==NULL) {
        success = false;
        printf("Error in image loading! SDL_Error: %s\n", SDL_GetError());
    }else{
        SDL_BlitSurface( imageSurface, NULL, mainSurface, NULL );
        SDL_UpdateWindowSurface( mainWindow );
    }
    return success;
}

void SimpleSDL::eventHandler(){
    while( !quit ) {
        while(SDL_PollEvent(&eventH)!=0){
            //User requests quit
            if( eventH.type == SDL_QUIT || (eventH.type == SDL_KEYDOWN && eventH.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
            }
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

int main(int argc, const char * argv[]) {
    system("pwd");
    
    SimpleSDL game;
    game.loadMedia();
    game.eventHandler();

    return 0;
}
