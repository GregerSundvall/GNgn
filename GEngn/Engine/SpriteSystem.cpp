﻿#include "Engine.h"
#include "SpriteSystem.h"

#include <iostream>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "EntitySystem.h"


SpriteSystem::SpriteSystem(EntitySystem* entitySystem)
{
    this->entitySystem = entitySystem;
}

int SpriteSystem::Register(int entityID, Color color)
{
    sprites.push_back(Sprite(entityID, color));
    return static_cast<int>(sprites.size()) -1;
}

void SpriteSystem::Unregister(int spriteID)
{
    if (spriteID < sprites.size() -1)
    {
        entitySystem->UpdateSpriteID(sprites[sprites.size() -1].entityID, spriteID);
        sprites[spriteID].color = sprites[sprites.size() -1].color;
        sprites[spriteID].entityID = sprites[sprites.size() -1].entityID;
    }
    sprites.pop_back();
}

void SpriteSystem::SetColor(int spriteID, Color color)
{
    sprites[spriteID].color = color;
}


void SpriteSystem::SetTexture(int spriteID, std::string imagePath) // Create and assign texture from image file.
{
    sprites[spriteID].imagePath = imagePath;
    drawSystem->CacheTexture(imagePath);
}

void SpriteSystem::SetTexture(int spriteID, const std::string& text, const std::string& fontPath) // Create and assign texture from text.
{
    sprites[spriteID].text = text;
    sprites[spriteID].fontPath = fontPath;
    
    // int size = static_cast<int>(entitySystem->GetTransform(sprites[spriteID].entityID)->size.y);
    // auto color = sprites[spriteID].color;
    // auto sdlColor = SDL_Color(color.r, color.g, color.b, color.a);
    //
    // TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size);
    // if (!font)
    // {
    //     std::cerr << "Failed to load font\n";
    // }
    //
    // auto surface = TTF_RenderText_Solid(font, text.c_str(), sdlColor);
    // if (!surface) { std::cerr << "Failed to create text surface\n"; }
    //
    // auto texture = SDL_CreateTextureFromSurface(drawSystem->renderer, surface);
    //
    // SDL_FreeSurface(surface);
    //
    // if (!texture)
    // {
    //     std::cerr << "Failed to create text texture\n";
    //     return;
    // }
}

void SpriteSystem::AssignNewEntityID(int spriteID, int newEntityID) //Used when destroying an entity
{
    sprites[spriteID].entityID = newEntityID;
}

void SpriteSystem::Update()
{
    for (int i = 0; i < sprites.size(); ++i)
    {
        auto tf = entitySystem->GetTransform(sprites[i].entityID);
        drawSystem->Add(tf->position, tf->size, sprites[i]);
    }
}
