//
//  main.cpp
//  Sith
//
//  Created by Timothy Hartt on 11/5/15.
//  Copyright (c) 2015 The Sith Lords. All rights reserved.
//
#include<iostream>
#include <SDL2/SDL.h>

const int SCEEN_WIDTH = 640;
const int SCEEN_HEIGHT = 480;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_J,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* gwindow = NULL;
SDL_Surface* gsurface = NULL;

SDL_Surface* gHelloWorld = NULL;

SDL_Surface* gXOut = NULL;
SDL_Surface* current = NULL;
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str() );
    
    if (loadedSurface ==NULL)
        printf( "Unable to load image %s! SDL Error: %s\n", "Images/Test.bmp", SDL_GetError() );

    return loadedSurface;
}
bool Init()
{
    bool Suc = true;
    if (SDL_Init(SDL_INIT_VIDEO) <0) {
        
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        Suc = false;
    }else{
        gwindow = SDL_CreateWindow("TheDarkSide", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCEEN_WIDTH, SCEEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if(gwindow == NULL) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            Suc = false;
        }else{
            gsurface  = SDL_GetWindowSurface(gwindow);
            
        }
        
    }
    
    return Suc;
}
//
bool loadMedia()
{
    //Loading success flag
    gKeyPressSurfaces[KEY_PRESS_SURFACE_J] = loadSurface("Images/Tan.bmp");
    
    bool success = true;
    
    
    return success;
}


void close()
{
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;
    
    SDL_DestroyWindow(gwindow);
    gwindow =NULL;
    
    
    SDL_Quit();
}


int main(int argc, const char * argv[])
{
    if( !Init()){
        
        printf( "Failed to initialize!\n" );
        
    }else{
        
        if( !loadMedia()){
            printf( "Failed to load media!\n" );
        }else{
            bool quite = false;
            
            SDL_Event e;
            
            while (!quite) {
                
                while(SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quite = true;
                    }
                    
                 }
                SDL_BlitSurface(gHelloWorld,NULL,gsurface,NULL);
                SDL_UpdateWindowSurface(gwindow);
            }
            
            
            
        
        }
        
        
        SDL_Delay( 2000 );
        close();
    }
    return 0;
}



