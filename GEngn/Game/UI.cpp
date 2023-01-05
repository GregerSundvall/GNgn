#include "UI.h"
#include "Game.h"


UI::UI()
{
    framerateBox = new Entity();
    framerateBox->AddTransform({0}, {64});
    framerateBox->AddSprite(Color(255, 255,255, 255));
    // framerateBox->AddSprite("Score", "Res/Fonts/SHOWG.TTF");
}
