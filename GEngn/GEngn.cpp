#include "Engine/Engine.h"
#include "SDL.h"
#include "GEngn.h"

Engine* engine;

int main( int argc, char* argv[] )
{
    engine = new Engine();
    engine->Run();
    
    return 0;
}

