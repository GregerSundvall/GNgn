#include "Engine/Engine.h"
#include "Game/Game.h"


constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;


int main(int argc, char* argv[])
{
    Engine* engine = new Engine();
    engine->Run();
    
    Game* game = new Game();

    
    
    
    return 0;
}
