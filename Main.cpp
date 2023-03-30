


#include "Engine/Engine.h"
#include "Game/Game.h"

int main(int argc, char* argv[])
{
    Engine* engine = new Engine(1920, 1080);
    
    Game* game = new Game();
    
    return 0;
}
