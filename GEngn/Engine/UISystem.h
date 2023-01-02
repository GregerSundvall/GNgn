#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>


class Text
{
public:
    Text(const std::string &fontPath, int fontSize, const std::string & content, const SDL_Color &color);

    void Display(int x, int y);

    static SDL_Texture* LoadFont(const std::string &fontPath, int fontSize,
        const std::string & content, const SDL_Color &color);

private:
    SDL_Texture* texture = nullptr;
    SDL_Rect rect;
};




class UISystem
{
    
    
};
