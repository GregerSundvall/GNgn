#include "Engine/Engine.h"
#include "Game/Game.h"





int main(int argc, char* argv[])
{
    Engine::Init(1920, 1080);
    
    Game* game = new Game();
    
    Engine::Run();
          
    // Destroy game
    // Destroy engine
    
    return 0;
}
