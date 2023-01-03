// #include "UISystem.h"
// #include "Engine.h"
// #include "DrawSystem.h"
//
// #include <iostream>
//
// Text::Text(const std::string& fontPath,
//     int fontSize,
//     const std::string& content,
//     const SDL_Color& color)
// {
//     texture = LoadFont(fontPath, fontSize, content, color);
//     SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
// }
//
// void Text::Display(int x, int y)
// {
//     rect.x = x;
//     rect.y = y;
//     SDL_RenderCopy(engine->GetRenderer(), texture, nullptr, &rect);
// }
//
// SDL_Texture* Text::LoadFont(const std::string& fontPath,
//     int fontSize,
//     const std::string& content,
//     const SDL_Color& color)
// {
//     TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
//     if (!font)
//     {
//         std::cerr << "Failed to load font\n";
//     }
//
//     auto surface = TTF_RenderText_Solid(font, content.c_str(), color);
//     if (!surface)
//     {
//         std::cerr << "Failed to create text surface\n";
//     }
//
//     auto texture = SDL_CreateTextureFromSurface(DrawSystem::GetRenderer(), surface);
//     if (!texture)
//     {
//         std:std::cerr << "Failed to create text texture\n";
//     }
//
//     SDL_FreeSurface(surface);
//     return texture;
// }
