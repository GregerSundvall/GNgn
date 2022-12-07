#include "Player.h"
#include "Engine.h"

#include <SDL.h>

void Player::Update()
{
    float moveInputX = static_cast<float>(-input->A + input->D);
    float moveInputY = static_cast<float>(-input->W + input->S);

    posX += moveInputX * speed * dTime;
    posY += moveInputY * speed * dTime;
        
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_Rect playerRect = {static_cast<int>(posX), static_cast<int>(posY), 32, 32};
    SDL_RenderFillRect(renderer, &playerRect);
}
