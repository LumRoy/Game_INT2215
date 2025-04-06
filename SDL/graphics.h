//
//  graphics.h
//  SDL
//
//  Created by Macbook on 18/3/25.
//

#ifndef graphics_h
#define graphics_h
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "defs.h"
#include "const_p.h"
extern SDL_Window* gWindow ;
extern SDL_Renderer* gRenderer;
struct Graphics {
    void logErrorAndExit(const char* msg, const char* error);
    void init();
    void prepareScene(SDL_Texture * background);
    void presentScene();
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void quit();
    void drawPaddle(int x, int y);
    void drawBall(int x, int y);
};
#endif /* graphics_h */
