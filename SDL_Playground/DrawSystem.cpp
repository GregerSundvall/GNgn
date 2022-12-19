#include "DrawSystem.h"
#include <SDL_render.h>
#include "Engine.h"


void DrawSystem::Add(Float2 position, Float2 size, Sprite sprite)
{
    SDL_Rect rect = {static_cast<int>(position.x - size.x * 0.5),
                    static_cast<int>(position.y - size.y * 0.5),
                    static_cast<int>(size.x), static_cast<int>(size.y)};
    objectsToDraw.push_back(DrawObject(sprite, rect));
}

void DrawSystem::DrawAll()
{
    for (int i = 0; i < objectsToDraw.size(); ++i)
    {
        SDL_SetRenderDrawColor(renderer,
        objectsToDraw[i].sprite.color.r,
        objectsToDraw[i].sprite.color.g,
        objectsToDraw[i].sprite.color.b,
        objectsToDraw[i].sprite.color.a);
        SDL_RenderFillRect(renderer, &objectsToDraw[i].rect);
    }
    objectsToDraw.clear();
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
