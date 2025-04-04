//
//  graphics.cpp
//  SDL
//
//  Created by Macbook on 18/3/25.
//
#include "graphics.h"
void Graphics::logErrorAndExit(const char* msg, const char* error){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                   "%s: %s", msg, error);
    SDL_Quit();
}
void Graphics::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());
    gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
        logErrorAndExit("CreateWindow", SDL_GetError());
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());
    gRenderer = SDL_CreateRenderer(gWindow, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //renderer =SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (gRenderer == nullptr)
        logErrorAndExit("CreateRenderer", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void Graphics::prepareScene(SDL_Texture * background){
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy( gRenderer, background, NULL, NULL);
}
void Graphics::presentScene(){
    SDL_RenderPresent(gRenderer);
}
SDL_Texture *Graphics::loadTexture(const char *filename){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   "Loading %s", filename);
    SDL_Texture *texture = IMG_LoadTexture(gRenderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                       SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
    return texture;
}
void Graphics::renderTexture(SDL_Texture *texture, int x, int y){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(gRenderer, texture, NULL, &dest);
}
void Graphics::quit(){
    IMG_Quit();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
void Graphics::drawPaddle(int x, int y) {
        SDL_Rect fillRect = {x, y, PADDLE_WIDTH, PADDLE_HEIGHT};
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderFillRect(gRenderer, &fillRect);
    }
void Graphics::drawBall(int x, int y) {
        SDL_Rect fillRect = {x, y, BALL_SIZE, BALL_SIZE};
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderFillRect(gRenderer, &fillRect);
    }

