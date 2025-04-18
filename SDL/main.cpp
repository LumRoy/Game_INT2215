//
//  main.cpp
//  SDL
//
//  Created by Macbook on 18/3/25.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include "graphics.h"
// XCode trên MacOS Sequioa khai báo thư viện SDL cần khai báo cả Package SDL 
using namespace std;

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
}
int main(int argc, char* args[]) {
    Graphics graphics;
    graphics.init();
    bool quit = false;
    SDL_Event e;

    SDL_Texture *background=graphics.loadTexture("background.png", gRenderer);
    graphics.prepareScene(background);
    graphics.presentScene();
    graphics.renderTexture(background, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    int paddle1Y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    int paddle2Y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    int ballX = (SCREEN_WIDTH - BALL_SIZE) / 2;
    int ballY = (SCREEN_HEIGHT - BALL_SIZE) / 2;
    int ballVelX = BALL_SPEED;
    int ballVelY = BALL_SPEED;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                        paddle1Y -= PADDLE_SPEED;
                        break;
                    case SDLK_s:
                        paddle1Y += PADDLE_SPEED;
                        break;
                    case SDLK_UP:
                        paddle2Y -= PADDLE_SPEED;
                        break;
                    case SDLK_DOWN:
                        paddle2Y += PADDLE_SPEED;
                        break;
                }
            }
        }
        
        if (paddle1Y < 0) {
            paddle1Y = 0;
        }
        if (paddle1Y > SCREEN_HEIGHT - PADDLE_HEIGHT) {
            paddle1Y = SCREEN_HEIGHT - PADDLE_HEIGHT;
        }
        if (paddle2Y < 0) {
            paddle2Y = 0;
        }
        if (paddle2Y > SCREEN_HEIGHT - PADDLE_HEIGHT) {
            paddle2Y = SCREEN_HEIGHT - PADDLE_HEIGHT;
        }
        
        ballX += ballVelX;
        ballY += ballVelY;

        if (ballY <= 0 || ballY + BALL_SIZE >= SCREEN_HEIGHT) {
            ballVelY = -ballVelY;
        }

        if ((ballX <= PADDLE_WIDTH && ballY + BALL_SIZE >= paddle1Y && ballY <= paddle1Y + PADDLE_HEIGHT) ||
            (ballX + BALL_SIZE >= SCREEN_WIDTH - PADDLE_WIDTH && ballY + BALL_SIZE >= paddle2Y && ballY <= paddle2Y + PADDLE_HEIGHT)) {
            ballVelX = -ballVelX;
        }

        if (ballX <= 0 || ballX + BALL_SIZE >= SCREEN_WIDTH) {
            ballX = (SCREEN_WIDTH - BALL_SIZE) / 2;
            ballY = (SCREEN_HEIGHT - BALL_SIZE) / 2;
            ballVelX = BALL_SPEED;
            ballVelY = BALL_SPEED;
        }

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);

        SDL_RenderCopy(gRenderer, background, NULL, NULL);
        graphics.drawPaddle(0, paddle1Y);
        graphics.drawPaddle(SCREEN_WIDTH - PADDLE_WIDTH, paddle2Y);
        graphics.drawBall(ballX, ballY);
        SDL_RenderPresent(gRenderer);
    }
    close();
    return 0;
}


