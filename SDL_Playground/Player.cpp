#include "Player.h"
#include "Engine.h"

#include <SDL.h>

void Player::Update()
{
    float moveInputX = -input->A + input->D;
    float moveInputY = -input->W + input->S;

    posX += moveInputX * speed * dTime;
    posY += moveInputY * speed * dTime;
        
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_Rect playerRect = {(int)posX, (int)posY, 32, 32};
    SDL_RenderFillRect(renderer, &playerRect);
}
