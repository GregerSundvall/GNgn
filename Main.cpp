#include "Engine/Engine.h"
#include "Game/Game.h"





int main(int argc, char* argv[])
{
    Engine::Init(1920, 1080);
    Engine::Run();
    
    Game* game = new Game();
    
          
    // Destroy game
    // Destroy engine
    
    return 0;
}
