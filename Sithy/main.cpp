//
//  main.cpp
//  Sith
//
//  Created by Timothy Hartt on 11/5/15.
//  Copyright (c) 2015 The Sith Lords. All rights reserved.
//
#include<iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>



const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Texture* loadTexture( std::string path );

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Texture* gTexture = NULL;

class LTexture
{
public:
    LTexture();
    
    ~LTexture();
    
    bool loadFromFile(std::string path);
    void free();
    
    void render(int x , int y);
    int getWidth();
    int getHeight();
    
        private:
    SDL_Texture* mTexture;
    
    int mWidth;
    int mHeight;
    
};

LTexture::LTexture()
{
    mTexture = nullptr;
    mWidth = 0;
    mHeight  = 0;
    
    
}
LTexture gFooTexture;
LTexture gBackgroundTexture;


bool LTexture::loadFromFile(std::string path)
{
    SDL_Texture * newText = NULL;
    
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    
    if(loadedSurface == NULL){
        //Debug
              printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
      
    }else{
        //Do this
        SDL_SetColorKey(loadedSurface, SDL_TRUE,
                        SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newText = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        
        if (newText == NULL){
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }else{
            //DO Things
            
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture =newText;
    
    return mTexture != NULL;
}
void LTexture::render(int x, int y)
{
    SDL_Rect renderQuad ={x,y,mWidth,mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
    
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

void LTexture::free()
{
    if (mTexture != NULL) {
        
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        
        mWidth = 0;
        mHeight = 0;
    }
    
}


LTexture::~LTexture()
{
    
    free();
}





bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load PNG texture
    if( !gFooTexture.loadFromFile("Images/foo.png") )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    
    return success;
}

void close()
{
    //Free loaded image
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {	
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            
            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }
                
                //Clear screen
                SDL_RenderClear( gRenderer );
                SDL_Rect mini;
                mini.x = 0;
                mini.y = 0;
                mini.w = SCREEN_WIDTH/2;
                mini.h = SCREEN_HEIGHT/2;
                
                SDL_RenderSetViewport(gRenderer, &mini);
                
                
                //Render texture to screen
                SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

                
                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }
    
    //Free resources and close SDL
    close();
    
    return 0;
}


