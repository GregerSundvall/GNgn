#include "DrawSystem.h"
#include <iostream>
#include <SDL_render.h>
#include <SDL_image.h>
#include "Engine.h"


void DrawSystem::Add(Float2 position, Float2 size, Sprite& sprite)
{
    SDL_Rect rect = { static_cast<int>(position.x), static_cast<int>(position.y),
                    static_cast<int>(size.x), static_cast<int>(size.y) };
    // TODO Add offset so position means CENTER position.
    
    lvl3StuffToDraw.push_back(DrawObject(sprite, rect));
}

void DrawSystem::CacheTexture(std::string imagePath)
{
    if (textureCache.contains(imagePath))
    {
        return;
    }

    SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath.c_str());
    if (!texture)
    {
        std::cerr << "DrawSystem failed to create texture\n";
        return;
    }
    textureCache.try_emplace(imagePath, texture);
}


void DrawSystem::Update()
{
    // for (int i = 0; i < objectsToDraw.size(); ++i)
    // {
    //     SDL_SetRenderDrawColor(renderer,
    //     objectsToDraw[i].sprite.color.r,
    //     objectsToDraw[i].sprite.color.g,
    //     objectsToDraw[i].sprite.color.b,
    //     objectsToDraw[i].sprite.color.a);
    //     SDL_RenderFillRect(renderer, &objectsToDraw[i].rect);
    //     
    // }
    // objectsToDraw.clear();

    for (int i = 0; i < lvl3StuffToDraw.size(); ++i)
    {
        if (lvl3StuffToDraw[i].sprite.imagePath != "")
        {
            std::string  path = lvl3StuffToDraw[i].sprite.imagePath;
            SDL_Texture* texture = textureCache.find(path)->second;
            SDL_RenderCopy(renderer, texture, nullptr, &lvl3StuffToDraw[i].rect);
            continue;
        }
        auto color = lvl3StuffToDraw[i].sprite.color;
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &lvl3StuffToDraw[i].rect);
    }
    lvl3StuffToDraw.clear();

    // Debug stuff
    // auto texture = IMG_LoadTexture(drawSystem->renderer, "Res/Ships/player.png");
    // SDL_Rect rect = SDL_Rect(32, 32, 32, 32);
    // SDL_RenderCopy(renderer, texture, nullptr, &rect);


    // TODO Draw the other vectors
}

void DrawSystem::Draw(DrawObject& drawObject)
{
    SDL_SetRenderDrawColor(renderer,
        drawObject.sprite.color.r,
        drawObject.sprite.color.g,
        drawObject.sprite.color.b,
        drawObject.sprite.color.a);
    SDL_RenderFillRect(renderer, &drawObject.rect);
}

