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
        Draw(objectsToDraw[i]);
    }
    objectsToDraw.clear();
}

void DrawSystem::Draw(DrawObject& drawObject)
{
    SDL_SetRenderDrawColor(renderer, drawObject.sprite.Color.R,
        drawObject.sprite.Color.G,
        drawObject.sprite.Color.B,
        drawObject.sprite.Color.A);
    SDL_RenderFillRect(renderer, &drawObject.rect);
}
