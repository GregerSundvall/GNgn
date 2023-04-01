#include "Engine/Engine.h"
#include "Game/Game.h"


extern int WINDOW_WIDTH = 1920;
extern int WINDOW_HEIGHT = 1080;


int main(int argc, char* argv[])
{
    Engine::Init();
    
    Game* game = new Game();
    
    Engine::Run();
          
    // Destroy game
    // Destroy engine
    
    return 0;
}
