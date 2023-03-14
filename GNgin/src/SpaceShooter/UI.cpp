#include "UI.h"
#include "Game.h"


UI::UI()
{
    entityID = entitySystem->CreateEntity();
    Entity()->AddTransform({10}, {64});
    // Entity()->AddSprite(Color(255, 255,255, 255));
    Entity()->AddSprite("Score", "assets/Fonts/SHOWG.TTF");
}

Entity* UI::Entity()
{
    auto entity = entitySystem->GetEntity(entityID);
    return entity;
}
